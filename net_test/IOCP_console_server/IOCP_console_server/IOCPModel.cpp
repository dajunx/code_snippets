#include "IOCPModel.h"

// ÿһ���������ϲ������ٸ��߳�(Ϊ������޶ȵ��������������ܣ���������ĵ�)
#define WORKER_THREADS_PER_PROCESSOR 2
// ͬʱͶ�ݵ�Accept���������(���Ҫ����ʵ�ʵ�����������)
#define MAX_POST_ACCEPT              10
// ���ݸ�Worker�̵߳��˳��ź�
#define EXIT_CODE                    NULL


// �ͷ�ָ��;����Դ�ĺ�

// �ͷ�ָ���
#define RELEASE(x) \
  {if(x != NULL ){delete x;x=NULL;}}
// �ͷž����
#define RELEASE_HANDLE(x) \
  { \
      if(x != NULL && x!=INVALID_HANDLE_VALUE) { \
        CloseHandle(x);x = NULL;
      } \
  }
// �ͷ�Socket��
#define RELEASE_SOCKET(x) {if(x !=INVALID_SOCKET) { closesocket(x);x=INVALID_SOCKET;}}

CIOCPModel::CIOCPModel(void):
              nThreads(0),
              hShutdownEvent(NULL),
              hIOCompletionPort(NULL),
              phWorkerThreads(NULL),
              strIP(DEFAULT_IP),
              nPort(DEFAULT_PORT),
              lpfnAcceptEx(NULL),
              pListenContext(NULL)
{
}

CIOCPModel::~CIOCPModel(void)
{
	// ȷ����Դ�����ͷ�
	this->Stop();
}

///////////////////////////////////////////////////////////////////
// �������̣߳�  ΪIOCP�������Ĺ������߳�
//         Ҳ����ÿ����ɶ˿��ϳ�����������ݰ����ͽ�֮ȡ�������д�����߳�
DWORD WINAPI CIOCPModel::WorkerThread(LPVOID lpParam)
{
	THREADPARAMS_WORKER* pParam = (THREADPARAMS_WORKER*)lpParam;
	CIOCPModel* pIOCPModel = (CIOCPModel*)pParam->pIOCPModel;
	int nThreadNo = (int)pParam->nThreadNo;

	printf("�������߳�������ID: %d.\n",nThreadNo);

	OVERLAPPED           *pOverlapped = NULL;
	PER_SOCKET_CONTEXT   *pSocketContext = NULL;
	DWORD                dwBytesTransfered = 0;

	// ѭ����������֪�����յ�Shutdown��ϢΪֹ
	while (WAIT_OBJECT_0 != WaitForSingleObject(pIOCPModel->hShutdownEvent, 0))
	{
		BOOL bReturn = GetQueuedCompletionStatus(
			pIOCPModel->hIOCompletionPort,
			&dwBytesTransfered,
			(PULONG_PTR)&pSocketContext,
			&pOverlapped,
			INFINITE);

		// ����յ������˳���־����ֱ���˳�
		if(EXIT_CODE == (DWORD)pSocketContext)
		{
			break;
		}

		// �ж��Ƿ�����˴���
		if(!bReturn)
		{
			// ��ʾһ����ʾ��Ϣ
			if(!pIOCPModel->HandleError(pSocketContext))
			{
				break;
			}

			continue;  
		}

    // ��ȡ����Ĳ���
    PER_IO_CONTEXT* pIoContext = CONTAINING_RECORD(pOverlapped, PER_IO_CONTEXT, m_Overlapped);

    // �ж��Ƿ��пͻ��˶Ͽ���
    if((0 == dwBytesTransfered) && (RECV_POSTED==pIoContext->m_OpType || SEND_POSTED==pIoContext->m_OpType))
    {  
      printf("�ͻ��� %s:%d �Ͽ�����.\n", inet_ntoa(pSocketContext->m_ClientAddr.sin_addr), ntohs(pSocketContext->m_ClientAddr.sin_port));

      // �ͷŵ���Ӧ����Դ
      pIOCPModel->RemoveContext(pSocketContext);
      continue;  
    }  

    switch(pIoContext->m_OpType)
    {
    case ACCEPT_POSTED:
      { 
        // Ϊ�����Ӵ���ɶ��ԣ�������ר�ŵ�_DoAccept�������д�����������
        pIOCPModel->DoAccpet(pSocketContext, pIoContext);
      }
      break;
    case RECV_POSTED:
      {
        // Ϊ�����Ӵ���ɶ��ԣ�������ר�ŵ�_DoRecv�������д����������
        pIOCPModel->DoRecv(pSocketContext, pIoContext);
      }
      break;

      // SEND
      // �����Թ���д�ˣ�Ҫ������̫���ˣ���������⣬Send�������������һЩ
    case SEND_POSTED:
      {

      }
      break;
    default:
      // ��Ӧ��ִ�е�����
      std::cout<<("_WorkThread�е� pIoContext->m_OpType �����쳣.\n")<<std::endl;
      break;
    }
	}

	std::cout<<"�������߳�"<<nThreadNo<<" ���˳�.\n"<<std::endl;

	// �ͷ��̲߳���
	RELEASE(lpParam);	
	return 0;
}

// ��ʼ��WinSock 2.2
bool CIOCPModel::LoadSocketLib()
{    
	WSADATA wsaData;
	int nResult = WSAStartup(MAKEWORD(2,2), &wsaData);
	// ����(һ�㶼�����ܳ���)
	if (NO_ERROR != nResult)
	{
		printf("��ʼ��WinSock 2.2ʧ�ܣ�\n");
		return false; 
	}

	return true;
}

//	����������
bool CIOCPModel::InitServer()
{
	// ��ʼ���̻߳�����
	InitializeCriticalSection(&csContextList);

	// ����ϵͳ�˳����¼�֪ͨ
	hShutdownEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	// ��ʼ��IOCP
	if (false == InitIOCP())
	{
		printf("��ʼ��IOCPʧ�ܣ�\n");
		return false;
	} else {
		printf("\nIOCP��ʼ�����\n.");
	}

	// ��ʼ��Socket
	if( false==InitListenSocket() )
	{
		printf("Listen Socket��ʼ��ʧ�ܣ�\n");
		this->DeInitialize();
		return false;
	} else {
		printf("Listen Socket��ʼ�����.\n");
	}

	printf("ϵͳ׼���������Ⱥ�����....\n");

	return true;
}


//	��ʼ����ϵͳ�˳���Ϣ���˳���ɶ˿ں��߳���Դ
void CIOCPModel::Stop()
{
	if( pListenContext!=NULL && pListenContext->m_Socket!=INVALID_SOCKET )
	{
		// ����ر���Ϣ֪ͨ
		SetEvent(hShutdownEvent);

		for (int i = 0; i < nThreads; i++)
		{
			// ֪ͨ���е���ɶ˿ڲ����˳�
			PostQueuedCompletionStatus(hIOCompletionPort, 0, (DWORD)EXIT_CODE, NULL);
		}

		// �ȴ����еĿͻ�����Դ�˳�
		WaitForMultipleObjects(nThreads, phWorkerThreads, TRUE, INFINITE);

		// ����ͻ����б���Ϣ
		this->ClearContextList();

		// �ͷ�������Դ
		this->DeInitialize();

		printf("ֹͣ����\n");
	}	
}

// ��ʼ����ɶ˿�
bool CIOCPModel::InitIOCP()
{
	// ������һ����ɶ˿�
	hIOCompletionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);

	if (NULL == hIOCompletionPort)
	{
		printf("������ɶ˿�ʧ�ܣ��������: %d!\n", WSAGetLastError());
		return false;
	}

	// ���ݱ����еĴ�����������������Ӧ���߳���
	nThreads = WORKER_THREADS_PER_PROCESSOR * GetNoOfProcessors();
	
	// Ϊ�������̳߳�ʼ�����
	phWorkerThreads = new HANDLE[nThreads];
	
	// ���ݼ�����������������������߳�
	DWORD nThreadID;
	for (int i = 0; i < nThreads; i++)
	{
		THREADPARAMS_WORKER* pThreadParams = new THREADPARAMS_WORKER;
		pThreadParams->pIOCPModel = this;
		pThreadParams->nThreadNo  = i+1;
		phWorkerThreads[i] = CreateThread(0, 0, WorkerThread, static_cast<void *>(pThreadParams), 0, &nThreadID);
	}

	printf(" ���� _WorkerThread %d ��.\n", nThreads);
	return true;
}

// ��ʼ��Socket
bool CIOCPModel::InitListenSocket()
{
	// AcceptEx �� GetAcceptExSockaddrs ��GUID�����ڵ�������ָ��
	GUID GuidAcceptEx = WSAID_ACCEPTEX;  
	GUID GuidGetAcceptExSockAddrs = WSAID_GETACCEPTEXSOCKADDRS; 

	// ��������ַ��Ϣ�����ڰ�Socket
	struct sockaddr_in ServerAddress;

	// �������ڼ�����Socket����Ϣ
	pListenContext = new PER_SOCKET_CONTEXT;

	// ��Ҫʹ���ص�IO�������ʹ��WSASocket������Socket���ſ���֧���ص�IO����
	pListenContext->m_Socket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	if (INVALID_SOCKET == pListenContext->m_Socket) 
	{
		printf("��ʼ��Socketʧ�ܣ��������: %d.\n", WSAGetLastError());
		return false;
	} else {
		printf("WSASocket() ���.\n");
	}

	// ��Listen Socket������ɶ˿���
	if( NULL== CreateIoCompletionPort( (HANDLE)pListenContext->m_Socket, hIOCompletionPort,(DWORD)pListenContext, 0))  
	{  
		printf("�� Listen Socket����ɶ˿�ʧ�ܣ��������: %d\n", WSAGetLastError());  
		RELEASE_SOCKET( pListenContext->m_Socket );
		return false;
	} else {
		printf("Listen Socket����ɶ˿� ���.\n");
	}

	// ����ַ��Ϣ
	ZeroMemory((char *)&ServerAddress, sizeof(ServerAddress));
	ServerAddress.sin_family = AF_INET;
	// ������԰��κο��õ�IP��ַ�����߰�һ��ָ����IP��ַ 
	//ServerAddress.sin_addr.s_addr = htonl(INADDR_ANY);                      
	ServerAddress.sin_addr.s_addr = inet_addr(strIP.c_str());         
	ServerAddress.sin_port = htons(nPort);                          

	// �󶨵�ַ�Ͷ˿�
	if (SOCKET_ERROR == bind(pListenContext->m_Socket, (struct sockaddr *)&ServerAddress, sizeof(ServerAddress))) 
	{
		printf("bind()����ִ�д���.\n");
		return false;
	} else {
		printf("bind() ���.\n");
	}

	// ��ʼ���м���
	if (SOCKET_ERROR == listen(pListenContext->m_Socket, SOMAXCONN))
	{
		printf("Listen()����ִ�г��ִ���.\n");
		return false;
	} else {
		printf("Listen() ���.\n");
	}

	// ʹ��AcceptEx��������Ϊ���������WinSock2�淶֮���΢�������ṩ����չ����
	// ������Ҫ�����ȡһ�º�����ָ�룬��ȡAcceptEx����ָ��
	DWORD dwBytes = 0;  
	if(SOCKET_ERROR == WSAIoctl(
		pListenContext->m_Socket, 
		SIO_GET_EXTENSION_FUNCTION_POINTER, 
		&GuidAcceptEx, 
		sizeof(GuidAcceptEx), 
		&lpfnAcceptEx, 
		sizeof(lpfnAcceptEx), 
		&dwBytes, 
		NULL, 
		NULL))  
	{  
		printf("WSAIoctl δ�ܻ�ȡAcceptEx����ָ�롣�������: %d\n", WSAGetLastError()); 
		this->DeInitialize();
		return false;  
	}  

	// ��ȡGetAcceptExSockAddrs����ָ�룬Ҳ��ͬ��
	if(SOCKET_ERROR == WSAIoctl(
		pListenContext->m_Socket, 
		SIO_GET_EXTENSION_FUNCTION_POINTER, 
		&GuidGetAcceptExSockAddrs,
		sizeof(GuidGetAcceptExSockAddrs), 
		&lpfnGetAcceptExSockAddrs, 
		sizeof(lpfnGetAcceptExSockAddrs),   
		&dwBytes, 
		NULL, 
		NULL))  
	{  
		printf("WSAIoctl δ�ܻ�ȡGuidGetAcceptExSockAddrs����ָ�롣�������: %d\n", WSAGetLastError());  
		this->DeInitialize();
		return false; 
	}  

	// ΪAcceptEx ׼��������Ȼ��Ͷ��AcceptEx I/O����
	for( int i=0;i<MAX_POST_ACCEPT;i++ )
	{
		// �½�һ��IO_CONTEXT
		PER_IO_CONTEXT* pAcceptIoContext = pListenContext->GetNewIoContext();

		if(false == this->PostAccept(pAcceptIoContext))
		{
			pListenContext->RemoveContext(pAcceptIoContext);
			return false;
		}
	}

	printf("Ͷ�� %d ��AcceptEx�������\n",MAX_POST_ACCEPT );
	return true;
}

//	����ͷŵ�������Դ
void CIOCPModel::DeInitialize()
{
	// ɾ���ͻ����б�Ļ�����
	DeleteCriticalSection(&csContextList);

	// �ر�ϵͳ�˳��¼����
	RELEASE_HANDLE(hShutdownEvent);

	// �ͷŹ������߳̾��ָ��
	for( int i=0;i<nThreads;i++ )
	{
		RELEASE_HANDLE(phWorkerThreads[i]);
	}
	
	RELEASE(phWorkerThreads);

	// �ر�IOCP���
	RELEASE_HANDLE(hIOCompletionPort);

	// �رռ���Socket
	RELEASE(pListenContext);
	printf("�ͷ���Դ���.\n");
}


// Ͷ��Accept����
bool CIOCPModel::PostAccept( PER_IO_CONTEXT* pAcceptIoContext )
{
	assert( INVALID_SOCKET!=pListenContext->m_Socket );

	// ׼������
	DWORD dwBytes = 0;  
	pAcceptIoContext->m_OpType = ACCEPT_POSTED;  
	WSABUF *p_wbuf   = &pAcceptIoContext->m_wsaBuf;
	OVERLAPPED *p_ol = &pAcceptIoContext->m_Overlapped;
	
	// Ϊ�Ժ�������Ŀͻ�����׼����Socket( ������봫ͳaccept�������� ) 
	pAcceptIoContext->m_sockAccept  = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);  
	if( INVALID_SOCKET==pAcceptIoContext->m_sockAccept )  
	{  
		printf("��������Accept��Socketʧ�ܣ��������: %d\n", WSAGetLastError()); 
		return false;  
	} 

	// Ͷ��AcceptEx
	if(FALSE == lpfnAcceptEx(pListenContext->m_Socket, pAcceptIoContext->m_sockAccept, 
                             p_wbuf->buf, 
                             p_wbuf->len - ((sizeof(SOCKADDR_IN)+16)*2),   
								             sizeof(SOCKADDR_IN)+16, 
                             sizeof(SOCKADDR_IN)+16, 
                             &dwBytes, p_ol))  
	{  
		if(WSA_IO_PENDING != WSAGetLastError())  
		{  
			printf("Ͷ�� AcceptEx ����ʧ�ܣ��������: %d\n", WSAGetLastError());  
			return false;  
		}  
	} 

	return true;
}

////////////////////////////////////////////////////////////
// ���пͻ��������ʱ�򣬽��д���
// �����е㸴�ӣ���Ҫ�ǿ������Ļ����Ϳ����׵��ĵ���....
// ������������Ļ�����ɶ˿ڵĻ������������һ�����

// ��֮��Ҫ֪�����������ListenSocket��Context��������Ҫ����һ�ݳ������������Socket��
// ԭ����Context����Ҫ���������Ͷ����һ��Accept����
//
bool CIOCPModel::DoAccpet( PER_SOCKET_CONTEXT* pSocketContext, PER_IO_CONTEXT* pIoContext )
{
	SOCKADDR_IN* ClientAddr = NULL;
	SOCKADDR_IN* LocalAddr = NULL;  
	int remoteLen = sizeof(SOCKADDR_IN), localLen = sizeof(SOCKADDR_IN);  

	// 1. ����ȡ������ͻ��˵ĵ�ַ��Ϣ
	// ��� m_lpfnGetAcceptExSockAddrs �����˰�~~~~~~
	// ��������ȡ�ÿͻ��˺ͱ��ض˵ĵ�ַ��Ϣ������˳��ȡ���ͻ��˷����ĵ�һ�����ݣ���ǿ����...
	this->lpfnGetAcceptExSockAddrs(pIoContext->m_wsaBuf.buf, 
                                 pIoContext->m_wsaBuf.len - ((sizeof(SOCKADDR_IN)+16)*2), 
                                 sizeof(SOCKADDR_IN)+16, 
                                 sizeof(SOCKADDR_IN)+16, 
                                 (LPSOCKADDR*)&LocalAddr, 
                                 &localLen, 
                                 (LPSOCKADDR*)&ClientAddr, 
                                 &remoteLen);  

	printf("�ͻ��� %s:%d ����.\n", inet_ntoa(ClientAddr->sin_addr), ntohs(ClientAddr->sin_port) );
	printf("�ͻ��� %s:%d ��Ϣ��%s.\n", inet_ntoa(ClientAddr->sin_addr), ntohs(ClientAddr->sin_port),pIoContext->m_wsaBuf.buf );


	// 2. ������Ҫע�⣬���ﴫ��������ListenSocket�ϵ�Context�����Context���ǻ���Ҫ���ڼ�����һ������
	// �����һ���Ҫ��ListenSocket�ϵ�Context���Ƴ���һ��Ϊ�������Socket�½�һ��SocketContext

	PER_SOCKET_CONTEXT* pNewSocketContext = new PER_SOCKET_CONTEXT;
	pNewSocketContext->m_Socket           = pIoContext->m_sockAccept;
	memcpy(&(pNewSocketContext->m_ClientAddr), ClientAddr, sizeof(SOCKADDR_IN));

	// ����������ϣ������Socket����ɶ˿ڰ�(��Ҳ��һ���ؼ�����)
	if( false==this->AssociateWithIOCP( pNewSocketContext ) )
	{
		RELEASE( pNewSocketContext );
		return false;
	}  


	// 3. �������������µ�IoContext�����������Socket��Ͷ�ݵ�һ��Recv��������
	PER_IO_CONTEXT* pNewIoContext = pNewSocketContext->GetNewIoContext();
	pNewIoContext->m_OpType       = RECV_POSTED;
	pNewIoContext->m_sockAccept   = pNewSocketContext->m_Socket;
	// ���Buffer��Ҫ���������Լ�����һ�ݳ���
	//memcpy( pNewIoContext->m_szBuffer,pIoContext->m_szBuffer,MAX_BUFFER_LEN );

	// �����֮�󣬾Ϳ��Կ�ʼ�����Socket��Ͷ�����������
	if( false==this->PostRecv( pNewIoContext) )
	{
		pNewSocketContext->RemoveContext( pNewIoContext );
		return false;
	}

	// 4. ���Ͷ�ݳɹ�����ô�Ͱ������Ч�Ŀͻ�����Ϣ�����뵽ContextList��ȥ(��Ҫͳһ���������ͷ���Դ)
	this->AddToContextList( pNewSocketContext );

	// 5. ʹ�����֮�󣬰�Listen Socket���Ǹ�IoContext���ã�Ȼ��׼��Ͷ���µ�AcceptEx
	pIoContext->ResetBuffer();
	return this->PostAccept( pIoContext ); 	
}

////////////////////////////////////////////////////////////////////
// Ͷ�ݽ�����������
bool CIOCPModel::PostRecv( PER_IO_CONTEXT* pIoContext )
{
	// ��ʼ������
	DWORD dwFlags = 0;
	DWORD dwBytes = 0;
	WSABUF *p_wbuf   = &pIoContext->m_wsaBuf;
	OVERLAPPED *p_ol = &pIoContext->m_Overlapped;

	pIoContext->ResetBuffer();
	pIoContext->m_OpType = RECV_POSTED;

	// ��ʼ����ɺ󣬣�Ͷ��WSARecv����
	int nBytesRecv = WSARecv( pIoContext->m_sockAccept, p_wbuf, 1, &dwBytes, &dwFlags, p_ol, NULL );

	// �������ֵ���󣬲��Ҵ���Ĵ��벢����Pending�Ļ����Ǿ�˵������ص�����ʧ����
	if ((SOCKET_ERROR == nBytesRecv) && (WSA_IO_PENDING != WSAGetLastError()))
	{
		printf("Ͷ�ݵ�һ��WSARecvʧ�ܣ�\n");
		return false;
	}
	return true;
}

// ���н��յ����ݵ����ʱ�򣬽��д���
bool CIOCPModel::DoRecv( PER_SOCKET_CONTEXT* pSocketContext, PER_IO_CONTEXT* pIoContext )
{
	// �Ȱ���һ�ε�������ʾ���֣�Ȼ�������״̬��������һ��Recv����
	SOCKADDR_IN* ClientAddr = &pSocketContext->m_ClientAddr;
	printf("�յ�  %s:%d ��Ϣ��%s\n", inet_ntoa(ClientAddr->sin_addr), 
                     ntohs(ClientAddr->sin_port), pIoContext->m_wsaBuf.buf );

	// Ȼ��ʼͶ����һ��WSARecv����
	return PostRecv( pIoContext );
}

// �����(Socket)�󶨵���ɶ˿���
bool CIOCPModel::AssociateWithIOCP( PER_SOCKET_CONTEXT *pContext )
{
	// �����ںͿͻ���ͨ�ŵ�SOCKET�󶨵���ɶ˿���
	HANDLE hTemp = CreateIoCompletionPort((HANDLE)pContext->m_Socket, hIOCompletionPort, (DWORD)pContext, 0);

	if (NULL == hTemp)
	{
		printf(("ִ��CreateIoCompletionPort()���ִ���.������룺%d\n"),GetLastError());
		return false;
	}

	return true;
}

// ���ͻ��˵������Ϣ�洢��������
void CIOCPModel::AddToContextList(PER_SOCKET_CONTEXT *pHandleData)
{
	EnterCriticalSection(&csContextList);

	vecClientContext.push_back(pHandleData);	
	
	LeaveCriticalSection(&csContextList);
}

//	�Ƴ�ĳ���ض���Context
void CIOCPModel::RemoveContext( PER_SOCKET_CONTEXT *pSocketContext )
{
	EnterCriticalSection(&csContextList);

  std::vector<PER_SOCKET_CONTEXT*>::iterator it = vecClientContext.begin();
  for (;it != vecClientContext.end(); ++it)
  {
    if( pSocketContext == *it )
    {
      RELEASE( pSocketContext );			
      vecClientContext.erase(it);
      break;
    }
  }

	LeaveCriticalSection(&csContextList);
}

// ��տͻ�����Ϣ
void CIOCPModel::ClearContextList()
{
	EnterCriticalSection(&csContextList);

  std::vector<PER_SOCKET_CONTEXT*>::iterator it = vecClientContext.begin();
  for (;it != vecClientContext.end(); ++it)
  {
    delete *it;
  }
  vecClientContext.clear();

	LeaveCriticalSection(&csContextList);
}

// ��ñ�����IP��ַ
std::string CIOCPModel::GetLocalIP()
{
	// ��ñ���������
	char hostname[MAX_PATH] = {0};
	gethostname(hostname,MAX_PATH);                
	struct hostent FAR* lpHostEnt = gethostbyname(hostname);
	if(lpHostEnt == NULL)
	{
		return DEFAULT_IP;
	}

	// ȡ��IP��ַ�б��еĵ�һ��Ϊ���ص�IP(��Ϊһ̨�������ܻ�󶨶��IP)
	LPSTR lpAddr = lpHostEnt->h_addr_list[0];      

	// ��IP��ַת�����ַ�����ʽ
	struct in_addr inAddr;
	memmove(&inAddr,lpAddr,4);
	//m_strIP = CString( inet_ntoa(inAddr) );
  strIP.append(inet_ntoa(inAddr));

	return strIP;
}

// ��ñ����д�����������
int CIOCPModel::GetNoOfProcessors()
{
	SYSTEM_INFO si;

	GetSystemInfo(&si);

	return si.dwNumberOfProcessors;
}

// ������������ʾ��ʾ��Ϣ
void CIOCPModel::ShowMessage(const std::string szFormat,...) const
{
	// ���ݴ���Ĳ�����ʽ���ַ���
	std::string   strMessage;
	va_list   arglist;

	// ����䳤����
	va_start(arglist, szFormat);
	//strMessage.FormatV(szFormat,arglist);
  vprintf(szFormat.c_str(), arglist);
	va_end(arglist);

  ///TODO ��Ϣ����Ĳ���û�к���
  std::cout<<"message: "<<szFormat<<std::endl;
}

/////////////////////////////////////////////////////////////////////
// �жϿͻ���Socket�Ƿ��Ѿ��Ͽ���������һ����Ч��Socket��Ͷ��WSARecv����������쳣
// ʹ�õķ����ǳ��������socket�������ݣ��ж����socket���õķ���ֵ
// ��Ϊ����ͻ��������쳣�Ͽ�(����ͻ��˱������߰ε����ߵ�)��ʱ�򣬷����������޷��յ��ͻ��˶Ͽ���֪ͨ��
bool CIOCPModel::IsSocketAlive(SOCKET s)
{
	int nByteSent = send(s, "", 0, 0);
	if (-1 == nByteSent) {
    return false;
  }

	return true;
}

// ��ʾ��������ɶ˿��ϵĴ���
bool CIOCPModel::HandleError(PER_SOCKET_CONTEXT *pContext)
{
  DWORD dwErr = GetLastError();
  switch(dwErr) {
  case WAIT_TIMEOUT: // ��ʱ�������ȴ�
    {
      // ȷ�Ͽͻ����Ƿ񻹻���...
      if( !IsSocketAlive( pContext->m_Socket) )
      {
        printf( "��⵽�ͻ����쳣�˳���\n");
        this->RemoveContext( pContext );
        return true;
      } else {
        printf( "���������ʱ��������...\n");
        return true;
      }
    }
  case ERROR_NETNAME_DELETED:
    {
      // �����ǿͻ����쳣�˳���
      printf( "��⵽�ͻ����쳣�˳���\n");
      this->RemoveContext( pContext );
      return true;
    }
  default:
    {
      printf( "��ɶ˿ڲ������ִ����߳��˳���������룺%d\n",dwErr );
      return false;
    }
  }
}
#include <Windows.h>
#include <mysql.h>
#include <winsock.h>

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

//=============================DB����===========================================

class DB_managment {
public:
  DB_managment() : conn(NULL), res(NULL) { databaseName.append("test"); }
  ~DB_managment() {}

  int init(std::string userName, std::string pwd, std::string loginIp,
           int loginPort) {
    //��ʼ��
    conn = mysql_init(0);

    if (conn == NULL) {
      return -1;
    }

    //�������ݿ�
    if (!mysql_real_connect(conn, loginIp.c_str(), userName.c_str(),
                            pwd.c_str(), databaseName.c_str(), loginPort, NULL,
                            0)) {
      return -1;
    }
    conn->reconnect = 1;
    return 0;
  }

  int choose_database() {
    if (mysql_select_db(conn, databaseName.c_str())) {
      return -1;
    }
    return 0;
  }

  int run_search(const std::string &strSql) {
    if (conn == NULL) {
      return -1;
    }

    //ִ�в�ѯ
    if (mysql_real_query(conn, strSql.c_str(), strSql.size())) {///TODOż������
      // ��ѯ����
      return -1;
    }

    ///TODO ����mysql��ѯ���ݴ���
    //��ȡ���ؽ��
    res = mysql_store_result(conn); ///TODO ż������

    while(row = mysql_fetch_row(res)) {
      std::cout<<"һ�м�¼: ";
      for(unsigned int j=0; j < mysql_num_fields(res); ++j)  
      {  
        std::cout << row[j] << " ";
      }
      std::cout<<"down."<<std::endl;
      Sleep(20);
    }

    mysql_free_result(res);
    std::cout<<"search table down."<<std::endl<<std::endl;
    return 0;
  }

  int run_insert(const std::string &strSql) {
    if (conn == NULL || strSql.empty()) {
      return -1;
    }

    //ִ�в�ѯ
    if (mysql_real_query(conn, strSql.c_str(), strSql.size())) {
      // ��ѯ����
      return -1;
    }
    return 0;
  }

  void print_errcode() {
    //?����ô�������ʾ�������ĺ���
    std::cout << "handle execute err,err_code:" << mysql_errno(conn) << std::endl;
  }

  MYSQL *conn;
  MYSQL_RES *res;
  MYSQL_ROW row;
  std::string databaseName;
};

//=============================�̺߳���==========================================

DWORD WINAPI addSomeDatas(LPVOID lpParameter) {
  DB_managment *p_db_3306 = static_cast<DB_managment *>(lpParameter);

  std::stringstream strSql;
  for (int i = 0; i < 1000; i++) {
    strSql << "insert into test values(" << i << ", " << i << i << i << ")";
    if (p_db_3306->run_insert(strSql.str())) {
      p_db_3306->print_errcode();
    }
    strSql.str("");
  }
  return 0L;
}

DWORD WINAPI getDatas(LPVOID lpParameter) {
  DB_managment *p_db_3306 = static_cast<DB_managment *>(lpParameter);

  std::stringstream strSql;
  while (true) {
    strSql << "select * from test";
    if (p_db_3306->run_search(strSql.str())) {
      p_db_3306->print_errcode();
    }
    strSql.str("");

    Sleep(1000);
  }
  return 0L;
}

//=============================IO===============================================

class IO {
public:
  IO() {}
  ~IO() {}

  void readFileContent(const std::string fileName) {
    std::ifstream file(fileName);
    std::string s;
    while (file >> s) {
      std::cout << "ch : " << s << std::endl;
    }
  }

  void saveContentToFile(const std::string fileName) {
    std::fstream file(fileName,
                      std::fstream::in | std::fstream::out | std::fstream::app);
    file << "lin";
    file.close();
  }
};

//=============================����==========================================

class worker {
public:
  worker() : bInitRes(false) {
    if (db_3306.init("root", "", "127.0.0.1", 3306)) {
      db_3306.print_errcode();
    }
    bInitRes = true;
  }
  ~worker() {}

  void chooseDatabase() {
    if (bInitRes && db_3306.choose_database()) {
      db_3306.print_errcode();
    }
  }

  void run_thread() {
    if (!bInitRes) {
      return;
    }

    HANDLE thread1 = CreateThread(NULL, 0, addSomeDatas, &db_3306, 0, NULL);
    HANDLE thread2 = CreateThread(NULL, 0, getDatas, &db_3306, 0, NULL);
    WaitForSingleObject(thread1, INFINITE);
    WaitForSingleObject(thread2, INFINITE);

    CloseHandle(thread1);
    CloseHandle(thread2);
  }

private:
  DB_managment db_3306;
  bool bInitRes;
};
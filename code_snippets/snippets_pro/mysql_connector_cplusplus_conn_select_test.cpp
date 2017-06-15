//mysql-connector-c++  ����/��ѯmysql
//��ʱ�õ�3rd������Ķ�̬����б���

//ʹ��lib��  F:\Work\3rd\mysql-connector-c++\build\driver\Debug

#include <driver/mysql_connection.h> 
#include <cppconn/driver.h> 
#include <cppconn/exception.h> 
#include <cppconn/resultset.h> 
#include <cppconn/statement.h>
using namespace std;

int main()
{
  // TODO ָ�붼û�����ó�ֵ������
  try { 
    sql::Driver *driver; 
    sql::Connection *con; 
    sql::Statement *stmt; 
    sql::ResultSet *res; 
    sql::PreparedStatement *pstmt;

    driver = get_driver_instance(); 
    con = driver->connect("localhost", "root", ""); 
    //ѡ��Ҫ���ӵ����ݿ� 
    con->setSchema("test");
    //�����ַ���ʽ
    con->setClientOption("characterSetResults", "utf8");
    stmt = con->createStatement(); 
    res = stmt->executeQuery("SELECT * from test1"); 
    //��������� 
    while (res->next())  
    { 
      //�����ID��user���е��ֶ���
      int id = res->getInt("ID");
      cout<<id<<endl;


    }
    delete res; 
    delete stmt;
    delete con; 
  } catch (sql::SQLException &e) { 
    //���쳣������£�����쳣 
    cout << "# ERR: SQLException in " << __FILE__; 
    cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl; 
    cout << "# ERR: " << e.what(); 
    cout << " (MySQL error code: " << e.getErrorCode(); 
    cout << ", SQLState: " << e.getSQLState() << " )" << endl; 
  }

  return 0;
}
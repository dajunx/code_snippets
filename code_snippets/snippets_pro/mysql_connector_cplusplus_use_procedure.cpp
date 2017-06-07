// mysql-connector-c++ ִ��/��ѯ�洢����
#include <driver/mysql_connection.h> 
#include <cppconn/driver.h> 
#include <cppconn/exception.h> 
#include <cppconn/resultset.h> 
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
using namespace std;

int main()
{
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

    //ִ�д洢����
    pstmt = con->prepareStatement("call proc_adder(1, 5, @sum)");
    pstmt->execute();
    //or below
    //pstmt = con->prepareStatement("call proc_adder(?, ?, @sum)");
    //pstmt->setInt(1, 1);
    //pstmt->setInt(2, 5);
    //pstmt->execute();

    //��ѯ�洢���̽��
    pstmt = con->prepareStatement("select @sum as sum");
    res = pstmt->executeQuery();
    //��������� 
    while (res->next())  
    { 
      int id = res->getUInt64(1);
      cout<<id<<endl;
    }

    delete res; 
    //delete stmt;
    delete pstmt;
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
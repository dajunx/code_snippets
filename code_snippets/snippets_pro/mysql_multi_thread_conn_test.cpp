//mysql-connector-c++  ����/��ѯmysql
//��ʱ�õ�3rd������Ķ�̬����б���

//ʹ��lib��  F:\Work\3rd\mysql-connector-c++\build\driver\Debug

#include <driver/mysql_connection.h> 
#include <cppconn/driver.h> 
#include <cppconn/exception.h> 
#include <cppconn/resultset.h> 
#include <cppconn/statement.h>
//#include <cppconn/connection.h>
#include <cppconn/prepared_statement.h>

#include <iostream>
#include <string>
#include <map>
#include <fstream>

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std;

void read_sql_from_disk_file(std::string& str_sql)
{
  std::ifstream fin("file.txt");  
  while(getline(fin, str_sql))
  {    
    std::cout<<"Read from file into string: "<<str_sql<<std::endl; 
  }
}

void write_data_to_disk_file(std::string& save_file_name, std::string& save_data)
{
  //std::cout<<cost.total_milliseconds()<<"ms"<<std::endl;
  std::fstream file(save_file_name,
    std::fstream::in | std::fstream::out | std::fstream::app);
  file<<save_data;
  file.close();
}

void insert_data_2_mysql(int i)
{
  boost::this_thread::sleep(boost::posix_time::seconds(2));
  try { 
    sql::Driver *driver; 
    sql::Connection *con; 
    sql::Statement *stmt; 
    //sql::ResultSet *res; 
    //sql::PreparedStatement *pstmt;

    driver = get_driver_instance(); 
    con = driver->connect("192.168.221.133", "linjj", "19900801"); 
    //ѡ��Ҫ���ӵ����ݿ� 
    con->setSchema("test");
    //�����ַ���ʽ
    con->setClientOption("characterSetResults", "utf8");
    stmt = con->createStatement(); 

    std::string str_sql, str_sql_tmp;
    read_sql_from_disk_file(str_sql);
    for(int index=0; index < 10000; ++index)
    {
      str_sql_tmp = str_sql;
      int iBegin = i * 10000 + index;
      std::stringstream uid;
      uid<<iBegin;
      str_sql_tmp.append(uid.str());
      str_sql_tmp.append(", \"");
      str_sql_tmp.append(uid.str());
      str_sql_tmp.append("\")");
      stmt->execute(str_sql_tmp);
      //boost::this_thread::sleep(boost::posix_time::millisec(10)); // ÿ����¼����ǰ���10ms����������Ƿ��mysql�г��
    }

    std::cout<<"thread: "<<i<<std::endl;
    //boost::this_thread::sleep(boost::posix_time::seconds(200));

    //delete res; 
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
}

//TODO ��Ӧ�Ĵ洢���̺ͽ����һ�£�����ʹ���޸�
void call_procedure(int i)
{
  boost::this_thread::sleep(boost::posix_time::seconds(2));
  try { 
    sql::Driver *driver; 
    sql::Connection *con; 
    sql::PreparedStatement *pstmt;
    sql::ResultSet * res;  //���ڴ洢���̷��ؽ��

    driver = get_driver_instance(); 
    con = driver->connect("192.168.221.136", "linjj", "19900801");
    //ѡ��Ҫ���ӵ����ݿ� 
    con->setSchema("test");
    //�����ַ���ʽ
    con->setClientOption("characterSetResults", "utf8");

    //ִ�д洢����
    std::stringstream str_id;
    str_id<<i;
    std::string sql_text("call insert_test_data(");
    sql_text.append(str_id.str());
    sql_text.append(")");

    pstmt = con->prepareStatement(sql_text);
    pstmt->execute();

    /*����ʹ��
    std::string sql_text("call insert_test_data(?)");

    pstmt = con->prepareStatement(sql_text);
    pstmt->setInt(1, i);
    */


    //�����洢���̵Ľ��(�����洢�����е�select ���ػ��� �洢���̲����Ĵ���[ʹ�� show errors; ])
    do {
      res = pstmt->getResultSet();
      while (res->next()) {
        std::cout << "id: " << res->getInt("id")
          << " name: " << res->getString("name") << std::endl;
      }
    } while (pstmt->getMoreResults());

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
}

void get_record_from_mysql()
{
  try { 
    sql::Driver *driver; 
    sql::Connection *con; 
    sql::Statement *stmt; 
    sql::ResultSet *res; 
    //sql::PreparedStatement *pstmt;
    std::map<int, std::string> map_data;
    std::string save_file_name("get_record_from_mysql.192.168.221.135.txt");
    std::stringstream data;

    driver = get_driver_instance(); 
    con = driver->connect("192.168.221.135", "linjj", "19900801"); 
    //ѡ��Ҫ���ӵ����ݿ� 
    con->setSchema("test");
    //�����ַ���ʽ
    con->setClientOption("characterSetResults", "utf8");
    stmt = con->createStatement(); 
    res = stmt->executeQuery("select uid, name from test1");
    while (res->next()) {//������д���ڴ棬��һ����д�����
      int uid = res->getInt("uid");
      std::string name = res->getString("name");
      data<<uid<<"\n";
      data<<name<<"\n";
      //map_data.insert(std::pair<int, std::string>(uid, name));
      //std::cout<<"record, uid: "<<uid<<", name: "<<name<<std::endl;
    }

    write_data_to_disk_file(save_file_name, data.str());

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
}

class action_record_time
{
public:
  action_record_time() {
    start = boost::posix_time::microsec_clock::local_time();
  }
  ~action_record_time() {
    end = boost::posix_time::microsec_clock::local_time();

    boost::posix_time::time_duration cost = end - start;

    std::stringstream str_cost_time;
    std::string file_name("cost_time.txt");
    str_cost_time<<cost.total_milliseconds()<<"ms";
    write_data_to_disk_file(file_name, str_cost_time.str());
  }

public:
  boost::posix_time::ptime start, end;
};

int main()
{
  // һ�����߳�д�����⡢���̶߳�ȡ���ݲ�download������
  {
    action_record_time dr;
    boost::thread th_read(boost::bind(get_record_from_mysql));
    th_read.join();
    //get_record_from_mysql();
  }

  {
    action_record_time dr;
    boost::thread_group thread_group;
    for(int i=0; i < 800; ++i)
    {
      thread_group.create_thread(boost::bind(&call_procedure, i));
      boost::this_thread::sleep(boost::posix_time::milliseconds(50));
    }
    thread_group.join_all();
  }

  boost::this_thread::sleep(boost::posix_time::seconds(5));
  return 0;
}
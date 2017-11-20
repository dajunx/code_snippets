//Observer ģʽ ������
#include <iostream>  
#include <vector>  
#include <string>  
using namespace std;  
class Secretary;  
// ����Ʊ��ͬ���ࣨ�۲���󣬹۲��ߣ�  
class StockObserver  
{  
public:  
  StockObserver(string strName, Secretary* strSub)  
  {  
    name = strName;  
    sub = strSub;  
  }  

  void Update();  
private:  
  string name;  
  Secretary* sub;  
};  

// �����ࣨ�������֪ͨ�ߣ�  
class Secretary  
{  
public:  
  string action;  
  void Add(StockObserver ob) { observers.push_back(ob); }  
  void Remove(int addIndex)  
  {  
    if(addIndex >=0 && addIndex < observers.size())  
      observers.erase(observers.begin() + addIndex);  
  }  
  void Notify()  
  {  
    vector<StockObserver>::iterator it;  
    for (it=observers.begin(); it!=observers.end(); ++it)  
    {  
      (*it).Update();  
    }  
  }  
private:  
  vector<StockObserver> observers;  
};  

void StockObserver::Update()  
{  
  cout << name << " : " << sub->action << ", begin to work" << endl;  
} 
int main()  
{  
  // ����֪ͨ��  
  Secretary* p = new Secretary();  

  // �۲���  
  StockObserver* s1 = new StockObserver("Lazy", p);  
  StockObserver* s2 = new StockObserver("SnowFire", p);  
  // ����֪ͨ����  
  p->Add(*s1);  
  p->Add(*s2);  
  // �¼�  
  p->action = "The boss is coming...";  
  // ֪ͨ  
  p->Notify(); 
  // ��̬ɾ��  
  p->Remove(0);
  p->Notify();  
  return 0;    
}  
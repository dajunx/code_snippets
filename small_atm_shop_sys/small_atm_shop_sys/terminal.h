#ifndef H_TERMINAL_H
#define H_TERMINAL_H

///TODO(linjianjun) 2018.04.05 �ն���γ��󣬺�������˼�����ֻ��ն˺�ATM�ն��ȸ���ʵ��
//class terminal {
//public:
//  terminal() {}
//  ~terminal() {}
//};

class ATM{
public:
  ATM() {}
  ~ATM() {}

  //����
  int borrow_money();

  //����
  int giveBack_money();

  //��ѯATM���������¼
  int scan_ATM_detail();
};

//�ֻ��ն���ʱ��֧�֣�1�����ÿ���Ǯ��2�������ÿ��� �ȼ��ն˹��ܣ���������˼����չ��
class phone
{
public:
  phone() {}
  ~phone() {}

  //����
  int spend_money();

  //ת��
  int exchange_money();

  //��ѯ�ֻ��ն˲�����ˮ
  int scan_phone_detail();
};

#endif

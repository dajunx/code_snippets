package main

import "fmt"

//����ָ��汾 func fun1(t bool, i* int) *int {
func fun1(t bool, i* int) int {
    switch {
    case t == false:
        *i--;
        fmt.Println("call --")
    case t == true:
        *i++;
        fmt.Println("call ++")
    default:
        fmt.Println("nothing")
    }   

    //fmt.Println("i value:", *i)
    return *i
}

func main() {
    //defer �����ӳٺ�����ִ��ֱ���ϲ㺯�����ء�
    // �ӳٵ��õĲ������������ɣ��������ϲ㺯������ǰ���������ᱻ����
    // �ӳٵĺ������ñ�ѹ��һ��ջ�С�����������ʱ�� �ᰴ�պ���ȳ���˳����ñ��ӳٵĺ�������
    i := 1
    defer fmt.Println("i value:", fun1(false, &i), ", type --")
    fmt.Println("i value:", fun1(true, &i), ", type ++")
}

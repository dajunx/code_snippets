package main

import "fmt"

//һ���ṹ�壨`struct`������һ���ֶεļ���
type Vertex struct {
	X int
	Y int
}

//�ṹ���ķ���ʾͨ���ṹ���ֶε�ֵ��Ϊ�б����·���һ���ṹ�塣
//ʹ�� Name: �﷨���Խ��г������ֶΡ�(�ֶ�����˳���޹ء�)
var (
	v1 = Vertex{1, 2}  // ����Ϊ Vertex
	v2 = Vertex{X: 1}  // Y:0 ��ʡ��
	v3 = Vertex{}      // X:0 �� Y:0
	p  = &Vertex{1, 2} // ����Ϊ *Vertex
)

func main() {
	fmt.Println(Vertex{1, 2})
	v := Vertex{1, 2}
	v.X = 4 //�ṹ���ֶ�ʹ�õ��������
	fmt.Println(v.X)

	//�ṹ���ֶο���ͨ�� �ṹ��ָ��������
	p := &v
	p.X = 1e9
	fmt.Println(v)

	fmt.Println(v1, p, v2, v3)
}
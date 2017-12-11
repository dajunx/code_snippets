package main

import "fmt"

var pow = []int{1, 2, 4, 8, 16, 32, 64, 128}

func main() {
	//for ѭ���� range ��ʽ���Զ� slice ���� map ���е���ѭ��
	for i, v := range pow {
		fmt.Printf("2**%d = %d\n", i, v)
	}

	//����ͨ����ֵ�� _ ��������ź�ֵ�����ֻ��Ҫ����ֵ��ȥ����, value���Ĳ��ּ���
	for i := range pow {
		fmt.Println("pos value:", i)
	}
	for _, value := range pow {
		fmt.Printf("%d\n", value)
	}
}
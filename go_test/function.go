package main

import "fmt"

//���溯��
func add1(x int, y int) int {
	return x + y
}

//ʡ�Ժ�����������
func add2(x, y int) int {
	return x - y
}

//�෵��ֵ
func swap(x, y string) (string, string) {
	return y, x
}

//�������أ�return ��䷵�ؽ���ĵ�ǰֵ
func split(sum int) (x, y int) {
	x = sum * 4 / 9
	y = sum - x
	return
}

func main() {
	fmt.Println(add1(42, 13))
	fmt.Println(add2(42, 13))
	fmt.Println(swap(42,13))
	fmt.Println(split(42))
}
package main

import "fmt"

func main() {
	// ���ʽ var a [10]int
	// ����ĳ����������͵�һ���֣�������鲻�ܸı��С
	var a [2]string
	a[0] = "Hello"
	a[1] = "World"
	fmt.Println(a[0], a[1])
	fmt.Println(a)
}
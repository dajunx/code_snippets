package main

import (
	"fmt"
	"math/cmplx"
	)

//`var` �����Զ����ڰ���������
// ע�⺯����������ں�����ʼ�� ����
// �����ⶨ����������� var��ͷ���Ҳ���ʹ�� := �ṹ
//var c, python, java bool
var c, python, java bool = true, false, false

//���岢��ʼ���������
var (
	ToBe   bool       = false
	MaxInt uint64     = 1<<64 - 1
	z      complex128 = cmplx.Sqrt(-5 + 12i)
)

func main() {
	//var i int
	//i := 999 //������������������ȷ�������͵ĵط�
	var i int = 999
	fmt.Println(i, c, python, java)
	const f = "%T(%v)\n"
	fmt.Printf(f, ToBe, ToBe)
	fmt.Printf(f, MaxInt, MaxInt)
	fmt.Printf(f, z, z)
}

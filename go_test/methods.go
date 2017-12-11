package main

import (
	"fmt"
	"math"
)

type Vertex struct {
	X, Y float64
}

//����
//���������� ������ func �ؼ��ֺͷ�����֮��Ĳ�����
func (v *Vertex) Abs1() float64 {
	return math.Sqrt(v.X*v.X + v.Y*v.Y)
}

//���Զ԰��е� ���� ���Ͷ������ⷽ����������������Խṹ��
//���ǣ����ܶ����������������ͻ�������Ͷ��巽��
type MyFloat float64
func (f MyFloat) Abs2() float64 {
	if f < 0 {
		return float64(-f)
	}
	return float64(f)
}

func main() {
	v := &Vertex{3, 4}
	fmt.Println(v.Abs1())
	f := MyFloat(-math.Sqrt2)
	fmt.Println(f.Abs2())
}
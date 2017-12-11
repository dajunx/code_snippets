package main

import (
	"fmt"
	"math"
)

// ��c��if�����ƣ�ֻ��û��С����
func sqrt(x float64) string {
	if x < 0 {
		return sqrt(-x) + "i"
	}
	return fmt.Sprint(math.Sqrt(x))
}

//����������֮ǰִ��һ���򵥵���䡣
// �������䶨��ı�������������� if ��Χ֮�ڡ�
// �� if �ı����䶨��ı���ͬ���������κζ�Ӧ�� else ����ʹ��
func pow(x, n, lim float64) float64 {
	if v := math.Pow(x, n); v < lim {
		return v
	} else {
		fmt.Printf("%g >= %g\n", v, lim)
	}
	// ���� v �Ѿ��޷�ʹ��
	return lim
}

func main() {
	fmt.Println(sqrt(2), sqrt(-4))
	fmt.Println(
		pow(3, 2, 10),
		pow(3, 3, 20),
	)
}
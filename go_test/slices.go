package main

import "fmt"

//slice �ɺ��� make ������������һ���㳤�ȵ����鲢�ҷ���һ�� slice ָ���������
func newSlice() {
    a := make([]int, 5)
    printSlice("a", a)
    b := make([]int, 0, 5)
    printSlice("b", b)
    c := b[:2]
    printSlice("c", c)
    d := c[2:5]
    printSlice("d", d)
}

//slice ����ֵ�� `nil`��һ�� nil �� slice �ĳ��Ⱥ������� 0
func nilSlice() {
	var z []int
	fmt.Println(z, len(z), cap(z))
	if z == nil {
		fmt.Println("nil!")
	}
}

func printSlice(s string, x []int) {
    fmt.Printf("%s len=%d cap=%d %v\n",
        s, len(x), cap(x), x)
}

//���Ԫ��
func appendDataToSlice() {
	var a []int
	printSlice("a", a)

	// append works on nil slices.
	a = append(a, 0)
	printSlice("a", a)

	// the slice grows as needed.
	a = append(a, 1)
	printSlice("a", a)

	// we can add more than one element at a time.
	a = append(a, 2, 3, 4)
	printSlice("a", a)
}

func main() {
    //һ�� slice ��ָ��һ�����е�ֵ�����Ұ����˳�����Ϣ
    p := []int{2, 3, 5, 7, 11, 13} 
    fmt.Println("p ==", p)

    // slice �±��0��ʼ����Ƭ������ҿ�
    fmt.Println("p[1:4] ==", p[1:4])
    // ʡ���±����� 0 ��ʼ
    fmt.Println("p[:3] ==", p[:3])
    // ʡ���ϱ���� len(s) ����
    fmt.Println("p[4:] ==", p[4:])

    for i := 0; i < len(p); i++ {
        fmt.Printf("p[%d] == %d\n", i, p[i])
    }   

    fmt.Println("new slice")
    newSlice()

    fmt.Println("nil slice")
    nilSlice()

    fmt.Println("add itmes to slice")
    appendDataToSlice()
}
package main

import (
    "fmt"
    "runtime"
    "time"
)

func testSwitch1() {
    // switch ��ʵ����һ���ֶεļ���
    // ִ��˳���Ǵ��ϵ��µ�ִ�У���ƥ��ɹ���ʱ��ֹͣ
    switch os := runtime.GOOS; os {
    case "darwin":
        fmt.Println("OS X.")
    case "linux":
        fmt.Println("Linux.")
    case "windows":
        fmt.Println("windows.")
	fallthrough //��ֹ��֧�Զ�����
    default:
        // freebsd, openbsd,
        // plan9, windows...
        //fmt.Printf("%s.", os)
        fmt.Printf("step into default case.")
    }  
}

//û�������� switch ͬ `switch true` һ����
// �����ȶ�����case������, c����Ӧ��ûû�����ʹ�÷�ʽ
func noInputSwitchTest() {
	t := time.Now()
	switch {
	case t.Hour() < 12:
		fmt.Println("Good morning!")
	case t.Hour() < 17:
		fmt.Println("Good afternoon.")
	default:
		fmt.Println("Good evening.")
	}
}

func main() {
    fmt.Print("Go runs on ")
    testSwitch1()
    fmt.Println("test no input switch.")
    noInputSwitchTest()
}
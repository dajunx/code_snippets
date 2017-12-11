package main

import "fmt"

type Vertex struct {
    Lat, Long float64
}
//map ����
var m map[string]Vertex

var n = map[string]Vertex{
    "Bell Labs": Vertex{
        40.68433, -74.39967,
    },  
    "Google": Vertex{
        37.42202, -122.08408,
    },  
}

//�޸�map�е�ֵ
func modifyMapItem(m map[string]Vertex) {
    m["Answer"] = Vertex{42,0}
    fmt.Println("The value:", m["Answer"])

    //�����޸�ֵ
    m["Answer"] = Vertex{48,0}
    fmt.Println("The value:", m["Answer"])

    //ɾ��
    delete(m, "Answer")
    fmt.Println("The value:", m["Answer"])

    v, ok := m["Answer"]
    fmt.Println("The value:", v, "Present?", ok) 
}

func main() {
    //map ��ʹ��֮ǰ������ make ������ new ��������ֵΪ nil �� map �ǿյģ����Ҳ��ܸ�ֵ
    m = make(map[string]Vertex)
    m["Bell Labs"] = Vertex{
        40.68433, -74.39967,
    }   
    fmt.Println(m["Bell Labs"])

    //map ���ķ����ṹ���ķ����ƣ����������м���
    fmt.Println(n)

    fmt.Println("modify m map data")
    modifyMapItem(m)
}
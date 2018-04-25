package main

import (
	"compress/gzip"
	"fmt"
	"io"
	"io/ioutil"
	"net/http"
	"strconv"
)

func webGetAction(url string) []byte {
	client := &http.Client{
		CheckRedirect: nil,
	}
	reqest, _ := http.NewRequest("GET", url, nil)

	reqest.Header.Set("User-Agent", " Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/31.0.1650.63 Safari/537.36")
	reqest.Header.Set("Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8")
	reqest.Header.Set("Accept-Charset", "GBK,utf-8;q=0.7,*;q=0.3")
	reqest.Header.Set("Accept-Encoding", "gzip,deflate,sdch")
	reqest.Header.Set("Accept-Language", "zh-CN,zh;q=0.8")
	reqest.Header.Set("Cache-Control", "max-age=0")
	reqest.Header.Set("Connection", "keep-alive")
	reqest.Header.Set("Referer", url)

	resp, err := client.Do(reqest)
	if err != nil {
		fmt.Println(url, err)
		return nil
	}

	defer resp.Body.Close()
	var reader io.ReadCloser
	switch resp.Header.Get("Content-Encoding") {
	case "gzip":
		reader, err = gzip.NewReader(resp.Body)
		if err != nil {
			fmt.Println(url, err)
			return nil
		}
		defer reader.Close()
	default:
		reader = resp.Body
	}

	if reader != nil {
		body, err := ioutil.ReadAll(reader)
		if err != nil {
			fmt.Println(url, err)
			return nil
		}
		return body
	}
	return nil
}

func testGetJSONFromLocalFile() {
	//URLTemp := "http://localhost/test/a_json_file.php" //本地wampserver启动服务提供json文件访问
	URLTemp := "http://127.0.0.1:9999/ReadMe.txt" //本地c++ 编写的web服务器
	resp, err := http.Get(URLTemp)
	if err != nil {
		//
	}
	defer resp.Body.Close()
	body, err := ioutil.ReadAll(resp.Body)
	if err != nil {
		//
	}
	fmt.Println(string(body))
}

func downloadSongJSON(songID int) bool {
	var ret bool
	URLTemp := "http://music.163.com/api/v1/resource/comments/R_SO_4_"
	URLTemp += strconv.Itoa(songID)
	fmt.Println(URLTemp)

	res := webGetAction(URLTemp) //模拟web get 操作
	fmt.Println(string(res))
	//如下方式会被正式网站判定非法请求
	/*
		resp, err := http.Get(URLTemp)
		if err != nil {
			ret = false
		}
		defer resp.Body.Close()
		body, err := ioutil.ReadAll(resp.Body)
		if err != nil {
			ret = false
		}
		fmt.Println(string(body))
	*/

	return ret
}

//获取网易真实存在的个数连接
func main() {
	//testGetJSONFromLocalFile()
	// 网易歌曲原始播放地址，含有评论
	songURL := "https://music.163.com/#/song?id="

	//遍历歌曲
	songIDBegin := 306665
	songIDEnd := songIDBegin + 0
	songID := songIDBegin
	for i := songIDBegin; i <= songIDEnd; i++ {
		//time.Sleep(time.Second * 2)

		res := downloadSongJSON(songID)
		if res == true {
			fmt.Println(songURL + strconv.Itoa(songID))
		}
	}

}

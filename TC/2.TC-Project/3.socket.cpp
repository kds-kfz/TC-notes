#include<iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include<stdio.h>

using namespace std;
#define SERVE_PORT 8080

int main(int argc, char *argv[]){
    int lfd; //原始套接字
    int cfd; //新套接字
    char buf[256]; //使用新套接熊套接字读取数据，将数据保存在buf里
    char  ip_buf[INET_ADDRSTRLEN]; //将网络ip地址字节序转换成主机ip字节序的文本字符串
    struct sockaddr_in saddr; //服务端结构体，保存通信特性，和指定的主机地址和端口
    struct sockaddr_in caddr; //缓存网络字节序中客户端的ip地址和端口
    socklen_t c_len; // 定义服务端相应客户端后，保存客户端信息的socket_in 结构体大小
    //socklen_t 是数据类型

    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(SERVE_PORT);
    inet_pton(AF_INET, "127.0.0.1", &saddr.sin_addr.s_addr);

    //创建套接字
    lfd = socket(AF_INET, SOCK_STREAM, 0);
    int ret = bind(lfd, (struct sockaddr *)&saddr, sizeof(saddr));

    //监听
    listen(lfd, 20);
    c_len = sizeof(caddr); //将大小设置为足够大的缓存区填充客户端的地址

    cout<<"等待客户端连接..."<<endl;
    //阻塞等待客户端连接
    cfd = accept(lfd, (struct sockaddr *)&caddr, &c_len);

    cout<<"服务端相应"<<endl;
    printf("client : ip[%s], port[%d]", 
        inet_ntop(AF_INET, &caddr.sin_addr.s_addr, ip_buf, INET_ADDRSTRLEN),
        ntohs(caddr.sin_port));

    while(1){
        ret = read(cfd, buf, sizeof(buf));
        if(ret == 0){
            cout<<"服务端断开连接"<<endl;
        }

        ret = write(STDOUT_FILENO, buf, ret);
        write(cfd, "I am client", sizeof("I am client"));
    }

    return 0;
}

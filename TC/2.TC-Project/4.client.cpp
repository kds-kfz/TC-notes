#include<iostream>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<strings.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

using namespace std;

int main(int argc, char *argv[]){
    if(argc < 3){
        cout<<"./client less"<<endl;
        exit(-1);
    }

    int cfd;
    int ret;
    char buf[80];
    struct sockaddr_in saddr;

    cfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&saddr, sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(atoi(argv[2]));
    inet_pton(cfd, argv[1], &saddr.sin_addr.s_addr);

    //建立连接
    connect(cfd, (struct sockaddr *)&saddr, sizeof(saddr));
    cout<<"客户端连接到服务器成功"<<endl;

    while(1){
        ret = read(STDIN_FILENO, buf, sizeof(buf));
        if(ret < 0){
            cout<<"read error"<<endl;
            exit(-1);
        }

        ret = write(cfd, buf, ret);
        if(ret < 0){
            cout<<"write error"<<endl;
            exit(-1);
        }

        ret = read(cfd, buf, sizeof(buf));
        cout<<buf<<endl;
    }
    return 0;
}

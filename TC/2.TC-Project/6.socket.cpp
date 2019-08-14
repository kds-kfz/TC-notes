#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <bits/stdc++.h>
#include <pthread.h>

using namespace std;
#define SERVE_PORT 8081

//客户端通信节点
struct info{
    int cfd;
    string type;
    string msg;//type + 内容, 以$符号间隔区分
    struct sockaddr_in caddr;
};

void fun(int a){
    int wai = waitpid(-1, NULL, WNOHANG);
    printf("child pid = %d\n", wai);
}

void *thread_handle(void* arg){
    //设置线程分离，此时系统已经回收了该线程号的资源
    //<该线程终止时底 层资源立即被回收>
    //此时不必再焦勇pthread_join回收资源
    pthread_detach(pthread_self());

    struct info *ts = (struct info *)arg;
    char ip_buf[16] = {0};
    char buf[1024] = {0};
    int ret;
    printf("client ip = [%s], port = [%d], cfd = [%d], pth = [%ld]\n",
            inet_ntop(AF_INET, &(ts->caddr.sin_addr.s_addr), ip_buf, sizeof(ip_buf)),
            ntohs(ts->caddr.sin_port),ts->cfd,
            pthread_self());

    while(1){
        ret = read(ts->cfd, buf, sizeof(buf));
        if(ret == 0){
            cout<<"服务器断开"<<endl;
            return (void *)-1;
        }else if(ret == -1){
            perror("read error\n");
            exit(-1);
        }
        write(STDOUT_FILENO, buf, ret);
        write(ts->cfd, "I am a client", sizeof("I am a client"));
    }
    close(ts->cfd);
    pthread_exit(0);
}

int main(int argc, char *argv[]){
    if(argc < 2){
        cout<<"参数缺少"<<endl;
	    exit(-1);
    }

    int sfd; //原始套接字
    int cfd; //新套接字
    //pid_t pid; //创建子进程
    pthread_t pth; //
    int count = 0;
    char buf[1024] = {0}; //使用新套接熊套接字读取数据，将数据保存在buf里
    char  ip_buf[INET_ADDRSTRLEN]; //将网络ip地址字节序转换成主机ip字节序的文本字符串
    struct sockaddr_in saddr; //服务端结构体，保存通信特性，和指定的主机地址和端口
    struct sockaddr_in caddr; //缓存网络字节序中客户端的ip地址和端口
    //socklen_t c_len; // 定义服务端相应客户端后，保存客户端信息的socket_in 结构体大小
    //socklen_t 是数据类型

    //绑定地址和端口
    bzero(&saddr,sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(atoi(argv[1]));
    inet_pton(AF_INET, "127.0.0.1", &saddr.sin_addr.s_addr);

    //创建套接字
    sfd = socket(AF_INET, SOCK_STREAM, 0);
    int ret = bind(sfd, (struct sockaddr *)&saddr, sizeof(saddr));

    //监听
    listen(sfd, 128);
    //c_len = sizeof(caddr); //将大小设置为足够大的缓存区填充客户端的地址

    struct info ts[256];
    while(1){
        cout<<"等待客户端连接..."<<endl;
        //阻塞等待客户端连接
	    socklen_t c_len=sizeof(caddr);
        cfd = accept(sfd, (struct sockaddr *)&caddr, &c_len);
        
        if(cfd==-1){
    	    printf("accept error\n");
    	    exit(-1);
        }
	    
        ts[count].cfd = cfd;
	    ts[count].caddr = caddr;
    
        cout<<"服务端相应"<<endl;
        /*
        printf("client : ip[%s], port[%d]\n", 
            inet_ntop(AF_INET, &ts[count].caddr.sin_addr.s_addr, ip_buf, INET_ADDRSTRLEN),
            ntohs(ts[count].caddr.sin_port));
        
        if((pid = fork()) == -1){
    	    printf("fork error\n");
    	    exit(-1);
        }else if(pid == 0){// 子进程
            close(sfd);
            printf("child_pid = [%d],father_pid = [%d]\n",getpid(),getppid());//子进程pid 父进程pid
            count--;
            while(1){
                ret = read(ts[count].cfd, buf, sizeof(buf));
                if(ret == 0){
                    cout<<"服务端断开连接"<<endl;
                }else if(ret == -1){
                    cout<<"未曾读取到数据"<<endl;
                    continue;
                }
                string tmp_buf = string(buf);
                if( tmp_buf.find("$") != string::npos ){
                    char *p = NULL;
                    p = strtok(buf,"$");
                    ts[count].type = string(p);
                    p = strtok(NULL, "$");
                    string tt = string(p);
                    ts[count].msg = tt.substr(0, tt.size() - 1);
                }else{
                    write(ts[count].cfd, "数据必须包含$符号", sizeof("数据必须包含$符号"));
                    continue;
                }
                printf("cfd = [%d],type = [%s], msg = [%s]\n",
                        ts[count].cfd, ts[count].type.c_str(), ts[count].msg.c_str());//子进程pid 父进程pid
    
                struct info tmp_ts;
                int tmp_count = 0;
                //查找非自己的房间
                for(int i = 0; i < count + 1; i++){
                    if( i == count ){
                        write(ts[count].cfd, "你是个新房间", sizeof("你是个新房间"));
                    }else if(ts[count].type == ts[i].type){
                        tmp_ts = ts[count];
                        write(tmp_ts.cfd, buf, ret);
                    }
                    // 这2种情况都跳出循，是新房间，或是首次找到相同的房间
                    break;
                }
            }
        }else{
            close(cfd);
            signal(SIGCHLD, fun);
        }
        */

        pthread_create(&pth, NULL, thread_handle, (void *)&ts[count]);
        count++;
	    if(count>=256){
	        break;
        }
        cout<<"count = "<<count<<endl;
    }

    return 0;
}

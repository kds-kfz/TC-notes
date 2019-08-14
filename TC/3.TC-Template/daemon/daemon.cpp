#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<ctype.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<time.h>
#include<fcntl.h>
#include<dirent.h>
#include<string.h>

//#include"zsocket.hpp"

#ifdef __OS_LINUX_VER
#include<sys/sysinfo.h>
#include<sys/wait.h>
#include<dirent.h>
#include<unistd.h>
#endif

#define NODE_INFO "./config/NodeInfo.cfg"

using namespace std;

int stopsrv(char *svname);

int g_dayofyear = -1;

int find_pid_by_name(char *pidNmae, int &first_pid);
int stopsrv(char *svname);

int stopsrv(char *svname){
    int n,pid;
    n = -1;
    while(n > 0){
        char cmd[64];
        n = find_pid_by_name(svname, pid);
        if(n > 0){
            memset(cmd, 0, sizeof(cmd));
            snprintf(cmd, sizeof(cmd), "kill -9 %d",pid);
            system(cmd);
        }else{
            break;
        }
    }
    return 0;
}

int find_pid_by_name(char *pidNmae, int &first_pid){
    #ifdef __OS_LINUX_VER
    DIR *dir;
    struct dirent *next;
    log *pidList = NULL;
    int i = 0;
    dir = opendir("/proc");
    if(!dir){
        fprintf(stderr, "Cannot open /proc\n");
        exit(1);
    }
    
    while((next = readdir(dir)) != NULL){
        FILE *status;
        char filename[READ_BUF_SIZE];
        char buffer[];
        char buffer2[];
        char name[];
        char state[];
        
        if(strcmp(next->d_name, "..") == 0){
            continue;
        }
        if(!isdigit(*next->d_name)){
            continue;
        }
        sprintf(filename, "/proc/%s/status", next->d_name);
        if(!(status = fopen(filename, "r"))){
            continue;
        }
        if(fhets(buffer, READ_BUF_SIZE - 1, status) == NULL){
            fclose(status);
            continue;
        }else{
            if(fgets(buffer2, READ_BUF_SIZE - 1, status) == NULL){
                fclose(status);
                continue;
            }
        }
        fclose(status);
        
        sscanf(buffer, "%s %s",name);
        if(strcmp(name, pidname) == 0){
            if(i == 0){
                first_pid = strol(next->name, NULL, 0);
            }
            if(strstr(buffer2, "zombie") == NULL){
                i++;
            }
        }
    }
    closedir(dir);
    return i;
#else
    return 0;
#endif
}

void init_dameon(){
    int pid, i;
    if(pid = fork()){exit(0);}//父进程退出
    else if(pid < 0){exit(1);}//fork失败
    //进程属于一个进程组，组号是进程组长的进程号PID
    //会话包含多个进程组，都共享一个控制终端
    //这个控制终端通常是创建进程的登录终端
    //控制终端，登录会话和进程组通常从父进程继承下来的
    //使子进程成为新的会话组长和进程组长
    setsid();
    //关闭从父进程继承下来的文件描述符
    //for(i = 0; i < NOFILE, ++i)
    //close(i);
    //改变工作目录到/tmp工作目录到/tmp
    chdir("/tmp");
    //将文件创建掩模清除，从父进程继承了文件创建掩模，
    //可能修改守护进程所创建的文件的存取位
    umask(0);
    //关闭标准输入
    close(0);
    //打开空设备文件
    open("/dev/null", O_RDWR);
    //让标准输出指向空设备文件
    dup2(0, 1);
    //让标准错误指向空设备文件
    dup2(0, 2);
    //请求到来，父进程没有等待子进程处理结束，子进程会变成僵尸进程
    //若等待，则降低进程的并发性
    //signal(SIGCHLD, SIG_IGN);
    return ;
}

int main(){
/*
    FLAGS_log_dir = "./log";//设置log目录
    //初始化，传入程序名
    google::InitGoogleLogging(argv[0]);//初始化
    //设置特定级别日志的输出目录和人前缀
    //第一个参数为日志级别
    //第二个参数为输出目录及日志文件前缀
    google::SetLogDestinat(google::GLOG_INFO, "./log/Daemon-");
    //大于指定级别的日志都输出到标准输出
    google：：SetStderrLogging(google::FATAL);
    //在日志文件名中，级别后增加一个扩展名，适用于所有严重级别
    //google::SetLogFilenameExtension("log_");
    //不设置软连接
    google::SetLogSymlink(0, "");
    //设置记录到标准输出的颜色消息，如果终端支持的话
    FLAGS_colorlogtostderr = false;
    //设置可以缓存日志的最大描述，0指实时
    FLAGS_logbufsecs = 0;
    //设置最大日志文件大小，最大10M
    FLAGS_max_log_size = 10;
    //设置是否在磁盘已满时避免日志记录到磁盘
    FLAGS_stop_logging_if_full_disk = true;
*/  
    init_dameon();
    int n = 0, ret = 1, pid, i;
    string tkname = "";
    string tkaddr = "";
    string tkstartcmd = "";
    string DelDrvName = "";
    string Opentime = "";
    string Closetime = "";
    int node_port;
    int OnoffDelete = 1;
    long logv = 0;
    short sleeptime = 30;
    time_t t_now = time(NULL);
    
    struct tm *ptm = localtime(&t_now);
    tkaddr = "127.0.0.1";
    int log_size;
    try{
        //Config mycfg(NODE_INFO);
        string szTmp;
        //szTmp = mycfg.value("node_name", 1);
        szTmp = "mydaemon";
        if(szTmp.size() > 0){
            tkname = szTmp;
            //LOG(INFO)<<"node_name = ["<<tkname<<"]";
            cout<<tkname<<endl;
        }else{
            //LOG(INFO)<<"[ERROR]Get node_name faild";
            cout<<"[ERROR]Get node_name faild"<<endl;
        }
        //szTmp = mycfg.value("self_port", 1);
        szTmp = "8081";
        if(szTmp.size() > 0){
            node_port = atoi(szTmp.c_str());
            //LOG(INFO)<<"node_port = ["<<node_port<<"]";
            cout<<"node_port = ["<<node_port<<"]"<<endl;
        }else{
            //LOG(INFO)<<"[ERROR]Get node_port faild";
            cout<<"[ERROR]Get node_port faild"<<endl;
        }
        //szTmp = mycfg.value("sleep_time", 1);
        szTmp = "25";
        if(szTmp.size() > 0){
            sleeptime = atoi(szTmp.c_str());
            //LOG(INFO)<<"sleep_time = ["<<sleeptime<<"]";
            cout<<"sleep_time = ["<<sleeptime<<"]"<<endl;
        }else{
            //LOG(INFO)<<"[ERROR]Get sleep_time faild";
            cout<<"[ERROR]Get sleep_time faild"<<endl;
        }
    }catch(...){
        //LOG(INFO)<<"[ERROR]Load config failed";
        cout<<"[ERROR]Load config failed"<<endl;
        return -1;
    }
    
    tkstartcmd = "./" + tkname + "&";
    n = find_pid_by_name((char *)tkname.c_str(), pid);
    if(n == 0){
        //LOG(INFO)<<tkname<<"has not been started";
        //LOG(INFO)<<"Start Node HKocr Server ...";
        cout<<"has not been started"<<endl;
        cout<<"Start Node HKocr Server ..."<<endl;
        system(tkstartcmd.c_str());
    }
    
    sleep(10);
    while(1){
        //LOG(INFO)<<"Sending heart detected msg";
        cout<<"Sending heart detected msg"<<endl;
        //ZSocket so;
        //ret = so.Connect(tkaddr.c_str(), node_port);
        ret = 1;
        if(ret){
            //LOG(INFO)<<"Connect ["<<tkaddr<<"]["<<node_port<<"]failed";
            //LOG(INFO)<<"Start Node HKocr Server ...";
            cout<<"Connect ["<<tkaddr<<"]["<<node_port<<"]failed"<<endl;
            cout<<"Start Node HKocr Server ..."<<endl;
            system(tkstartcmd.c_str());
        }else{
            char cmd[24];
            //ret = so.send((void *)"00000000000000", 14);
            cout<<"已发送消息: 00000000000000"<<endl;
            if(ret <= 0){
                //so.close();
                //LOG(INFO)<<"Sending heart detected msg failed";
                cout<<"Sending heart detected msg failed"<<endl;
                memset(cmd, 0, sizeof(cmd));
                snprintf(cmd, sizeof(cmd), "kill -9 %d", tkname.c_str());
                system(cmd);
                //LOG(INFO)<<"Restart [" <<tkname<<"]";
                cout<<"Restart [" <<tkname<<"]"<<endl;
                system(tkstartcmd.c_str());
            }else{
                memset(cmd, 0, sizeof(cmd));
                //ret = so.RecvEx(cmd, sizeof(cmd));
                cout<<"等待接收内容: ["<<cmd<<"]"<<endl;
                if(ret <= 0){
                    //so.close();
                    //LOG(INFO)<<"Receive return code failed";
                    cout<<"关闭套接字"<<endl;
                    memset(cmd, 0, sizeof(cmd));
                    snprintf(cmd, sizeof(cmd), "kill -9 %d", tkname.c_str());
                    system(cmd);
                    //LOG(INFO)<<"Restart [" <<tkname<<"]";
                    cout<<"Restart [" <<tkname<<"]"<<endl;
                    system(tkstartcmd.c_str());
                }else{
                    //LOG(INFO)<<"Receive mag is ["<<cmd<<"]";
                    cout<<"Receive mag is ["<<cmd<<"]"<<endl;
                }
            }
        }
        //so.close();
        cout<<"关闭套接字"<<endl;
        //close(so.Handle());
        sleep(sleeptime);
    }
    //关闭库
    //google::ShutdownGoogletGoog();
    _exit(0);
}


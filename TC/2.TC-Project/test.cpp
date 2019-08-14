#include<iostream>
#include<stdarg.h>
#include<stdio.h>
using namespace std;

//函数说明：以任何格式打印出数据
void debugout(const char *fmt, ...){
    char buf[512];
    try{
        va_list ap;
        va_start(ap, fmt);
        vsnprintf(buf, sizeof(buf) - 1, fmt, ap);
        va_end(ap);
        cout<<buf<<endl;
    }catch(...){
        cout<<"exception in construct debug message"<<endl;
    }
}

int main(){
    debugout("打印各种格式数据：[%d][%.3f][%10lf][%c][%s]", 
        2019, 3.1415926, 3.1415926, 'A', "你好，世界");
    
    time_t t;
    time(&t);
    struct tm *showTime;
    showTime =localtime(&t);   
    debugout("%04d-%02d-%02d", 
        showTime->tm_year + 1900, 
        showTime->tm_mon +1, 
        showTime->tm_mday);   
    return 0;
}

#include<iostream>
#include<string>
#include<stdio.h>
#include<bits/stdc++.h>

using namespace std;

int main(){
    char s[] = "ssssssss1bssssss2asss3bsss4";
    char *d = "ab";
    char *p;
    printf("---[%s]\n", strtok(s, d));
    while((p = strtok(NULL, d))){
        printf("+++[%s]\n", p);
    }
    return 0;
}

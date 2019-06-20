// Socket.cpp : 定义控制台应用程序的入口点。
//
/*
#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

*/
#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <WinSock2.h>
#include <string>
#include <stdlib.h>
#include <Windows.h>
#include <fstream>
#include <vector>
#include <process.h>
#include "cJSON.h"

#define G_PORT 7912
#define S_PORT 49968

using namespace std;
void printfJson(cJSON *root);

int sk = 0;//client
int s_sock = 0;//server

void printJson(cJSON *root);

int SocketInit(){
	WSADATA wsaData;
	int err;
	WORD sockVersion = MAKEWORD(2, 2);
	err = WSAStartup(sockVersion, &wsaData);
	if(err != 0){
		perror("WSAStartup fail\n");
		return -1;
	}
	sk = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(sk == 0){
		printf("socket faild\n");
		return -1;
	}
	printf("socket init done!\n");
	return 0;
}

int CreateSock(){
	WSADATA wsaData;
	int err;
	WORD sockVersion = MAKEWORD(2, 2);
	err = WSAStartup(sockVersion, &wsaData);
	if(err != 0){
		perror("WSAStartup fail\n");
		return -1;
	}
	s_sock = socket(AF_INET, SOCK_STREAM, 0);
	if(s_sock == 0){
		printf("create sock faild\n");
		return -1;
	}
	printf("socket init done!\n");
	return 0;
}

int Bind(int port){
	int opt = 3000;
	setsockopt(s_sock, SOL_SOCKET, SO_REUSEADDR, (const char *)&opt, sizeof(opt));
	sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	return bind(s_sock, (sockaddr *)&server, sizeof(server));
}

int Listen(int backlog = 50){
	return listen(s_sock, 50);
}

SOCKET Accept(struct sockaddr *addr, int &addrlen){
	return accept(s_sock, addr, &addrlen);
}

int SocketConnect(int sk){
	int ret = 0;
	struct sockaddr_in sock_in;
	sock_in.sin_family = AF_INET;
	sock_in.sin_addr.s_addr = inet_addr("182.119.137.75");
	sock_in.sin_port = htons(G_PORT);
	ret = connect(sk, (struct sockaddr *)&sock_in, sizeof(struct sockaddr));
	if(ret){
		printf("Sockect connect faild\n");
		return -2;
	}
	printf("Sockect connect Successd!\n");
	return ret;
}

int SendData(char str[], int size){
	int num = 0;
	num = send(sk, str, size, 0);
	printf("SendData done! num:[%d]\n", num);
	return num;
}

int RecData(){
	int count = 0;
	int rc =0 ;
	int pack_len = 0;
	char rec[4096] = {0};
	do{
		count = recv(sk, rec, 8, 0);
		if(count < 0){
			rc++;
		}else{
			break;
		}
	}while(rc < 10);
	pack_len = atoi(rec);
	printf("pack_len: [%d]\n", pack_len);
	do{
		count = recv(sk, rec, pack_len, 0);
		if(count < 0){
			rc++;
		}else{
			break;
		}
	}while(rc < 10);
	printf("RecData done count: [%d], rec: [%s]\n", count, rec);
	return count;
}

DWORD WINAPI test_send(LPVOID lpParamter){
	string json = "0000035801 {\"sysBk\":\"01810999999\",\"socMax\":\"01\",\"ocrFileList\":[{\"groupNo\":\"00000002\",\"minName\":\"111111111\",\"createTime\":\"2019-04-02 09:48:14.0\",\"docMax\":\"01\",\"batchNo\":\"20190402000004\",\"fileCode\":\"8300010001\",\"filePatch\":\"D:/TC_Project/TC/demo/Socket/picture/01.jpg\",\"fileName\":\"222222222(account doc)\",\"docMin\":\"0101\",\"maxName\":\"333333333\"}],\"batchNo\":\"20190402000004\"}";
	char buff[1024] = {0};
	printf("json.size(): [%d]\n", json.size());
	memcpy(buff, json.c_str(), json.size());
	SocketInit();
	SocketConnect(sk);
	SendData(buff, json.size());
	Sleep(100);
	RecData();
	closesocket(sk);
	return 0;
}

int result(){
	char recvbuff[4096];
	int cliaddr_len;
	struct sockaddr_in cliaddr;
	char buff_cli[50];
	SOCKET cliSock;
	int accept_id = 0;
	int rc = 0;
	cJSON *root = NULL;
	int pkg_len = 0;
	int count = 0;

	CreateSock();
	Bind(S_PORT);
	Listen();
	while(1){
		printf("111111111\n");
		memset(recvbuff, 0, 4096);
		memset(&cliaddr, 0, sizeof(cliaddr));
		memset(buff_cli, '\0', sizeof(buff_cli));
		cliaddr_len = sizeof(cliaddr);

		if((cliSock = accept(s_sock, (struct sockaddr *)&cliaddr, &cliaddr_len)) == -1){
			closesocket(cliSock);
			printf("222222222\n");
			Sleep(1000);
			continue;
		}

		printf("IP_ADDR = %s\n", inet_ntoa(cliaddr.sin_addr));
		memset(recvbuff, 0, sizeof(recvbuff));
		do{
			count = recv(cliSock, recvbuff, 8, 0);
			if(count < 0){
				rc++;
			}else{
				break;
			}
		}while(rc < 10);
		if(8 != count){
			printf("数据长度copunt不为8\n");
			return -1;
		}
		pkg_len = atol(recvbuff);
		memset(recvbuff, 0, sizeof(recvbuff));
		rc = 0;
		do{
			count = recv(cliSock, recvbuff, 2, 0);
			if(count < 0){
				rc++;
			}else{
				break;
			}
		}while(rc < 10);
		printf("数据类型recvbuff = [%d]\n", atoi(recvbuff));
		if(2 != count){
			printf("数据长度count不为2\n");
			return -2;
		}
		memset(recvbuff, 0, sizeof(recvbuff));
		rc  = 0;
		do{
			count = recv(cliSock, recvbuff, pkg_len, 0);
			if(count < 0){
				rc++;
			}else{
				break;
			}
		}while(rc < 10);
		printf("pkg_len = %d, recvbuff = %s, count = %d\n", pkg_len, recvbuff, count);
		if(pkg_len != count){
			printf("Recv XML Length errpr, break");
			return -3;
		}

		root = cJSON_Parse(recvbuff);
		printJson(root);
	}
	closesocket(cliSock);
	free(root);
	printf("33333333\n");
	return 0;
}

void printJson(cJSON *root){//以递归的方式打印json的最内层键值对
	for(int i = 0; i < cJSON_GetArraySize(root); i++){//遍历最外层json键值对
		cJSON *item = cJSON_GetArrayItem(root, i);
		if(cJSON_Object == item->type){//如果对应键值对仍为cJSON_Object就递归调用printJson
			printJson(item);
		}else{
			printf("%s->", item->string);
			printf("%s\n", cJSON_Print(item));
		}
	}
}
#if 1
int main(){
	{
		for(int i = 0; i < 1; i++){
			HANDLE hThread = CreateThread(NULL, 0, test_send, NULL, 0, NULL);
			if(hThread != NULL){
				CloseHandle(hThread);
			}
			Sleep(1000);
		}
	}
	result();
	system("pause");
	return 0;
}
#endif

#if 0
int main(int argc, _TCHAR* argv[]){
	char *jsonStr = "";
	cJSON *root = NULL;
	cJSON *item = NULL;

	root = cJSON_Parse(jsonStr);
	if(!root){//为空则返回错误报文
		printf("Error before: [%s]\n", cJSON_GetErrorPtr());
	}else{
		cJSON *ocrList = NULL;
		root = cJSON_Parse(jsonStr);
		if(!root){//为空则返回错误报文
			printf("Error before: [%s]\n", cJSON_GetErrorPtr());
			return -1;//E_PARSE_CODE_XML_ERROR;
		}else{
			item = cJSON_GetObjectItem(root, "sysBk");//系统机构号
			if((cJSON_String == item->type) && (strcmp(item->string, "sysBk") == 0)){
				if(item->valuestring != NULL){
					printf("sysBk: [%s]\n", item->valuestring);
				}
			}
			item = cJSON_GetObjectItem(root, "batchNo");//批次编号
			if((cJSON_String == item->type) && (strcmp(item->string, "batchNo") == 0)){
				if(item->valuestring != NULL){
					printf("batchNo: [%s]\n", item->valuestring);
				}
			}
			item = cJSON_GetObjectItem(root, "docMax");//大类编号
			if((cJSON_String == item->type) && (strcmp(item->string, "docMax") == 0)){
				if(item->valuestring != NULL){
					printf("docMax: [%s]\n", item->valuestring);
				}
			}

			ocrList = cJSON_GetObjectItem(root, "ocrFileList");//
			if(ocrList != NULL){
				json_node = j_node;
				if(cJSON_Array == ocrList->type){
					for(int i = 0; i<cJSON_GetArraySize(ocrList); i++){
						cJSON *tmp = cJSON_GetArrayItem(ocrList, i);
						item = cJSON_GetObjectItem(tmp, "docMax");//大类编号
						if((cJSON_String == item->type) && (strcmp(item->string, "docMax") == 0)){
							if(item->valuestring != NULL){
								printf("docMax: [%s]\n", item->valuestring);
							}
						}
						item = cJSON_GetObjectItem(tmp, "maxName");//大类名称
						if((cJSON_String == item->type) && (strcmp(item->string, "maxName") == 0)){
							if(item->valuestring != NULL){
								printf("maxName: [%s]\n", item->valuestring);
							}
						}
						item = cJSON_GetObjectItem(tmp, "docMin");//小类编号
						if((cJSON_String == item->type) && (strcmp(item->string, "docMin") == 0)){
							if(item->valuestring != NULL){
								printf("docMin: [%s]\n", item->valuestring);
							}
						}
						item = cJSON_GetObjectItem(tmp, "minName");//小类名称
						if((cJSON_String == item->type) && (strcmp(item->string, "minName") == 0)){
							if(item->valuestring != NULL){
								printf("minName: [%s]\n", item->valuestring);
							}
						}
						item = cJSON_GetObjectItem(tmp, "groupNo");//文件组号
						if((cJSON_String == item->type) && (strcmp(item->string, "groupNo") == 0)){
							if(item->valuestring != NULL){
								printf("groupNo: [%s]\n", item->valuestring);
							}
						}
						item = cJSON_GetObjectItem(tmp, "fileCode");//文件编码
						if((cJSON_String == item->type) && (strcmp(item->string, "fileCode") == 0)){
							if(item->valuestring != NULL){
								printf("fileCode: [%s]\n", item->valuestring);
							}
						}
						item = cJSON_GetObjectItem(tmp, "fileName");//文件名称
						if((cJSON_String == item->type) && (strcmp(item->string, "fileName") == 0)){
							if(item->valuestring != NULL){
								printf("fileName: [%s]\n", item->valuestring);
							}
						}
						item = cJSON_GetObjectItem(tmp, "filePath");//文件全路径
						if((cJSON_String == item->type) && (strcmp(item->string, "filePath") == 0)){
							if(item->valuestring != NULL){
								printf("filePath: [%s]\n", item->valuestring);
							}
						}
					}
				}
				json_node_item.push_back(j_node);
			}
		}
		printf("\n[%s]\n", "打印json所有最内层键值对:");
		printJson(root);
		system("pause");
	}
	return 0;
}

#endif


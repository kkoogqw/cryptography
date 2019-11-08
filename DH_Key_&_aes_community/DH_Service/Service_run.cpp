
#include "DH_server.h"

#include <stdlib.h>
#include <stdio.h>
#include <winsock2.h>
#include <time.h>
#include "conio.h"
#include <windows.h>
#include <process.h>
#include <math.h>

#define QLEN       5
#define WSVERS     MAKEWORD(2, 0)
#define BUFLEN     2000             
#pragma comment(lib,"ws2_32.lib")  

SOCKET msock, ssock;            
SOCKET sockets[100] = { NULL };

int cc;
char *pts;                    
time_t now;                    
char buf[BUFLEN];             
char *input;
HANDLE hThread1, hThread[2] = { NULL };
unsigned int threadID, ThreadID[100], number;

struct sockaddr_in fsin;
struct sockaddr_in Sin;

// 建立mod p
string temp_init = build_mod_p();
string mod_p = build_mod_p();
string send_p = pack_send_mod(mod_p);

// 存放由client发送得来的数据
vector<string> key_info_set;
bool is_send_info = false;

unsigned int __stdcall Chat(PVOID PM) {
	// 建立mod p
	char modp_buf[BUFLEN];
	char key_info_buf[BUFLEN];
	sprintf(modp_buf, send_p.c_str());

	// 服务器只进行消息转发，不负责进行加密/解密
	
	(void)time(&now);
	pts = ctime(&now);
	sockets[number] = ssock;
	SOCKET sock = ssock;
	ThreadID[number] = threadID;
	unsigned int threadid = threadID;

	// 首先进行modp的发送
	(void)send(sock, modp_buf, sizeof(modp_buf), 0);
	cout << "Send the D-H prime mod number to client successfully!" << endl;
	
	// 查看当前密钥消息集的状态，决定等待接受/发送数据
	int rec_count = recv(sock, key_info_buf, BUFLEN, 0);
	string recv_key_info = key_info_buf;
	key_info_set.push_back(recv_key_info);

	cout << "Have recived " << key_info_set.size() << "exchanged key information! " << endl;

	// 根据标识变量(线程信号量通信)转发两个模幂结果
	if (key_info_set.size() == 2){
		char key_buf[BUFLEN];
		sprintf(key_buf, key_info_set[0].c_str());
		(void)send(sock, key_buf, sizeof(key_buf), 0);
	}
	else {
		cout << "Waiting for another client..." << endl;
		while (key_info_set.size() != 2) { Sleep(50); }
		char key_buf[BUFLEN];
		sprintf(key_buf, key_info_set[1].c_str());
		(void)send(sock, key_buf, sizeof(key_buf), 0);
		is_send_info = true;
	}

	while (is_send_info == false) { Sleep(50); }

	// 缓冲区建立
	char buf1[BUFLEN];
	char buf2[BUFLEN];
	char buf3[BUFLEN];
	char buf4[BUFLEN];
	
	sprintf(buf2, "[Server]\nThread <%d>\tClient Info <IP:%s Port:%d>  Enter the chat!\n", threadid, inet_ntoa(fsin.sin_addr), fsin.sin_port);
	
	cout << buf2;
	
	cout << "Sending the data/massage to clients..." << endl;
	for (int i = 0; i <= number; i++) {
		if (sockets[i] != NULL && sockets[i] != sock) {
			(void)send(sockets[i], buf2, sizeof(buf2), 0);
			// printf(" 发送至线程号<%d>成功！\n", ThreadID[i]);
			cout << "Send massage to [Thread " << ThreadID[i] << "] Successfully!"<< endl;
		}
	}
	cout << endl;

flag1:cc = recv(sock, buf3, BUFLEN, 0);   
	if (cc == SOCKET_ERROR || cc == 0) {
		(void)time(&now);
		pts = ctime(&now);
		// sprintf(buf3, " 线程号 <%d> 客户<IP:%s 端口:%d>  leave !  \n \t\t时间： %s", threadid, inet_ntoa(fsin.sin_addr), fsin.sin_port, pts);
		sprintf(buf3, "[Server]\nThread <%d> Client Info <IP:%s Port:%d>  Left the chat!  \nTime: %sConnection will be closed...\n", threadid, inet_ntoa(fsin.sin_addr), fsin.sin_port, pts);
		sock = NULL;
		sockets[number] = NULL;
		CloseHandle(hThread[number]);
	
		cout << buf3 << endl;
	
		cout << "Sending the data/massage to clients..." << endl;
		for (int i = 0; i <= number; i++) {
			if (sockets[i] != NULL && sockets[i] != sock) {
				(void)send(sockets[i], buf3, sizeof(buf3), 0);
				// printf(" 发送至线程号<%d>成功！\n", ThreadID[i]);
				cout << ("Send massage to [Thread %d] Successfully!", ThreadID[i]) << endl;
			}
		}
		cout << endl;
		return 0;
	}

	else if (cc > 0) {
		(void)time(&now);
		pts = ctime(&now);
		// sprintf(buf4, " 线程号 <%d> 客户<IP:%s 端口:%d>说 ：%s  \n \t\t时间 ： %s", threadid, inet_ntoa(fsin.sin_addr), fsin.sin_port, buf3, pts);
		sprintf(buf4, "[Client]\nThread <%d> Client Info <IP:%s Port:%d>\tSay:\n=>%s<=\nTime:  %s", threadid, inet_ntoa(fsin.sin_addr), fsin.sin_port, buf3, pts);
		// todo 
		// 提取其中的密文段并转换为16进制输出到服务器控制台
		string cip = buf3;
		printf("[Client]\nThread <%d> Client Info <IP:%s Port:%d>\nTime:  %sSend ciphertext: ", threadid, inet_ntoa(fsin.sin_addr), fsin.sin_port, pts);
		// operating for ciphtext...
		for (int i = 0; i < cip.length(); i++) {
			printf("0x%02X ", (unsigned char)cip[i]);
		}
		cout << endl;

		// Send to Client
		cout << "Sending the data/massage to clients..." << endl;
		for (int i = 0; i <= number; i++) {
			if (sockets[i] != NULL && sockets[i] != sock)
			{
				(void)send(sockets[i], buf4, sizeof(buf4), 0);
				cout << "Send massage to [Thread " << ThreadID[i] << "] Successfully!" << endl;
			}
		}
		cout << endl;
		goto flag1;
	}
	(void)closesocket(sock);

	return 0;
}


int main() {
	cout << "===[ AES / Diffie-Hellman Chat test Program ]===" << endl;
	cout << "Name:\tGao Qian-wen" << endl;
	cout << "ID:\t16338002" << endl;
	cout << "Major:\tSDCS Information Security" << endl;
	cout << "====================[ Server ]====================" << endl;

	// test print 
	// cout << "mod p:" << mod_p << endl;

	// 建立Server
	int alen;                   
	WSADATA wsadata;
	char service[] = "5050";
	WSAStartup(WSVERS, &wsadata);                         //加载 winsock 2.2 library
	msock = socket(PF_INET, SOCK_STREAM, 0);              //生成套接字。TCP协议号=6， UDP协议号=17
	memset(&Sin, 0, sizeof(Sin));
	Sin.sin_family = AF_INET;
	Sin.sin_addr.s_addr = INADDR_ANY;                    //指定绑定接口的IP地址。INADDR_ANY表示绑定(监听)所有的接口。
	Sin.sin_port = htons((u_short)atoi(service));        //atoi--把ascii转化为int，htons - 主机序(host)转化为网络序(network), s(short)
	bind(msock, (struct sockaddr *)&Sin, sizeof(Sin));   // 绑定端口号（和IP地址)
	listen(msock, 5);                                    //队列长度为5

	(void)time(&now);
	pts = ctime(&now);

	cout << "Time: " << pts;
	cout << "Waiting for client connection..." << endl;
	number = -1;
	while (1) {
		alen = sizeof(struct sockaddr);
		ssock = accept(msock, (struct sockaddr *)&fsin, &alen);
		number++;
		if (number >= 2) {
			cout << "Only 2 client connections for Server!" << endl;
			number = 1;
			continue;
		}
		hThread[number] = (HANDLE)_beginthreadex(NULL, 0, Chat, NULL, 0, &threadID);
	}
	(void)closesocket(msock);
	WSACleanup();                         
	//卸载 winsock 2.2 library
	return 0;
}
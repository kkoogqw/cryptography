
#include "DH_AES_init.h"

#include <stdlib.h>
#include <stdio.h>
#include <winsock2.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <process.h>
#include <math.h>

#define BUFLEN        2000                  // 缓冲区大小
#define WSVERS        MAKEWORD(2, 0)        // 指明版本2.0
#pragma comment(lib,"ws2_32.lib")         // 指明winsock 2.0 Llibrary


SOCKET sock, sockets[100] = { NULL };                       
//    int    cc;                              
char *packet = NULL;      
char *pts, *input;
HANDLE hThread;
unsigned threadID;

BigInt temp_init = build_128_number();

BigInt g("2");
BigInt private_order = build_128_number();
BigInt mod_p;
BigInt rec_key;


string order = private_order.to_string(private_order);
string send_key;
string AES_key;

// 标识状态：
// 0 等待接收mod p
// 1 收到 p 计算完成 g ^ x mod p,等待发送完成
// 2 已经发送完成 g ^ x mod p, 准备接受对方密钥,计算 AES key
// 3 连接建立完成，可以发送消息
// 
int state = 0;

unsigned int __stdcall Chat(PVOID PM) {
	time_t now;
	(void)time(&now);
	pts = ctime(&now);
	char buf[BUFLEN];

	while (1) {
		int cc = recv(sock, buf, BUFLEN, 0);   // cc为接收的字符数
		if (cc == SOCKET_ERROR || cc == 0) {
			
			cout << "ERROR: " << GetLastError();
			cout << " Lost the connection with the Server!" << endl;
			CloseHandle(hThread);
			(void)closesocket(sock);
			break;
		}
		else if (cc > 0) {
			if (state == 0) {
				string temp_p = buf;
				mod_p = unpack_rec_p(temp_p);
				send_key = pack_send_key_info(private_order, mod_p, g);
				//test print
				// cout << send_key << endl;

				char my_info_buf[BUFLEN];
				sprintf(my_info_buf, send_key.c_str());
				(void)send(sock, my_info_buf, sizeof(my_info_buf), 0);
				cout << "Waiting for another client..." << endl;
				state = 2;
			}
			else if (state == 2) {
				string temp_k_info = buf;
				cout << "building AES key..." << endl;
				rec_key = unpack_rec_key_info(temp_k_info); 
				AES_key = build_encrypt_key(private_order, rec_key, mod_p);
				// test print 
				// cout << "AES key: "; print_ciphertext(AES_key);

				cout << "AES key builds successfully!" << endl;
				cout << "Diffie-Hellman Key Exchange Agreement has finished!" << endl;
				state = 3;
			}
			else if (state == 3){
				// 检查接收的消息包
				// “[server]” 不进行解密直接输出
				// “[Client]” 提取对应字段解密后输出
				// 应当分别输出密文与对应翻译出的明文
				string temp_msg = buf;
				string msg_from = temp_msg.substr(0, 8);
				if (msg_from == "[Server]") {
					cout << "From: "<< buf << endl;
					continue;
				}
				// 对buf中的字符提取： 对方IP/端口/线程号
				else if (msg_from == "[Client]") {
					int msg_begin, msg_end;
					int client_info_begin, client_info_end;
					// 获取消息内容
					for (int i = 0; i < temp_msg.length(); i++) {
						if (temp_msg[i] == '\n' && temp_msg[i + 1] == 'T' && temp_msg[i + 2] == 'h' && temp_msg[i + 3] == 'r') {
							client_info_begin = i;
							continue;
						}
						if (temp_msg[i] == '\t' && temp_msg[i + 1] == 'S' && temp_msg[i + 2] == 'a' && temp_msg[i + 3] == 'y') {
							client_info_end = i;
							continue;
						}
						if (temp_msg[i] == '=' && temp_msg[i + 1] == '>') {
							msg_begin = i + 2;
							continue;
						}
						if (temp_msg[i] == '<' && temp_msg[i + 1] == '=') {
							msg_end = i;
							break;
						}
					}
					string client_info = temp_msg.substr(client_info_begin, client_info_end - client_info_begin);
					string cip_msg = temp_msg.substr(msg_begin, msg_end - msg_begin);
					// test print
					cout << "From: " << msg_from << client_info << endl;
					cout << "Recived ciphertext: " << endl;
					print_ciphertext(cip_msg);
					//  todo 解密部分
					string decrypted_text = AES_128_CBC_decrypt(AES_key, cip_msg, "sysu");
					cout << "Decrypt result: " << endl;
					print_decrypt_result(decrypted_text); 
					cout << endl;
					cout << "Raw decrypt result:" << endl << decrypted_text << endl;
				}
				else {
					cout << "Cannot recognize the message source!" << endl;
				}
				
			}

		}
	}
	return 0;
}

int main() {
	cout << "===[ AES / Diffie-Hellman Chat test Program ]===" << endl;
	cout << "Name:\tGao Qian-wen" << endl;
	cout << "ID:\t16338002" << endl;
	cout << "Major:\tSDCS Information Security" << endl;
	cout << "====================[ Client ]====================" << endl;

	time_t now;
	(void)time(&now);
	pts = ctime(&now);
	char host_ip[] = "127.0.0.1";        /* server IP to connect         */
	char service_port[] = "5050";          /* server port to connect       */

	struct sockaddr_in sin;          
	WSADATA wsadata;
	WSAStartup(WSVERS, &wsadata);       

	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons((u_short)atoi(service_port));   
	sin.sin_addr.s_addr = inet_addr(host_ip);

	sock = socket(PF_INET, SOCK_STREAM, 0);

	connect(sock, (struct sockaddr *)&sin, sizeof(sin));


	hThread = (HANDLE)_beginthreadex(NULL, 0, Chat, NULL, 0, &threadID);
	cout << "You can send massage to others online!" << endl;
	cout << "And the massage you send will be encrypted by AES - 128 in CBC type." << endl;
	while (1) {
		char buf1[BUFLEN];
		// todo
		// 输入消息进行加密打包发送
		string plaintext;
		getline(cin, plaintext);
		if (plaintext == "exit") {
			break;
		}

		// AES 加密部分
		string AES_encrypted_text = AES_128_CBC_encrypt(AES_key, plaintext, "sysu");
		sprintf(buf1, AES_encrypted_text.c_str());
		// gets_s(buf1);
		
		(void)send(sock, buf1, sizeof(buf1), 0);
		(void)time(&now);
		pts = ctime(&now);
		cout << "Send successfully！\tTime: " << pts << endl;
		
	}

	CloseHandle(hThread);
	closesocket(sock);
	WSACleanup();                     /* 卸载某版本的DLL */

	cout << "Plaese press ENTER to exit the prcess..." << endl;
	getchar();
	return 0;                           /* exit */
}
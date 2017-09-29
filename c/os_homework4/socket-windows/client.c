#include <Winsock2.h>
#include <stdio.h>
#include <memory.h>
#include <string.h>
#include <conio.h>
#pragma comment(lib, "Ws2_32.lib")
#define QUEUE_SIZE 5
#define BUF_SIZE 4096
#define PORT 1002
void main() {
	//初始化SOCKET必须调用
	WSAData wsd;
	WSAStartup(MAKEWORD(2, 0), &wsd);
	printf("为确保程序正常运行，请先启动服务端\n");
	printf("请输入你想连接的地址，按回车会默认使用本机地址\n");
	char i_address[16];
	gets(i_address);
	if (i_address[0] == '\0')
	{
		strcpy(i_address, "127.0.0.1");
	}
	printf("准备与服务器 %s 建立连接 端口:%d\n", i_address, PORT);
	//创建SOCKET
	SOCKET s = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (s == INVALID_SOCKET)
	{
		printf("socket 创建失败,错误代码：%d\n", WSAGetLastError());
		exit(0);
	}
	//定义 socket 地址 初始化清空
	struct sockaddr_in channel;
	memset(&channel, 0, sizeof(channel));
	channel.sin_family = AF_INET;
	channel.sin_addr.s_addr = inet_addr(i_address);
	channel.sin_port = htons(PORT);
	//绑定地址以及端口
	int c = connect(s, (struct sockaddr *) &channel, sizeof(channel));
	if (c == SOCKET_ERROR)
	{
		printf("连接出错 失败, 错误代码:%d\n", WSAGetLastError());
		exit(0);
	}
	//初始化工作完成
	printf("TCP连接已建立 ，准备向主机 %s:%d 发送信息\n ", i_address, PORT);
	//定义缓冲区
	char buf[BUF_SIZE];
	char info[256];
	char quitInfo[] = "QUIT";
	int nBytesSend = strlen(buf);
	do
	{
		gets(info);
		if (info[0] == '\0')
		{
			printf("没有检测到内容，请重新输入\n");
		}
		else {
			if (!strcmp(info, quitInfo))
			{
				printf("检测到退出命令\n");
				break;
			}
			strcpy(buf, info);
			nBytesSend = send(s, buf, strlen(buf), 0);
		}
	} while (nBytesSend == strlen(buf));
	printf("即将关闭连接\n");
	int r = closesocket(s);
	if (r == SOCKET_ERROR)
	{
		printf("关闭失败\n");
		exit(0);
	}
	printf("输入结束 与服务器连接断开,按任意键结束\n");
	getch();
}

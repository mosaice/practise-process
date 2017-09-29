#include "socket.h"

int main(int argc, char **argv) {
  int sockfd, fd, n;
  struct sockaddr_in server;
  struct hostent *hp;
  char rbuf[1024];

  printf("客户端启动\n");
  /*创建socket套接字*/
  sockfd=socket(AF_INET,SOCK_STREAM,0);
  /*尝试从命令行参数读取参数转换成地址*/
  if((hp=gethostbyname(argv[1]))==NULL) return 1;
  server.sin_family = AF_INET;
  /*将读出的参数转换成地址和端口后写入server结构体中*/
  bcopy((char *)hp->h_addr, (char *)&server.sin_addr.s_addr, hp->h_length);
  server.sin_port = htons(atoi(argv[2]));
  /*尝试对服务端建立连接*/
  if (connect(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0) return 1;
  /*连接建立成功后读取本地文件发送过去*/
  fd=open("in.txt",O_RDONLY,0644);
  while((n=read(fd,rbuf,1024))>0) {
    
    if(n<1024) rbuf[n] = '\0';
    send(sockfd, rbuf, n, 0);
    bzero(rbuf, sizeof(rbuf));
  }
  printf("发送完毕\n");
  /*关闭句柄*/
  close(fd);
  close(sockfd);
  return 0;
}

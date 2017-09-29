#include "socket.h"

int main(int argc, char **argv) {
  int sockfd, newsockfd, fd, count, length;
  struct sockaddr_in server;
  char buff[1024];

  printf("服务端启动\n");
  /*创建套接字*/
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    perror("creat socket:");
    exit(-1);
  }
  /*设置服务端地址以及端口*/
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = 0;
  /*对套接字进行地址端口绑定*/
  if (bind(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0) return 1;
  length = sizeof(server);
  /*获取地址端口信息*/
  if (getsockname(sockfd, (struct sockaddr *)&server, &length) < 0) printf("getting socket name error\n");

  printf("socket port %d\n", ntohs(server.sin_port));
  /*对套接字监听 并且接收长度为5*/
  listen(sockfd, 5);
  /*循环 处理连接请求*/
  while (1) {
    /*等待 建立连接*/
    newsockfd = accept(sockfd, (struct sockaddr *)0, (int *)0);
    if (newsockfd == -1) {
      perror("accept error!");
      exit(-1);
    }
    /*创建子进程*/
    if (!fork()) {
      /*子进程内部关闭socket句柄*/
      close(sockfd);
      /*清空buff区域*/
      bzero(buff, sizeof(buff));
      /*打开输入文件的句柄*/
      fd = open("out.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
      sleep(1);
      /*重复接受内容到buff 并写入到文件中去*/
      while ((count = recv(newsockfd, buff, sizeof(buff), 0)) > 0)
        write(fd, buff, count);
      
      /*写入完毕关闭文件 子进程退出*/
      close(fd);
      exit(0);
    }
    /*关闭连接*/
    close(newsockfd);
  }
}

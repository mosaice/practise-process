/* 
* 编写一个父子进程之间用无名管道进行数据传送的C程序
* 父进程逐一读出一个文件的内容，并通过管道发送给子进程
* 子进程从管道中读出信息，再将其写入一个新的文件
* 程序结束后，对原文件和新文件的内容进行比较
* 说明：读入的文件为in.txt 写入的文件为out.txt
*/

#include <stdio.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char **argv) {
  int out, n, chan[2];
  FILE *in;
  char buff[100];
  /* 开启一个读的文件流 */
  in = fopen("in.txt", "r");
  /* 创建一个只写的文件流 */
  out = open("out.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
  /* 开启一个无名管道 */
  pipe(chan);

  if (fork()) {
    /*父进程关闭读的管道将文件内入读入然后依次送到写的管道中去*/
    close(chan[0]);
    while (fgets(buff, sizeof(buff) - 1, in)) {
      write(chan[1], buff, sizeof(buff));
    }
    close(chan[1]);
  } else {
    /*子进程关闭写的管道，接收读的管道的内容依次写到out.txt中去*/
    close(chan[1]);
    while (read(chan[0], buff, sizeof(buff)) > 0) {
      write(out, buff, strlen(buff));
    }
    close(chan[0]);
  }
  /*关闭 两个文件指针*/
  close(in);
  close(out);
  return 0;
}


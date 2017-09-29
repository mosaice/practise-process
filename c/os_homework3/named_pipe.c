/* 在两个用户的独立程序之间，使用有名管道，重新编写一个C程序，实现题2的功能 */
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char **argv) {
  int in, out, wp, rp, n, iofile;
  char buff[1024];
  /* 开启一个读的文件流 */
  in = open("in.txt", O_RDONLY, 0644);
  /* 创建一个只写的文件流 */
  out = open("out.txt", O_WRONLY | O_CREAT | O_TRUNC , 0644);
  /* 创建一个有名管道文件 */
  iofile = mknod("iofile", S_IFIFO | 0666, 0);

  if (iofile == -1)
  {
    perror("Error: ");
    return (-1);
  }

  if (fork()) {
    /*父进程以写的模式打开管道*/
    wp = open("iofile", O_WRONLY);
    /*循环读取文件中的内容发送到写的管道中去，结束后关闭管道和文件指针*/
    while ((n = read(in, buff, 1024)) > 0) {
      write(wp, buff, n);
    }
    close(wp);
    close(in);
  } else {
    /*子进程以读的模式打开管道*/
    rp = open("iofile", O_RDONLY);
    /*
    * 尝试从管道中读文件
    * 当管道中有内容时,n为读取到的内容长度
    * 当n = -1 表示管道中的内容已经读完
    * 当n = 0 表示还未读取到内容，则睡眠5秒
    * 否则将读取到的内容写入文件中
    */
    while ((n = read(rp, buff, 1024)) != -1) {
      if (!n) {
        sleep(5);
      } else {
        write(out, buff, strlen(buff));
      }
    }
    close(rp);
    close(out);
  }
  if (n == -1)
  {
    perror("Error: ");
    return (-1);
  }
  return 0;
}

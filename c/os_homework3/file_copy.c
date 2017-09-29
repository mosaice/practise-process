/* 编写一个文件复制的C语言程序： */
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  /*
  * buf 为文件内容缓存
  * t 为命令行第三个参数的首字母主要用来区别模式用的
  * t = a: 模式1 使用read wrtie nbytes = 1
  * t = b: 模式2 使用fread fwrtie szie = 1, nitems = 1
  * t = c: 模式3 使用read wrtie nbytes = 4096
  * t = d: 模式4 使用fread fwrtie szie = 1, nitems = 4096
  */
  char buf[5000];
  char t = (char)argv[3][0];
  FILE *fd1, *fd2;
  switch (t) {
    case 'a':
      fd1 = open(argv[1], O_RDONLY);
      creat(argv[2], 0660);      
      fd2 = open(argv[2], O_WRONLY);
      while (read(fd1, buf, 1) > 0) {
        write(fd2, buf, 1);
      }
      break;
    case 'b':
      fd1 = fopen(argv[1], "r");
      fd2 = fopen(argv[2], "w");
      while (fread(buf, 1, 1, fd1) > 0) {
        fwrite(buf, 1, 1, fd2);
      }
      break;
    case 'c':
      fd1 = open(argv[1], O_RDONLY);
      creat(argv[2], 0660);      
      fd2 = open(argv[2], O_WRONLY);
      while (read(fd1, buf, 4096) > 0) {
        write(fd2, buf, 4096);
      }
      break;
    case 'd':
      fd1 = fopen(argv[1], "r");
      fd2 = fopen(argv[2], "w");
      while (fread(buf, 1, 4096, fd1) > 0) {
        fwrite(buf, 1, 4096, fd2);
      }
      break;
    default:
      fd1 = open(argv[1], O_RDONLY);
      creat(argv[2], 0660);      
      fd2 = open(argv[2], O_WRONLY);
      while (read(fd1, buf, 1) > 0) {
        write(fd2, buf, 1);
      }
      break;
  }
  close(fd1);
  close(fd2);
}

#include <sys/types.h>
#include <signal.h>
#include <stdio.h>

// 自定义信号处理函数
int func() {
  printf("我是信号处理方法\n");
}

int main() {
  /*
  * 初始化pid 和 status 变量
  * 因为fork 函数的子进程中的pid 为0 为了区分 将pid 设置为1
  * 程序默认的退出是 返回信号 0 
  */
  int pid,status = 1;
  /* 注册自定义信号处理函数 */
  signal(SIGUSR1,func);
  /* 如果fork失败则重复 */
  while ((pid=fork())==-1);
  /* pid 为0 为子进程*/
  if (pid) {
    /* 父进程里面 */
    printf("这里是父进程.\n");
    printf("父进程即将发送信号.\n");
    /* 像子进程发送信号 */
    kill(pid,SIGUSR1);
    /* 等待子进程结束 将子进程的返回值赋值到 status */
    pid = wait(&status);
    printf("子进程： %d,status=%d \n",pid,status);
  } else {
    /* 进入子进程 先进行睡眠让父进程先执行 */
    sleep (5);
    printf("这里是子进程.\n");
    printf("子进程接收到信号.\n");
    /* 重新装载程序镜像 */
    execlp("echo", "echo", "我是重装镜像的echo", NULL);
    /*
    * 如果子程序重装图像成功则后面部分被替换不会执行
    * 反之如果打印出来了 代表子程序重装图像失败
    */
    printf("子进程重装失败了.\n");
    exit(2);
  }
  /* 子程序重装成功 则没有这部分 */
  printf ("父进程结束了. \n");
}

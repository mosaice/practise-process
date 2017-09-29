/*
* 使用共享内存来管理两个信号量 来模拟生产者消费者问题
* 程序启动后会fork 出子进程，父进程负责检查生产的信号
* 如果大于0则生产并对消费的信号加一，子进程负责检查消费信号若大于0则消费并给生产信号加一
*/

#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>

#define FILENAME "test"
#define NUM 5

typedef struct {
  int queue[NUM];
  int product;
  int consume;
} production;

int main()
{
  printf("使用共享内存控制信号量 模拟生产者消费者 模型\n");
  int fd;
  /*设置共享内存来储存生产消费状态和产品数组*/
  production *p_map;
  fd = open(FILENAME, O_CREAT | O_RDWR, 00777);
  p_map = (production *)mmap(NULL, sizeof(production), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  write(fd, " ", sizeof(production) * NUM);
  p_map->consume = 0;
  p_map->product = NUM;

  /*分出子进程分别生产消费*/
  if (fork())
  {
    /*生产者*/
    int p = 0, id = 0;
    while (1)
    {
      if((p_map->product) > 0)
      {
        --(p_map->product);
        (p_map->queue)[p] = ++id;
        printf("生产： %d\n", (p_map->queue)[p]);
        p = (p + 1) % NUM;
        ++(p_map->consume);
      }
      sleep(1);
    }
  } else {
    /*消费者*/
    int c = 0, i;
    while (1)
    {
      if ((p_map->consume) > 0)
      {
        --(p_map->consume);
        for (i = 0; i < NUM; i++)
        {
          printf("%d ", (p_map->queue)[i]);
        }
        putchar('\n');

        printf("消费： %d\n", (p_map->queue)[c]);
        (p_map->queue)[c] = 0;
        ++(p_map->product);
        c = (c + 1) % NUM;
      }
      sleep(3);
    }
  }
  close(fd);
  return 0;
}

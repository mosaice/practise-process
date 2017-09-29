#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 1000                                                            /* 实验环境 固定分配内存的值 */

/**
 * 内存区域块结构体
 * 为单个双向链表节点
 */
typedef struct _map {
  unsigned m_size;                                                              /* 当前块大小 */
  char *m_addr;                                                                 /* 当前块起始地址 */
  struct _map *next;                                                            /* 当前块下一个节点地址 */
  struct _map *prev;                                                            /* 当前块上一个节点地址 */
} map;

/**
 * 全局变量
 */
map *header;                                                                    /* map 链表的头节点地址 */
char *startAddr;                                                                /* 实验环境分配内存的起始地址 */
unsigned total = 0;                                                             /* 统计已经分配内存大小的变量 */
FILE *fp;                                                                       /* 写结果文件的指针变量 */

/**
 * [logMap 负责输入打印当前内存状态]
 * 并且负责整理 m_size == 0 的空节点的删除
 */
void logMap() {
  map *tempp = header;
  int i = 1;
  printf("总共内存: %d ,已经分配: %d \n", MAXSIZE, total);
  fprintf(fp, "总共内存: %d ,已经分配: %d \n", MAXSIZE, total);
  /**
   * 进行 m_size == 0 节点的移动整理
   * 1. 当该节点非头部节点，将其删除
   * 2. 当该节点为头部节点 且有后续节点，将后续节点的地址赋值给 头节点
   * 3. 当该节点为头部节点 且无后续节点，不做处理
   */
  do {
    if (!tempp->m_size) {
      if (tempp->prev) {
        tempp->prev->next = tempp->next;
      } else if (tempp->next) {
        header = tempp->next;
      }
    }
    tempp = tempp->next;
  } while(tempp);

  /* 重新归位到头节点进行 遍历 输入操作 */
  tempp = header;
  do {
    printf("空闲内存: %d 大小: %u, 起始地址: %u \n", i, tempp->m_size, tempp->m_addr);
    fprintf(fp, "空闲内存: %d 大小: %u, 起始地址: %u \n", i, tempp->m_size, tempp->m_addr);
    i++;
    printf("\n");
    fprintf(fp, "\n");
    tempp = tempp->next;
  } while(tempp);
}

/**
 * [fmalloc 用来模拟申请分配内存，采用的首次适应法]
 * @param  size [申请分配内存的大小]
 * @return      [0 (失败) || 分配成功后的地址]
 */
char *fmalloc(unsigned size) {
  /**
   * 首先进行，边界检测
   * 当 size 错误时直接返回 0
   */
  if (size > MAXSIZE) {
    printf("请输入小于1000的数值\n");
    fprintf(fp, "请输入小于1000的数值\n");
    return 0;
  }

  if (size + total > MAXSIZE) {
    printf("剩余空间不足\n");
    fprintf(fp, "剩余空间不足\n");
    return 0;
  }
  map *tempp = header;                                                          /* 局部变量 临时指针 */
  char *a;                                                                      /* 分配的指针变量 */
  /**
   * 采用首次适应法
   * 即第一次发现合适的满足内存就分配
   * 并对当前内存块地址与大小进行更新
   */
  do {
    if (size <= tempp->m_size) {
      tempp->m_size -= size;
      a = tempp->m_addr;
      tempp->m_addr += size;
      total += size;
      printf("分配成功,起始地址: %u\n", a);
      fprintf(fp, "分配成功,起始地址: %u\n", a);
      return a;
    }
    tempp = tempp->next;
  } while(tempp);

  printf("分配失败 没有足够大的单个内存块\n");
  fprintf(fp, "分配失败 没有足够大的单个内存块\n");
}

/**
 * [ffree  首次适应法对应的释放函数]
 * @param  size [释放内存区域的大小]
 * @param  addr [释放的起始地址]
 * @return      [0(失败) || 1(成功)]
 */
int ffree (unsigned size, char *addr) {
  /**
   * 初始化 参数检查
   * 对指针地址的数值进行比较或运算时，将其强制转换为int类型确保正确性
   */
  if ((int)startAddr > (int)addr) {
    printf("操作越界 请输入大于起始地址的数字\n");
    fprintf(fp, "操作越界 请输入大于起始地址的数字\n");
    return 0;
  }
  if (size > MAXSIZE) {
    printf("请输入小于1000的数值\n");
    fprintf(fp, "请输入小于1000的数值\n");
    return 0;
  }

  if (total < size) {
    printf("释放错误 超过已分配的内存\n");
    fprintf(fp, "释放错误 超过已分配的内存\n");
    return 0;
  }

  map *tempp = header;                                                          /* 遍历用的临时指针变量 */

  /**
   * 循环开始先进行异常检测
   * 发现异常条件时直接中断函数
   */
  do {
    /**
     *异常1. 节点的起始地址 < 释放目标的起始地址，同时 节点的结束地址 > 释放目标的起始地址
     *说明，释放目标的地址位于某一块空白内存区域中，表示本次释放的内存区域和未分配的地址中有部分重叠区域
     */
    if ((int)tempp->m_addr < (int)addr && (int)tempp->m_addr + tempp->m_size > (int)addr) {
      printf("释放错误 起始地址包含在其他内存块中\n");
      fprintf(fp, "释放错误 起始地址包含在其他内存块中\n");
      return 0;
    }
    /**
     *异常2. 节点的起始地址 > 释放目标起始地址，同时 节点的起始地址 < 释放区域的结束地址
     *说明，释放区域的区间过大，已经和其他空白区域重叠
     */
    if ((int)tempp->m_addr > addr && (int)tempp->m_addr < (int)addr + size) {
      printf("释放错误 内存大小超过界限\n");
      fprintf(fp, "释放错误 内存大小超过界限\n");
      return 0;
    }
    /**
     * 异常3. 释放起始位置已经为某个空白节点的起始位置
     * 说明，释放区域一定会和其他空白区域重叠
     */
    if ((int)tempp->m_addr == (int)addr) {
      printf("释放错误 起始地址已经为空的内存块地址\n");
      fprintf(fp, "释放错误 起始地址已经为空的内存块地址\n");
      return 0;
    }
    /* 匹配条件 1.节点的起始位置为释放区域的结束位置 */
    if ((int)tempp->m_addr == (int)addr + size) {
      map *ppp = header;
      /**
       * 选定当前匹配的节点后
       * 重新对其他节点进行循环检查
       * 确保其他节点不会存在异常情况
       */
      do {
        if ((int)ppp->m_addr < addr && (int)ppp->m_addr + ppp->m_size > (int)addr) {
          printf("释放错误 起始地址包含在其他内存块中2\n");
          fprintf(fp, "释放错误 起始地址包含在其他内存块中2\n");
          return 0;
        }

        if ((int)ppp->m_addr > (int)addr && (int)ppp->m_addr < (int)addr + size) {
          printf("释放错误 内存大小超过界限2\n");
          fprintf(fp, "释放错误 内存大小超过界限2\n");
          return 0;
        }
        ppp = ppp->next;
      } while(ppp);
      /**
       * 匹配条件 1的处理
       * 将当前空白节点起始地址设置为释放地址，并使其大小增加释放的大小
       */
      total -= size;
      tempp->m_addr = addr;
      tempp->m_size += size;
      return 1;
    }
    /* 当释放地址为空白内存节点的结束地址 */
    if ((int)addr == (int)tempp->m_addr + tempp->m_size) {
      /**
       * 进入匹配条件后
       * 同样先对其他空白内存节点进行异常条件检查
       * 确保不会出现超出边界
       */
      map *pp = header;
      do {
        /**
         * 匹配条件2.释放地址的起始地址为空白节点的结束地址，同时释放地址的结束地址为另一个节点的起始地址
         * 处理，将释放地址之前连接的节点的容量增加释放大小与后一节点之和
         * 同时将之前节点的下一节点连接到后一节点的下一节点，以对后一节点进行删除
         */
        if ((int)pp->m_addr == (int)addr + size) {
          total -= size;
          tempp->m_size = tempp->m_size + size + pp->m_size;
          tempp->next = pp->next;
          return 1;
        }
        if ((int)pp->m_addr > (int)addr && (int)pp->m_addr < (int)addr + size) {
          printf("释放错误 内存大小超过界限3\n");
          fprintf(fp, "释放错误 内存大小超过界限3\n");
          return 0;
        }
        pp = pp->next;
      } while(pp);
      /**
       * 匹配条件3.释放地址为空白节点的结束地址，但是释放地址的结束地址并没有越界到其他空白节点
       * 处理，为释放地址之前的空白节点增加容量
       */
      total -= size;
      tempp->m_size += size;
      return 1;
    }
    tempp = tempp->next;
  } while(tempp);

  /**
   * 匹配条件4，选择释放的内存区域属于两个相邻的空白节点之间，互相没有接触到边界
   * 处理，为这块释放的区域单独新增加一个节点插入到链表的最后
   */
  tempp = header;
  while (tempp->next) {
    tempp = tempp->next;
  }
  total-=size;
  map *mapp = malloc(sizeof(map));
  mapp->m_addr = addr;
  mapp->m_size = size;
  mapp->prev = tempp;
  mapp->next = NULL;
  tempp->next = mapp;
  return 1;
}

/**
 * [main 启动程序]
 * @param  argc [description]
 * @param  argv [description]
 * @return      [description]
 */
int main(int argc, char const *argv[]) {
  /**
   * 初始化工作
   * 分配实验环境空间内存并获取其实地址
   * 初始化链表表头
   */
  startAddr = malloc(MAXSIZE);
  header = malloc(sizeof(map));
  header->m_size = MAXSIZE;
  header->m_addr = startAddr;
  header->next = NULL;
  header->prev = NULL;

  /* 尝试打开文件记录 */
  if (!(fp = fopen("result.txt", "w"))) {
   printf("cannot open file!\n");
   return 0;
  }

  printf("请选择操作：分配内存(m) or 释放内存(f) or 退出(q)\n");
  printf("分配起始地址: %u\n", startAddr);
  fprintf(fp, "请选择操作：分配内存(m) or 释放内存(f) or 退出(q)\n");
  fprintf(fp, "分配起始地址: %u\n", startAddr);

  char cmdchar;                                                                 /* 单个命令字符变量 */
  unsigned size;                                                                /* 命令行输入的大小变量 */
  char *addr;                                                                   /* 命令行输入的地址变量 */

  /* 程序io主体 */
  while (1) {
    printf("等待命令\n");
    fprintf(fp, "等待命令\n");
    do {
      cmdchar = getchar();
      fprintf(fp, "%c\n", cmdchar);
    } while(cmdchar == '\n' || cmdchar == '\t' || cmdchar == ' ');

    switch (cmdchar) {
      case 'm':
      printf("输入需要分配的内存大小\n");
      fprintf(fp, "输入需要分配的内存大小\n");
      scanf("%u", &size);
      fprintf(fp, "%d\n", size);
      if (fmalloc(size)) logMap();
      break;
      case 'f':
      printf("输入需要释放的内存大小和地址,空格分隔\n");
      fprintf(fp, "输入需要释放的内存大小和地址,空格分隔\n");
      scanf("%u %u", &size, &addr);
      fprintf(fp, "%d %d\n", size, addr);
      if (ffree(size, addr)) logMap();
      break;
      case 'q':
      fclose(fp);
      exit(0);
      break;
    }
  }
  fclose(fp);
  return 0;
}


** _exit,exit和return的区别
_exit(int)要引入#include <unistd.h>, 用于直接退出进程
exit(int)要引入#include <stdlib.h>, 用于请求IO缓存后再退出进程
return, 用于函数返回

** #ifdef,#ifndef,#else,#endif的用法
用于条件执行代码和避免重复引入头文件
#+begin_src c
// 注释掉下面这句，就不会打印出debuging......了
#define DEBUG
#ifdef DEBUG
printf("debuging......");
#endif
#+end_src

*** 包装器#ifndef
#+begin_src
文件a.h
#include "b.h"
文件b.h
#include "a.h"
文件c.c
#include "a.h"
// 这样就会出现循环引入的问题，编译器会报#include nested too deeply
// 这时只需将b.h改成
#ifndef INCLUDED_A
#define INCLUDED_A
#include "a.h"
#endif
#+end_src

** isdigit, isxdigit, isspace
位于#include <ctype.h>中的宏，用于检查参数是否为数字0到9.
isxdigit则检查参数是否为16进制有效数字
isspace 判断入参是否为空格符或\t\n\v\f\r字符。


** fprintf

** getc, ungetc

#+begin_src
/* @module <stdio.h>
 * @description 从字符串中格式化读取参数
 * @param {char *} str - 源字符串
 * @param {char *} fmt - 格式化字符串
 * @more {pointer} - 存储参数的指针
 */
int sscanf(const char *str, const char *fmt, ...)
#+end_src
示例：
#+begin_src
int day, year;
char *weekday;
char month[20];
char dtm[100] = "Saturday March 25 1989";
sscanf(dtm, "%s %s %d %d", weekday, month, &day, &year);
#+end_src

#+begin_src
/* @module <stdio.h>
 * @description 从流中获取读取一行或n-1个字符串到str中。
 * @parma {char *} str - 读取内存将存储到str中
 * @param {int} n - 读取的最大字符数（包含最后的空字符）
 * @param {FILE *} stream - 源流
 * @return {char *} 读取成功则和str内容一样，否则为空指针
 */
char *fgets(char *str, int n, FILE *stream)
#+end_src
示例：
#+begin_src
#include <stdio.h>
#define N 60
int main(){
  FILE *fp;
  char str[N];
  fp = fopen("file.txt", "r");
  if (fp == NULL){
    perror("error on file opening!");
    exit(-1);
  }
  if (fgets(str, N, fp) != NULL){
    puts(str);
  }
  fclose(fp);
  
  return 0;
}
#+end_src

static
const

C语言没有C++和C#的命名空间，也没有Java的包机制，因此必须制定命名规则来避免可能出现的命名冲突。

静态变量的问题：
1. 多线程共享同一个静态变量，需要加锁处理并发冲突;
2. 编译器无法递归运行，因为递归存在重复#include的问题，那么之前引入的静态变量就会被覆盖。

未赋值变量很有可能默认值为0, 因此将有效值设置为0xCC或1, 以便后续排查未赋值变量。

** 枚举Enum
#+begin_src
// 定义枚举
// 默认从0开始，后续元素递增1
enum COLOR {
  RED,
  GREEN = 3,
  BLUE
};
// 声明变量
enum COLOR curr_color;
// 赋值
curr_color = BLUE;

// 定义枚举并声明变量
enum COLOR {
  RED,
  GREEN = 3,
  BLUE
} curr_color;

// 定义匿名枚举并声明变量
enum {RED, GREEN = 3, BLUE} curr_color;

// 遍历枚举元素
// 输出：-> 0 -> 3 -> 4
for (curr_color = RED; curr_color <= BLUE; ++curr_color){
  printf("-> %d ", curr_color);
}

// swtich语句
switch (curr_color){
  case RED:
    break;
  case BLUE:
    break;
  default:
    ...
}

// int类型转换为枚举
int a = 0;
curr_color = (enum COLOR) a;
#+end_src

** 指针
一个存储内存地址的变量。
指针的数据类型是代表内存地址的16进制数，而声明中的类型是指地址对应变量或常量的数据类型。
#+begin_src
int var = 1;
int *ip;   // 声明指针
ip = &var; // &取址符，获取var的地址存放到ip上
printf("%p \n", &var);
printf("%p \n", ip);
printf("%d \n", *ip); // *可通过指针获取内存空间存放的值

#include <stdio.h>
int *ip2 = NULL:  // 空指针，内存地址为0x0。表示指向一个不可访问的内存位置（地址为0的内存空间是操作系统保留的，应用程序无法访问）
if (ip2){
  // 非空指针
}
else{
  // 空指针
}
#+end_src

*** 指针的指针
#+begin_src
#include <stdio.h>

int var = 1;
int *iptr = NULL;
int **pptr = NULL; // 声明指针的指针

iptr = &var;
pptr = &pptr;

// *iptr == **pptr
#+end_src

*** 指针作为函数返回值
#+begin_src
int *foo(){
  int var = 1;
  static int *iptr = &var;
  
  return iptr;
}

int *val_ptr = foo();
prinf("%d \n", *val_ptr);
#+end_src
注意：
不能以局部变量地址作为函数返回值，除非局部变量声明为static。
原因：局部变量是存储在内存的栈区内，函数调用完成时局部变量所属的内存空间就会被释放。而static变量会存储在静态数据区，不会随着函数调用完成而释放。

*** 函数指针
用于调用函数、传递参数。
#+begin_src
int max(int x, int y){
  return x > y ? x : y;
}
// 声明和定义函数指针
int (* p)(int, int) = max;
p(p(1,2), 3);

// 作为参数
int most_of_three(int x, int y, int z, int (*p)(int, int)){
  return p(p(x, y), z);
}
most_of_three(1, 2, 3, max);
#+end_src

** 结构体
#+begin_src
// 定义结构体
struct Book {
  char title[50];
  int book_id;
};
// 声明结构体变量
struct Book book;

// 定义结构体并声明变量
struct {
  char title[50];
  int book_id;
} book;

// 作为入参
int get_book_id(struct Book book){
  return book.book_id;
}
get_book_id(book);

// 指针入参
int get_book_id(struct Book *book){
  return book->book_id;
}
get_book_id(&book);

// 相互嵌套的结构体，需要使用结构体不完全声明
struct B; // 结构体B中包含指向结构体A的指针，而结构体A内也包含指向结构体B的指针

struct A{
  struct B *b;
}
struct B{
  struct A *a;
}
#+end_src

Q:使用指针和不使用指针的区别？

** 变量
#+begin_src
// 声明并定义，但没有初始化值
// 已经为变量a分配内存空间，所以为定义
int a;

// 声明而已
// 没有为变量a分配内存空间
extern int a;
#+end_src
变量声明的作用：用于告诉编译器变量的类型和名称均存在，而链接时则需要变量的定义了。

** 共用体
#+begin_src
// 定义共用体Data
union Data {
  int i;
  float f;
  char str[10];
};

// 定义变量
union Data data;

// 设置成员
data.i = 1;
data.f = 1.1;
data.str = "abcd";

// 读取成员
printf("%s\n", data.str);
#+end_src

** 头文件
*** 作用
    包含常量、全局变量、函数声明和宏定义，被多个源文件引用。
*** 类型
1. 编译器自带的头文件
  引入方式：#include <file>，从系统目录的标准列表中引入file。
2. 程序员编写的头文件
  引入方式：#include "file"，从当前目录中引入file。
*** 包装器#ifndef
为防止多次引入同一个头文件（编译器会报错）
#+begin_src
// a.h文件下
#ifndef A_HEADER
#define A_HEADER

#include b.h

#endif

// b.h文件下
#ifndef B_HEADER
#define B_HEADER

#include a.h

#endif

// mian.c文件下
#include "a.h"
#include "b.h"
#+end_src
技巧：建立global.h，然后引入所有头文件，然后c文件则引入global.h即可。
*** 条件引入
#+begin_src
#include SYSTEM_H
#+end_src
然后通过gcc的-D选项设置宏SYSTEM_H的值。

** 异常处理
函数返回1或NULL表示发生异常，而具体的异常代码则存放在全局变量errno中，<errno.h>头文件中包含各种的异常代码。
注意：程序初始化时要将errno置为0.
perror(const char *str)，回显`${str}: ${errno|文本形式}`
char * strerror(int errno),返回errno的文本形式
示例：
#+begin_src
#include <stdio.h>
#include <errno.h>

extern int errno;

int main (){
  FILE *fp;
  int errnum;
  pf = fopen("unexists.txt", "rb");
  if (pf == NULL){
    errnum = errno;
    perror("Error");
    printf(strerror(errno));
    
    exit(EXIT_SUCCESS);
  }

  exit(EXIT_FAILURE);
}
#+end_src

** 函数可变实参
使用<stdarg.h>来实现
#+begin_src
#include <stdio.h>
#include <stdarg.h>

int sum(int x, int y, int num, ...){
  int sum = 0;

  // 初始化可变参数列表valist
  // num为实际可变参数个数
  va_list valist;
  va_start(valist, num);

  int i;
  for (i = 0; i < num; ++i){
    sum += va_arg(valist, i); // va_arg根据索引取可变入参
  }
  sum += x + y;
  
  // 释放列表空间
  va_end(valist);

  return sum;
}
sum(1, 2, 2, 3, 4); // 1+2+3+4 = 10
#+end_src

** 动态内存管理
在函数在<stdlib.h>中
#+begin_src
/* 在内存中动态分配num*size个连续的内存空间，并将每个字节设置为0
 */
void *calloc(int num, int size)

/* 释放address指向的内存块
 */
void free(void *address)

/* 在堆区分配num大小的内存空间，空间的值不会被初始化。
 */
void *malloc(int num)

/* 从新分配address指向的内存块，并增加或减少到newsize的大小
 */
void *realloc(void *address, int newsize)
#+end_src
示例：
#+begin_src
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
  char *str;

  str = malloc(10*sizeof(char)); // 或calloc(10, sizeof(char))
  if (str == NULL) {
    perror("error");
    exit(EXIT_FAILURE);
  }
  strcopy(str, "abcdefg");
  printf(str);
  
  // 扩充空间
  realloc(str, 20*sizeof(char));
  if (str == NULL) {
    perror("error");
    exit(EXIT_FAILURE);
  }
  strcat(str, "ccccc");
  printf(str);
  
  // 释放空间
  free(str);
  
  return 0;
}
#+end_src

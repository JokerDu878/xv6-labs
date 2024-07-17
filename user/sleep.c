#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char const *argv[])
{
  if (argc != 2) { //参数错误
    fprintf(2, "usage: sleep <time>\n");//  2不是一个普通的文件流指针，而是一个特殊的文件描述符（file descriptor），它代表了标准错误输出（stderr） 
    exit(1);
  }
  int time = atoi(argv[1]); 
  sleep(time);
  printf("sleep %d \n." , time);
  exit(0);
}

// int main(int argc , char const *argv[]){
//     if(argc !=2 ){//参数错误
//      printf("Error, Example: sleep 2 ");
//      exit(1);
//     }

//     sleep(atoi(argv[1]));
//     exit(0);

// }
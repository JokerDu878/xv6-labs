#include "kernel/types.h"
#include "user/user.h"

#define RD 0
#define WR 1

const uint INT_LEN = sizeof(int);

/**
 * @brief 读取左邻居的第一个数据
 * @param lpipe 左邻居的管道符
 * @param pfirst 用于存储第一个数据的地址
 * @return 如果没有数据返回-1,有数据返回0
 */

int lpipe_first_data(int lpipe[2], int *dst)
{
  if (read(lpipe[RD], dst, sizeof(int)) == sizeof(int)) {
    printf("prime %d\n", *dst);
    return 0;
  }
  return -1;
}

/**
 * @brief 读取左邻居的数据，将不能被first整除的写入右邻居
 * @param lpipe 左邻居的管道符
 * @param rpipe 右邻居的管道符
 * @param first 左邻居的第一个数据
 */
void transmit_data(int lpipe[2], int rpipe[2], int first)
{
  int data;
  // 从左管道读取数据
  while (read(lpipe[RD], &data, sizeof(int)) == sizeof(int)) {
    // 将无法整除的数据传递入右管道
    if (data % first)
      write(rpipe[WR], &data, sizeof(int));
  }
  close(lpipe[RD]);
  close(rpipe[WR]); //及时关闭，不然会导致资源浪费
}


/**
 * @brief 寻找素数
 * @param lpipe 左邻居管道
 */
void primes(int lpipe[2])
{
  close(lpipe[WR]);
  int first ; 
  if(lpipe_first_data(lpipe , &first) == 0){
    int p[2];
    pipe(p);
    transmit_data(lpipe,p,first); //右边

    if(fork() == 0){
        primes(p); // 递归的思想，但这将在一个新的进程中调用
    }else{
        close(p[RD]);
        wait(0);
    }

  }
  exit(0);
}

int main(int argc, char const *argv[])
{
  int p[2];
  pipe(p);

  for (int i = 2; i <= 35; ++i) //写入初始数据
    write(p[WR], &i, INT_LEN);

  if (fork() == 0) {
    primes(p);
  } else {
    close(p[WR]);
    close(p[RD]);
    wait(0);
  }

  exit(0);
}


// void func(int * input , int num){

//     if(num == 1){
//         printf("prime %d\n" , *input);
//         return;
//     }
//     int p[2] , i;
//     int prime = *input ;
//     int temp;

//     printf("prime %d\n" , prime);
//     pipe(p);
//     if(fork() == 0){ //子进程
//         for( i=0; i<num ;i++){
//             temp = *(input+i);
//             write(p[1] , (char*)(&temp) , 4);
//         }
//         exit(0);
//     }
//     //父进程
//     close(p[1]); 
//     if(for() ==0){ //又进来了
//         int counter =0;
//         char buffer[4];
//         while(read(p[0],buffer , 4) !=0){
//             temp = *((int*)buffer);
//             if(temp%prime !=0){
//                 *input = temp;
//                 input+=1;
//                 counter++;
//             }
//         }
//         func(input-counter , counter);
//         exit(0);

//     }
//     wait(0);
//     wait(0);


// }




// int main(int argc , const char * argv[]){
//     int input[34];
//     int i =0;
//     for( ; i<34;i++){
//         input[i] = i+2;
//     }
// }
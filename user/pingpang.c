#include "kernel/types.h"
#include "user/user.h"
 

int main(int argc , const char * argv[]){

    int p1[2]; //管道文件描述符
    int p2[2];

    pipe(p1) ; //创建一个管道
    pipe(p2) ;


    char buff[] = {'x'};
    long length = sizeof(buff);

    if(fork()==0){  //子进程
        int pid = getpid();
        close(p1[1]);//不写入p1
        close(p2[0]); //不读取p2
        if(read( p1[0], buff, length) != length){
            printf(" a-->b read error!");
            exit(1);
        }

        printf("%d: received ping\n",pid);

        if(write(p2[1],  buff, length) != length){
            printf("a<---b write error!");
			exit(1);
        };
        exit(0);
    }

    close(p1[0]);//不读取p1
    close(p2[1]); //不写入p2

    if(write(p1[1], buff , length) != length){
        printf("a--->b write error!");
		exit(1);
    }
    if(read( p2[0], buff, length)!= length){
        printf("a<---b read error!");
		exit(1);
    };


    printf("%d: received pong\n",getpid());

    wait(0);
	exit(0);

    
}
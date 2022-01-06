#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int func(int*,int);

int
main(int argc, char *argv[])
{
    int p[2];
    pipe(p);
    if(fork()==0){
        //子进程
        //不需要用到写

        close(p[1]);
        //读取数据出来
        func(p,0);
    }
    else
    {
        //不需要用到read，先关掉
        close(p[0]);
        //父进程
        //向管道写入数据
        int arr[34] = {};
        for(int i =0;i<34;i++){
            arr[i]=i+2;
        }
        write(p[1],arr,34*sizeof(int));
        close(p[1]);
        //父进程需要等待子进程退出，
        wait((int*) 0);
        exit(0);
    }
    exit(0);
    return 0;
}

int
func(int* p,int i)
{
    if(i==11) return 0; 
    int pp[2];
    pipe(pp);
    if(fork()==0)
    {   
        //子进程不需要写
        close(pp[1]);
        func(pp,i+1);
    }
    else
    {
        //父进程不需要进行读操作
        close(pp[0]);
        int* getFromLeft=(int*)malloc(sizeof(int)); 
        read(p[0],getFromLeft,sizeof(int));
        printf("prime %d============%d\n",*getFromLeft,p[0]);
        int* n =(int*)malloc(sizeof(int));
        while(read(p[0],n,sizeof(int)))
        {
            if((*n)%(*getFromLeft)!=0)
            {
                write(pp[1],n,sizeof(int));
            }
        }
        close(p[0]);
        close(pp[1]); 
    }
    exit(0);
}
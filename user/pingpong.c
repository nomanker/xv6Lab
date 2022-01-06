#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int 
main(int argc, char *argv[])
{
    int p[2];
    int c[2];
    pipe(p);
    pipe(c);
    int pid=fork();
    if(pid==0){
        //进入子进程
        //关闭标准的输入
        char* s="";
        read(c[0],s,1);
        close(c[0]);
        printf("%d: received ping\n",getpid());
        write(p[1],"b",1);
        close(p[1]);
        exit(0);
    }else{
        //父进程
        char* s="";
        write(c[1],"a",1);
        close(c[1]);
        read(p[0],s,1);
        printf("%d: received pong\n",getpid());
        close(p[0]);
    }
     exit(0);
}
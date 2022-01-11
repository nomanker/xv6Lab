#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

int main(int argc,char *argv[])
{
    char buf[512];
    char* full_argv[MAXARG];
    int i;
    int len;
    if(argc<2)
    {
        fprintf(2,"usage:xargs your_command\n");
        exit(1);
    }

    if(argc+1>MAXARG)
    {
        fprintf(2,"too many args\n");
        exit(1);
    }
    //跳过第一个参数xargs
    for(i=1;i<argc;i++)
    {
        full_argv[i-1]=argv[i];
    }
    //最后一个需要填充0
    full_argv[argc]=0;
    while(1)
    {
        i=0;
        //read a line
        while(1)
        {
            len = read(0,&buf[i],1);
            if(len==0||buf[i]=='\n') break;
            i++;
        }
        if(i==0) break;
        buf[i]=0;
        full_argv[argc-1]=buf;
        if(fork()==0)
        {
            //子进程
            exec(full_argv[0],full_argv);
            exit(0);
        }
        else 
        {
            wait(0);
        }
    }
    exit(0);
}
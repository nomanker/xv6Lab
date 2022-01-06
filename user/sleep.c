#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int 
main(int argc, char *argv[])
{
    int i;
    if(argc <=1){
        fprintf(2, "Usage: sleep for some times...\n");
        exit(1);
    }
    if(argc>2){
        fprintf(2,"Usage: sleep function only need one arg...\n");
        exit(1);
    }
    for(i=1;i<argc;i++){
        sleep(atoi(argv[i]));
    }
     exit(0);
}
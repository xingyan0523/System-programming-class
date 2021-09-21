#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <unistd.h>



char user[100][100];
int usernum = 0;

bool member(char *str){
    for(int i = 0; i < usernum; i++){
        if(!strcmp(user[i], str)){
            return true;
        }
    }
    return false;
}

int main(){
    
    FILE *fp = fopen("./ronSvr.db", "r+");
    
    while(fgets(user[usernum], 100, fp)){
        char *ptr = strchr(user[usernum], '\n');
        if(ptr)
            *ptr = '\0';
        //printf("%s\n",user[usernum]);
        usernum++;
    }
    char name[100];
    bool in = false;
    printf("請問使者名稱：\n");
    while(fgets(name, 100, stdin)){
        char *ptr = strchr(name, '\n');
        if(ptr)
            *ptr = '\0';
        if(member(name)){
            printf("以順利登入\n");
            int pid = fork();
            if(!pid)
                while(1){
                    int sec = rand() % 5 + 1;
                    sleep(sec);
                    printf("pid = %d, %s, %d sec\n", getpid(), name, sec);
                }

        }
        else{
            printf("無法登入\n");
            

        }


    }







    return 0;
}
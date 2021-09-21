#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <linux/limits.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <ctype.h>
#include <stdbool.h>
#include <fcntl.h>


char lazyBox_path[4096];

int lazyshell_main() { //1
    while(1) {
        char buf[4096];
        char cmd[4096] = "";
        printf("lazybox$");
        fgets(buf, 4096, stdin);

        char *space = buf;
        while(*space == ' '){
            space++;
        }
        
        strcat(cmd, space);

        char *line = strchr(cmd, '\n');
        if(line){
            *line = '\0';
        }

        if(!strncmp("exit", cmd, 4)){//1
            exit(0);
        }
        else if(!strncmp("cd", cmd, 2)){//2
            char path[PATH_MAX];
            char *ptr = cmd + 2;
            while(*ptr == ' '){
                ptr++;
            }
            strcpy(path, ptr);
            chdir(path);
        }
        else if(!strncmp("stat", cmd, 4) || !strncmp("ln", cmd, 2) || !strncmp("chown", cmd, 5)){
            char buf2[4096] = "./";
            strcat(buf2, cmd);
            system(buf2);
        }
        else{
            system(cmd);
        }
        
    }
}

int ln_main(int argc, char **argv){
    if(!strcmp(argv[1], "-s")){
        symlink(argv[2], argv[3]);
    }
    else{
        link(argv[1], argv[2]);
    }
}

int stat_main(int argc, char **argv) {//4
    char cmd[PATH_MAX];
    strcpy(cmd, lazyBox_path);
    strcat(cmd, " ");
    strcat(cmd, argv[0]);
    char path[PATH_MAX] = "";
            
    struct stat statbuf;

    stat(argv[1], &statbuf);

	printf("%s\natime: %smtime: %sctime: %s", getpwuid(statbuf.st_uid)->pw_name, 
    ctime(&statbuf.st_atime), ctime(&statbuf.st_mtime) ,ctime(&statbuf.st_ctime));

}

int chown_main(int argc, char **argv){
    int fd = open("sudo_success", O_WRONLY);
    if(fd == -1){
        char input[32];
        printf("你要執行的是特權指令,確定的話,請輸入『yes』,否則按下『enter』終止操作\n");
        fgets(input, 32, stdin);
        if(input[0] == '\n'){
                return 0;
        }
        else if(strncmp(input, "yes", 3)){
            return 0;
        }
        system("touch sudo_success");
    }
    
    struct timespec file_t, current_t;
    struct stat statbuf;

    stat("sudo_success", &statbuf);
    file_t = statbuf.st_ctim;

    clock_gettime(CLOCK_REALTIME, &current_t);

    if (current_t.tv_sec - file_t.tv_sec > 30) {
        char input[32];
        printf("你要執行的是特權指令,確定的話,請輸入『yes』,否則按下『enter』終止操作\n");
        fgets(input, 32, stdin);
        if(input[0] == '\n'){
                return 0;
        }
        else if(strncmp(input, "yes", 3)){
            return 0;
        }
    }
    system("touch sudo_success");

    int uid = atoi(argv[1]);
    seteuid(0);
    chown(argv[2], uid, uid);
}

int main (int argc, char **argv) {
    getcwd(lazyBox_path, 4096);

    if(!strncmp(argv[0] + 2, "lazyshell" , 9) || !strncmp(argv[0] + 2, "lazybox" , 7)){//1 2
        lazyshell_main();
    }
    else if(!strcmp(argv[0] + 2, "ln")){//3
        ln_main(argc, argv);
    }
    else if(!strcmp(argv[0] + 2 , "stat")){ //4
        stat_main(argc, argv);
    }
    else if(!strcmp(argv[0] + 2 , "chown")){
        chown_main(argc, argv);
    }
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <linux/limits.h>

int main (int argc, char **argv){
    char path[PATH_MAX] = "";
    char cat[PATH_MAX] = "cat ";

    strcat(path, argv[1]);
    strcat(cat, path);

    struct stat filestat;
    stat(path, &filestat);

    time_t timebuf = filestat.st_mtim.tv_sec;
    printf("mtime: %s", ctime(&timebuf));
    system(cat);
   
    while(1){
        stat(path, &filestat);
        if(timebuf != filestat.st_mtim.tv_sec){
            printf("\n-----------------------------------\n");
            printf("new mtime: %s", ctime(&filestat.st_mtim.tv_sec));
            printf("old mtime: %s", ctime(&timebuf));
            printf("-----------------------------------\n");
            
            system(cat);
        }
        timebuf = filestat.st_mtim.tv_sec;
    }
    return 0;
}
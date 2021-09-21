#include <time.h>
#include <fcntl.h>
#include <stdio.h>
#include <assert.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/inotify.h>

#define BUF_LEN (10 * (sizeof(struct inotify_event) + NAME_MAX + 1))

int InotifyEvent(struct inotify_event *i) {
    if (i->mask & IN_CLOSE_WRITE) { printf("IN_CLOSE_WRITE "); return 1;}
	if (i->mask & IN_MODIFY) { printf("IN_MODIFY "); return 1;}    
    return 0;
}

void getMTime(int fd, struct tm* tm) {
	struct stat statbuf;
	struct tm t;
	char buf[1000];
	fstat(fd, &statbuf);
	tzset();
	localtime_r(&(statbuf.st_mtime), tm);
}


int main(int argc, char **argv){
    int inotifyFd, wd, j;
    char cat[PATH_MAX] = "cat ";
    char buf[BUF_LEN];
    char timebuf[128];
    char timebuf2[128];
    int numRead;
    char *p;
    struct inotify_event *event;
    
    strcat(cat, argv[1]);
    struct stat filestat;
    stat(argv[1], &filestat);
    struct tm last_mtime, cur_mtime;
    

    inotifyFd = inotify_init();        
    

    wd = inotify_add_watch(inotifyFd, argv[1], IN_ALL_EVENTS);
    getMTime(wd, &cur_mtime);
    getMTime(wd, &last_mtime);
	strftime(timebuf, 1000, "%F %T", &cur_mtime);
	strftime(timebuf2, 1000, "%F %T", &last_mtime);
	printf("這次修改時間：%s, 上次修改時間：%s\n", timebuf, timebuf2);
    system(cat);

    
    while(1) {
        numRead = read(inotifyFd, buf, BUF_LEN);

        for (p = buf; p < buf + numRead; ) {
            event = (struct inotify_event *) p;
            if(InotifyEvent(event)){
                stat(argv[1], &filestat);
                getMTime(wd, &cur_mtime);
                strftime(timebuf, 1000, "%F %T", &cur_mtime);
                printf("這次修改時間：%s, 上次修改時間：%s\n", timebuf, timebuf2);
                getMTime(wd, &last_mtime);
                strftime(timebuf2, 1000, "%F %T", &last_mtime);

                system(cat);
            }

            p += sizeof(struct inotify_event) + event->len;
        }
    }

    return 0;
}
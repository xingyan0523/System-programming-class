#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include <sys/types.h>
#include <unistd.h>


int main(int argc, char* argv[]) {
	int fd;
	int ret;
	int offset;
    char buf[4096];
    //打開lockf.db檔案
	fd = open("./lockf.db", O_RDWR, S_IRUSR | S_IWUSR);
	printf("fd = %d is opened\n", fd);
    //使用lockf對文件上鎖，長度為4byte
    ret = lockf(fd, F_LOCK, 4);
    if (ret != 0)
        perror("flock");
    
	for(int i = 0; i < 1000; i++){//循環1000次
        lseek(fd, 0, SEEK_END);//將檔案指標移動到文件結尾
        lseek(fd, -4, SEEK_CUR);//往前4個byte（四位數數字）
        read(fd, buf, 4);//得取4個byte存到buf
        sscanf(buf, "%d", &offset);//從buf裡讀取整數儲存到offset
        
        lseek(fd, 0, SEEK_END);//將檔案指標移動到文件結尾
        lseek(fd, offset, SEEK_CUR);//往後移動offset個byte
        sprintf(buf, "%d", offset + 1);//將offset+1印入buf
        write(fd, buf, 4);//將buf的內容寫入檔案
        
        usleep(10000);//程式在此等待0.01s(10000ms)
	}

	printf("end\n");
	return 0;
}
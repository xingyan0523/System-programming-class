#define _DEFAULT_SOURCE
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <stddef.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <linux/limits.h>

int filetype[1000];
char fileSymbol[1000];

//準備統計目錄中到底有多少種檔案型別，如果有該型別在filetype[X]上設定為1，該型別的代表字放在fileSymbol
void initFileType() {
    for (int i = 0; i < 1000; i++) {
        filetype[i] = -1;
    }
    /*
    DT_BLK      This is a block device. 「b」
    DT_CHR      This is a character device. 「c」
    DT_DIR      This is a directory. 「d」
    DT_FIFO     This is a named pipe (FIFO). 「f」
    DT_LNK      This is a symbolic link. 「l」
    DT_REG      This is a regular file. 「-」
    DT_SOCK     This is a UNIX domain socket. 「s」
    DT_UNKNOWN  The file type could not be determined. 「U」
    */

    fileSymbol[DT_BLK] = 'b';
    fileSymbol[DT_CHR] = 'c';
    fileSymbol[DT_DIR] = 'd';
    fileSymbol[DT_FIFO] = 'f';
    fileSymbol[DT_LNK] = 'l';
    fileSymbol[DT_REG] = '-';
    fileSymbol[DT_SOCK] = 's';
    fileSymbol[DT_UNKNOWN] = 'U';
    
}


void printFileType() {
    printf("檔案種類：");
    for (int i=0; i< 1000; i++) {
        if(filetype[i] == 1)
            printf("%c", fileSymbol[i]);
    }
    printf("\n");
}

//回傳某個檔案的大小
int readSize(char* pathname) {
    struct stat buf;
    assert(stat(pathname, &buf) == 0);
    return buf.st_size;

}

//使用遞迴計算某個目錄中的所有正規檔案的大小，並統計到底有多少種檔案型別
long myCountDir(char* path) {
    long size = 0; 
    //打開該目錄
    DIR* dirp = opendir(path);
    //讀取該目錄的第一個「物件」
    struct dirent* ent = readdir(dirp);
    while (ent) {
        //『這個目錄』及『上一層目錄』跳過不處理
        if (!strcmp(ent->d_name, "." ) || !strcmp(ent->d_name, ".." )) {
            ent = readdir(dirp);
            continue;
        }
        //設定有這種檔案型別
        filetype[ent->d_type] = 1;
        //製造『路徑/名』
        //如果使用者的輸入是「/」怎麼辦？，例如：「//home」會發生錯誤嗎？1不會
        char pathname[PATH_MAX]="";
        strcat(pathname, path);
        strcat(pathname, "/");
        strcat(pathname, ent->d_name);
        printf("%s\n", pathname);
        if(strstr(pathname, "user") && strstr(pathname ,"run")){ 
            //在/run/user底下因為特殊問題為產生bug，故在此先跳過不處理
            return 0;
        }
                
        
        if (ent->d_type == DT_REG) { 
            //如果是正規檔案->讀取他的大小
            size += readSize(pathname);
        } 
        else if (ent->d_type == DT_DIR) { 
            //如果是目錄->呼叫遞迴往更下層目錄尋找檔案    
            size += myCountDir(pathname); 
        }
        ent = readdir(dirp);
    }
    closedir(dirp);
    return size;
}

int main(int argc, char** argv) {
    setuid(0);
    initFileType();
    printf("授課老師（羅習五）的生日是：1990/04/10\n總共大小：%ld byte\n", myCountDir(argv[1]));
    printFileType();
    return 0;
}

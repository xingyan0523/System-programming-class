#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
    //讀取檔案名稱和buffer大小
    FILE *input = fopen(argv[1], "r");
    FILE *output = fopen(argv[2], "w");
    long int bufsize = atoi(argv[3]);
    //使用setvbuf設定input, output的buffer
    char *bufIn = (char*)malloc(bufsize);
    char *bufOut = (char*)malloc(bufsize);
    setvbuf(input, bufIn, _IOFBF, bufsize);
    setvbuf(output, bufOut, _IOFBF, bufsize);
    //配置一個陣列用來存word
    char *word = malloc(sizeof(char) * 80);;
    int wordlen = 0;
    int linepos = 0;
    
    while (1){
        char inputchar = getc(input);//讀取一個字元
        if (inputchar == ' ' || inputchar == '\n' || inputchar == EOF){//遇到這些狀況相當於一個word的結尾
            word[wordlen] = ' ';//在word的結尾加上空白
            wordlen++;
            word[wordlen] = '\0';//在word的結尾加上結尾

            if(linepos + wordlen > 79){//判斷當前的行數加上新的word會不會超過(79 + '\n' = 80)
                putc('\n', output);//若超過就換行
                linepos = 0;//新的一行從頭開始
            }
            fprintf(output,"%s", word);//將word寫入文件
            linepos += wordlen;//加上word的長度
            wordlen = 0;//word長度歸0
            if (inputchar == EOF)//如果到EOF就結束迴圈
                break;
        }
        else{//目前不是word的結尾則把字元加入word
            word[wordlen] = inputchar;
            wordlen++;
        }
    }
    return 0;
}
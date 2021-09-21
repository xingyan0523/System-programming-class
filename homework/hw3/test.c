#include<stdio.h>

int main (){
    int num = 3500;
    int sum = 4;
    for(int i = 0; i < 1000; i++){
        sum += num;
        sum += 4;
        num += 1;

    }
    printf("%f\n", sum /1048576.);//1Mib = 1048576byte
    return 0;

}
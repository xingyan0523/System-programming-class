#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <signal.h> //引進 signal
#include <unistd.h> //引進 nice

#include <sys/resource.h>//引進 getpriority()
#include <time.h> //引進 clock_gettime
long long int cpp;
//開始及結束時間
struct timespec start_time, end_time;

//將timespec轉成nanoseconds
long ts_to_long(struct timespec t) {
	return t.tv_sec * 1000000000 + t.tv_nsec;
}

//鬧鐘的時間到了，要做什麼事情？
void alarmHandler(int signo) {
        //printf("cpp = %lld\n", cpp);
        printf("%lu nanoseconds!\n", ts_to_long(end_time) - ts_to_long(start_time));
        exit(0);
}

/*****
        程式碼和makefile，
        助教執行『sudo make』指令後，
        必須自動產生nice_testing，
        nice_testing要自動fork出一個child，
        child和parent的優先等級相差5。
******/

int main(int argc, char** argv) {
        
        int nice_v=atoi(argv[1]); //讀入nice的參數
        int childPid = fork();  //產生二個行程
        int c_pid=0,p_pid=0;
        int c_nice=0,p_nice=0;//紀錄父子行程的nice值
        if (childPid > 0) {     //養我們的雙親
                p_pid=getpid();
                printf("parent pid=%d\n",p_pid);
                nice(nice_v);   //修改parent的nice值
                p_nice=getpriority(PRIO_PROCESS, p_pid);//回傳值 就是指定父行程的 nice值 
                printf("parent nice=%d\n",p_nice);
        } else {
                //child不用特別處理
                c_pid=getpid();
                printf("child pid=%d\n",c_pid);
                c_nice=getpriority(PRIO_PROCESS, c_pid);//回傳值 就是指定子行程的 nice值 
                printf("child nice=%d\n",c_nice);               
        }
        //底下的程式碼無論child是否大於0都會執行
        //設定鬧鐘（SIGALRM）叫的時候，『作業系統』呼叫 alarmHandler
        signal(SIGALRM, alarmHandler);
        //把鬧鐘的時間定在1秒鐘以後
        clock_gettime(CLOCK_MONOTONIC, &start_time);
        alarm(1);
        //不斷地cpp++
        while (1) {
                //cpp++;
                clock_gettime(CLOCK_MONOTONIC, &end_time);
        }
}
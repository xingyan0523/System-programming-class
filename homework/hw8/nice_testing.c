#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>

long long int cpp;
int childPid;

void alarmHandler(int signo) {
    if(childPid)
        printf("parent: cpp = %lld\n", cpp);
    else
        printf("child:  cpp = %lld\n", cpp);
    exit(0);
}

int main() {
    cpu_set_t set;
	CPU_ZERO(&set);
	CPU_SET(1, &set);
    sched_setaffinity(0, sizeof(set), &set);
    int nice_p = 5;
    
    childPid = fork(); //產⽣⼆個⾏程
    if (childPid) //parent
        nice(nice_p); 

    signal(SIGALRM, alarmHandler);
    alarm(1);
    
    while(1)
        cpp++;
}
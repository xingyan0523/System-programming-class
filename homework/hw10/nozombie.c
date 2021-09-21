#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
	int pid = fork();
	if (pid == 0) {	
		for (int i = 0; i < 100; i++) {
			int pid2 = fork();
			if (pid2 == 0) {	//child
				printf("child %2d 開始等待\n", i);
				sleep(i+1);
				printf("child %2d 告辭了\n", i);
				exit(0);
			} else {
				//parent
				continue;
			}
		}
		exit(0);	
	} else {
		int wstatus;
		wait(&wstatus);
	}
	return 0;
}

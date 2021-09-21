#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
	char* const argv[5] = {"ls", "-alh", "/", NULL};
	int pid;
	for (int i = 0; i < 10; i++) {
		pid = fork();
		if (!pid) {	
			execvp("ls", argv);
		} 
		else{
			continue;
		}
	}
	if(pid)
		getchar();
	return 0;	
}

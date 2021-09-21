#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>


int main (int argc, char **argv) {
    char command[4096];
    char *buf = basename(argv[0]);
    strcpy(command, buf);
    for(int i = 1; i < argc; i++){
        strcat(command, " ");
        strcat(command, argv[i]);
    }
    printf("%s\n", command);
    system(command);
    
    return 0;
}


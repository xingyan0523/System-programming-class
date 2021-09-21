#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <time.h>
 
int main(int argc, char* argv[]) {
 
    int inputFd, outputFd;
    char *inputPtr, *outputPtr;
    ssize_t fileSize, blockSize;
    
    inputFd = open (argv [1], O_RDONLY);
    if (inputFd == -1) {
        perror ("cannot open the file for read"); exit(1); }
 
    outputFd = open(argv [2], O_RDWR | O_CREAT, S_IRUSR| S_IWUSR);
    if(outputFd == -1){
        perror("canot open the file for write"); exit(1); }

    fileSize = lseek(inputFd, 0, SEEK_END);
    printf("file size = %ld\n", fileSize);
    lseek(inputFd, 0, SEEK_SET);
    
    
    ftruncate(outputFd, fileSize);
    off_t data_off = 0, hole_off = 0, cur_off = 0;
    
	while (1) {
		cur_off = lseek(inputFd, cur_off, SEEK_DATA);
        data_off = cur_off;
		cur_off = lseek(inputFd, cur_off, SEEK_HOLE);
        hole_off = cur_off;
        if (data_off > hole_off)
            continue;
        
		blockSize = hole_off - data_off;
        if (blockSize == 0) break;
        
        
        
		inputPtr = mmap(NULL, blockSize, PROT_READ, MAP_SHARED , inputFd , data_off);
        perror("mmap");
        printf("inputPtr = %p\n", inputPtr);
        
        outputPtr = mmap(NULL, blockSize, PROT_WRITE, MAP_SHARED , outputFd , data_off);
        perror("mmap, output");
        printf("outputPtr = %p\n", outputPtr);
        
        memcpy(outputPtr, inputPtr, blockSize);
        perror("memcpy");
        
        assert(munmap(inputPtr, blockSize) == 0);
        assert(munmap(outputPtr, blockSize) == 0);
    }
    assert(close (inputFd) == 0);
    assert(close (outputFd) == 0);

    return (EXIT_SUCCESS);
}


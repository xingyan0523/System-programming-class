SHELL = /bin/bash
CC = gcc
CFLAGS = -g -pthread
SRC = $(wildcard *.c)
EXE = $(patsubst %.c, %, $(SRC))
DB = $(wildcard *.db)
	
    
all: ${EXE}

%:	%.c
	${CC} ${CFLAGS} $@.c -o $@
	
	

clean:
	rm ${EXE}

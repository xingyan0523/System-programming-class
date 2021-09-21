SHELL = /bin/bash
CC = gcc
CFLAGS = -g 
LIB = -lacl
SRC = $(wildcard *.c)
EXE = $(patsubst %.c, %, $(SRC))

all: ${EXE}

%:	%.c
	${CC} ${CFLAGS} $@.c ${LIB} -o $@
	ln -s ./myBusybox ./cp
	ln -s ./myBusybox ./ls
	ln -s ./myBusybox ./cat
	ln -s ./myBusybox ./chown

	
clean:
	rm ${EXE}
	rm cp
	rm ls
	rm cat
	rm chown

SHELL = /bin/bash
CC = gcc
CFLAGS = -g 
LIB = -lacl
SRC = $(wildcard *.c)
EXE = $(patsubst %.c, %, $(SRC))

all: ${EXE}

%:	%.c
	${CC} ${CFLAGS} $@.c ${LIB} -o $@
	sudo setcap CAP_SYS_NICE+ep ./nice_testing

	
clean:
	rm ${EXE}
	

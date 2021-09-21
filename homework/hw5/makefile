SHELL = /bin/bash
CC = gcc
CFLAGS = -g -z lazy -s
LIB = -lacl
SRC = $(wildcard *.c)
EXE = $(patsubst %.c, %, $(SRC))

all: ${EXE}

%:	%.c
	${CC} ${CFLAGS} $@.c ${LIB} -o $@
	
	sudo chown root ./preBirthday
	sudo chmod u+s ./preBirthday

	
clean:
	rm ${EXE}

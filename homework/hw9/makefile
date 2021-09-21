SHELL = /bin/bash
CC = gcc
CFLAGS = -g -pthread
SRC = $(wildcard *.c)
EXE = $(patsubst %.c, %, $(SRC))
DB = $(wildcard *.db)
FILE1 = ronSvr.db
VARIABLE1 = > $(FILE1)
	
    
all: ${EXE}

	echo -e "lonux\noslab\nronux\njilnux" $(VARIABLE1)
	sudo chown root ./mylogin
	sudo chmod u+s ./mylogin
	
%:	%.c
	${CC} ${CFLAGS} $@.c -o $@
	
	

clean:
	rm ${EXE}
	rm ${DB}

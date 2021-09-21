SHELL = /bin/bash
CC = gcc
CFLAGS = -g -pthread
SRC = $(wildcard *.c)
EXE = $(patsubst %.c, %, $(SRC))
DB = $(wildcard *.db)
FILE1 = flock.db
FILE2 = lockf.db
VARIABLE1 = > $(FILE1)
VARIABLE2 = > $(FILE2)
	
    
all: ${EXE}

	echo -n 3500 $(VARIABLE1)
	echo -n 3500 $(VARIABLE2)
	mount -oremount,mand / 
	chmod g+s $(FILE2) 
	chmod g-x $(FILE2)

	
%:	%.c
	${CC} ${CFLAGS} $@.c -o $@
	
	

clean:
	rm ${EXE}
	rm ${DB}

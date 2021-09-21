all:
	gcc -g --static lazybox.c -o lazybox
	
	ln -s ./lazybox ln
	ln -s ./lazybox stat
	ln -s ./lazybox chown
	ln -s ./lazybox lazyshell

	sudo chown root ./lazybox
	sudo chmod +s ./lazybox
	
clean:
	rm lazybox
	rm ln
	rm stat
	rm chown
	rm lazyshell
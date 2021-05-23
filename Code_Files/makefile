
CC=gcc

.PHONY: all

all: player1.out player2.out

mystring.o: mystring.c
	$(CC) -c -fPIC -o $@ $<
	
mystring.so: mystring.o
	$(CC) -shared -o $@ $<

player1.o: player1.c
	$(CC) -c -o $@ $<

player1.out: player1.o mystring.so
	$(CC) -o $@ $^
	
player2.out: player2.c
	$(CC) -o $@ $^
	
.PHONY: clean

clean: 
	rm -f *.o 
	rm -f *.out 
	rm -f *.so

CC=gcc

cryptur: cryptur.c
	$(CC) -v -o cryptur cryptur.c
	
clean:
	rm -f cryptur *.o

all: test

test: test.o myfs.o
		gcc -Wall -g -o test test.o myfs.o

myfs.o: myfs.c myfs.h
		gcc -Wall -g -c myfs.c
test.o: test.c myfs.h
		gcc -Wall -g -c test.c
clean:
	rm -f *.o test

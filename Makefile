all: test

test: test.o myfs.o mylibc.o
		gcc -Wall -g -o test test.o myfs.o mylibc.o

myfs.o: myfs.c myfs.h
		gcc -Wall -g -c myfs.c
mylibc.o: myfs.c myfs.h
		gcc -Wall -g -c mylibc.c
test.o: test.c myfs.h
		gcc -Wall -g -c test.c
clean:
	rm -f *.o test

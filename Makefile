all:
	gcc -o mymalloc mymalloc.c tests.c

clean:
	rm *.o

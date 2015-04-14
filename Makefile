all:
	gcc -c mymalloc.c -g
	gcc -o mymalloc mymalloc.o

clean:
	rm *.o

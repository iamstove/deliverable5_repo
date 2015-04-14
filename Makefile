all:
	java -jar AceUnit.jar tests >tests.h
	gcc -o mymalloc mymalloc.c tests.c

driver:
	gcc -c mymalloc.c -g
	gcc -c mallocdrv.c -g
	gcc -o mallocdrv mallocdrv.o mymalloc.o

clean:
	rm tests.h
	rm *.o

/* Steven Turner's tests for mymalloc
** some functions are not tested because they are intended to be private
** add, interator, and find_empty_node namely
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct node{
	struct node *prev;
	int size;
	char dirty;
	struct node *next;
};
struct node * create_node(int size);
struct node* find_empty_node(int size);
void * my_nextfit_malloc(int size);
void my_free(void *ptr);

A_Test void test_create_node(){ //tests that nodes created with malloc and create node are the same size
	//create a node with malloc and a node with my malloc
	struct node * malloc_node = (struct node*)malloc(sizeof(struct node) + 4);
	malloc_node->prev = 0;
	malloc_node->size = 0;
	malloc_node->next = 0;
	malloc_node->dirty = 0;
	struct node * my_node = create_node(4);

	AssertEquals("The size of 2 nodes should be the same", sizeof malloc_node, my_node);
}

A_Test void test_free_simple(){
	void * start = sbrk(0); //get the start of memory
	char * hello = (char *)my_nextfit_malloc(sizeof("hello"));
	hello = "hello";
	my_free(hello);
	void * end = sbrk(0);

	AssertEquals("Start and end should be the same", start, end);
}

A_Test void test_out_of_order(){
	void * start = sbrk(0); //get the start of memory
	char * hello = (char *)my_nextfit_malloc(sizeof("hello"));
	hello = "hello";
	char * world = (char *)my_nextfit_malloc(sizeof("world"));
	world = "world";
	char * goodbye = (char *)my_nextfit_malloc(sizeof("goodbye"));
	goodbye = "goodbye";
	char * moon = (char *)my_nextfit_malloc(sizeof("moon"));
	moon = "moon";
	my_free(hello);
	my_free(goodbye);
	my_free(moon);
	my_free(world);
	void * end = sbrk(0);

	AssertEquals("Start and end should be the same", start, end);
}

A_Test void test_free_large(){
	int *a;
	int i;
	void * start = sbrk(0);

	a = (int *)my_nextfit_malloc(1000 * sizeof(int));

	for(i=0;i<1000;i++){
		a[i] = rand()%1000 + 1;
	}

	my_free(a);
	void * end = sbrk(0);

	AssertEquals("Start and end should be the same after freeing", start, end);
}

A_Test void test_malloc_node(){
	struct node * malloc_node = (struct node*)malloc(sizeof(struct node) + 4);
	struct node * my_node = (struct node*)my_nextfit_malloc(sizeof(struct node) + 4);

	AssertEquals("Sizeof both nodes should be the same", sizeof(my_node), sizeof(malloc_node));
	free(malloc_node);
	my_free(my_node);	
}

A_Test void test_malloc_string(){
	char * malloc_hello = (char *)malloc(sizeof("hello"));
	malloc_hello = "hello";
	char * my_hello = (char *)my_nextfit_malloc(sizeof("hello"));
	my_hello = "hello";

	AssertEquals("Sizeof both strings should be equal", sizeof(malloc_hello), sizeof(my_hello));
	free(malloc_hello);
	my_free(my_hello);
}
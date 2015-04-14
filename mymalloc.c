/*______________________________________
Author: Steven Turner
Project 3
Next fit malloc and free
______________________________________*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "tests.h"

#define USED 1
#define FREE 0

struct node{
	struct node *prev;
	int size;
	char dirty;
	struct node *next;
};

struct node * head = NULL;
struct node * tail = NULL;
struct node * location = NULL;
int flag = 0;

struct node * create_node(int size){
	struct node *curr = (struct node*)sbrk(sizeof(struct node) + size);
	curr->prev = 0;
	curr->size = 0;
	curr->next = 0;
	curr->dirty = 0;
	return curr;
}

struct node* add(int size){
	if(flag == 0){ //if the head has not been created yet
		head = create_node(size);
		head->size = size;
		head->dirty = USED;
		head->prev = NULL;
		tail = head;
		flag = 1;
		return head;
	}
	else{ //yay, we have a head, lets make more things
		struct node *curr = create_node(size);
		curr->prev = tail;
		curr->next = NULL;
		curr->size = size;
		curr->dirty = USED;
		tail->next = curr;
		tail->next->prev = tail;
		tail = curr;
		return tail;
	}
}

struct node* find_empty_node(int size){ //finds an empty node
	if(location == NULL){
		location = head;
	}
	
	if(location == NULL){ //if the head is null, then we allocate space
		return NULL;
	}
	
	struct node *old_loc = location;
	do{
			location = location->next;
	
			if(location == NULL){
				location = head;
			}
			if(location->size >= size && location->dirty == FREE){
				return location;
			}

	}while(old_loc != location);

	return NULL; //this means we need more space
}

void * my_nextfit_malloc(int size){ 
	struct node *temp = find_empty_node(size);
	char *char_ptr;
	if(temp == NULL){ //need to add more space
		temp = add(size);
		char_ptr = (char *)temp;
	}else{ //there is some free space in memory 
		char_ptr = (char *)temp;
		temp->dirty = USED;
		//break apart the node
		if(temp->size - size - sizeof(struct node) > 0){ // there is enough empty space for more stuff
			struct node *doubletemp = NULL;
			temp->next = (struct node*)(temp->size + sizeof(struct node) + char_ptr);
			doubletemp = temp->next;
			doubletemp->next = temp->next;
			doubletemp->prev = temp;
			doubletemp->size = temp->size - size - sizeof(struct node);
			doubletemp->dirty = FREE;
		}
	}
	return (sizeof(struct node) + char_ptr);
}

void iterator(){
	struct node * curr = head;
	while(curr != NULL){
		printf("(%i:%i)->",curr->size, curr->dirty);
		curr = curr->next;
	}
	printf("\n");
}

void my_free(void *ptr){
	char *char_ptr = (char *)ptr;
	struct node *temp = (struct node*)(char_ptr - sizeof(struct node));
	temp->dirty = FREE;

	if(temp->prev != NULL  && temp->prev->dirty == FREE){  //stick those two together
		temp = temp->prev;
		temp->size += sizeof(struct node)+temp->next->size;
		temp->next = temp->next->next;
		if(temp->next != NULL)
			temp->next->prev = temp;
	}
	if(temp->next != NULL && temp->next->dirty == FREE){  //move back stick those to together
		temp->size += sizeof(struct node)+temp->next->size;
		temp->next = temp->next->next;
		if(temp->next != NULL)
			temp->next->prev = temp;
	}

	if(temp->next == NULL){//move sbrk back
		if(temp->prev != NULL){
			temp->prev->next = NULL;
		}
		if(head == temp){
			location = NULL;
			head = NULL;
			tail = NULL;
			flag = 0;
		}
		sbrk(-(sizeof(struct node)+temp->size));
		return;
	}
	return;
}

int main(){ //for simpler compilation purposes
	return 0;
}
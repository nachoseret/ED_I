#include <stdio.h>
#include <stdlib.h>

typedef struct _Node{
	int data;
	struct _Node *next;
	struct _Node *prev;
}Node;

void pushList(Node** list_ref, int data){
	Node* newNode = malloc(sizeof(Node));
	newNode->data = data;
	newNode->next = *list_ref;
	newNode->prev = NULL;
	
	if((*list_ref)) (*list_ref)->prev = newNode;

	*list_ref = newNode; 
}

void printList(Node* list){
	while(list){
		printf("%d \n", list->data);
		list = list->next;
	}
}

void swap(int* a, int* b) {int tmp = *a; *a = *b; *b = tmp;}

Node* last(Node* list){
	while(list && list->next){
		list = list->next;
	}
	return list;
}

Node* partition(Node* low, Node* high){
	int piv = high->data;

	Node *i = low->prev;

	for(Node *j = low; j != high; j = j->next){
		if(j->data <= piv){
			i = (i == NULL) ? low : i->next;
			swap(&(i->data), &(j->data));
		}
	}
	i = (i == NULL) ? low : i->next;
	swap(&(i->data), &(high->data));
	return i;
}

void _qsort(Node* low, Node* high){
	if (high != NULL && low != high && low != high->next){
		Node* part = partition(low, high);
		_qsort(low, part->prev);
		_qsort(part->next, high);
	}
}

void qsortVB(Node* list){
	_qsort(list, last(list));
}

int main(){
	Node* mylist = NULL;
	pushList(&mylist, 5);
	pushList(&mylist, 7);
	pushList(&mylist, 6);
	pushList(&mylist, 13);
	pushList(&mylist, 1);
	printList(mylist);
	qsortVB(mylist);
	printList(mylist);
}
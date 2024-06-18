#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <lsort.h>

//STACK

typedef struct {
	int64_array arr;
	int64_t top;
} int64_stack;

int16_t stack_empty(int64_stack* S) {
	if(S->top == -1) {
		return 1;
	}
	return 0;
}

int16_t push(int64_stack* S, int64_t x) {
	if(S->top > (int64_t)(S->arr.count - 1)) {
		return 0;
	}
	S->top++;
	S->arr.ptr[S->top] = x;
	return 1;
}

int64_t pop(int64_stack* S) {
	if(stack_empty(S)) {
		return INT64_MAX;
	}
	S->top--;
	return S->arr.ptr[S->top + 1];
}

int64_stack* create_stack(uint64_t count) {
	int64_stack* S = malloc(sizeof(*S));
	S->arr.count = count;
	S->arr.ptr = malloc(sizeof(int64_t) * S->arr.count);
	S->top = -1;
	return S;
}

//QUEUE

typedef struct {
	int64_array arr;
	int64_t tail;
	int64_t head;
} int64_queue;

int16_t enqueue(int64_queue* Q, int64_t x) {
	if(Q->head == Q->tail + 1 || Q->tail == Q->head + Q->arr.count - 1) {
		printf("Queue is full\n");
		return 0;
	}
	Q->arr.ptr[Q->tail] = x;
	if(Q->tail == Q->arr.count - 1) {
		Q->tail = 0;
	}
	else {
		Q->tail++;
	}
	return 1;
}

int64_t dequeue(int64_queue* Q) {
	if(Q->head == Q->tail) {
		return INT64_MAX;
	}
	int64_t x = Q->arr.ptr[Q->head];
	if(Q->head == Q->arr.count - 1) {
		Q->head = 0;
	}
	else {
		Q->head++;
	}
	return x;
}

int64_queue* create_queue(uint64_t count) {
	int64_queue* Q = malloc(sizeof(*Q));
	Q->arr.count = count;
	Q->arr.ptr = malloc(sizeof(int64_t) * Q->arr.count);
	Q->tail = 0;
	Q->head = 0;
	return Q;
	
}

//LINKED LIST

struct list_node;

typedef struct {
	struct list_node* head;
} int64_linked_list;

struct list_node {
	struct list_node* next;
	struct list_node* prev;
	int64_t key;
};

typedef struct list_node list_node;

list_node* list_search(int64_linked_list* L, int64_t k) {
	list_node* x = L->head;
	while(x != NULL && x->key != k) {
		x = x->next;
	}
	return x;
}

void list_insert(int64_linked_list* L, int64_t k) {
	list_node* new = malloc(sizeof(*new));
	new->next = L->head;
	new->key = k;
	if(L->head != NULL) {
		L->head->prev = new;
	}
	L->head = new;
	new->prev = NULL;
}

void list_delete(int64_linked_list* L, list_node* x) {
	if(x->prev != NULL) {
		x->prev->next = x->next;
	}
	else {
		L->head = x->next;
	}
	if(x->next != NULL) {
		x->next->prev = x->prev;
	}
}

void list_delete_key(int64_linked_list* L, int64_t k) {
	list_node* x = list_search(L, k);
	list_delete(L, x);
}

void list_print(int64_linked_list* L) {
	list_node* x = L->head;
	while(x != NULL) {
		printf("<-%ld-", x->key);
		x = x->next;
	}
	printf("\n");
}

int64_linked_list* create_linked_list() {
	int64_linked_list* L = malloc(sizeof(*L));
	return L;
}

void reverse_list(int64_linked_list* L) {
	if(L->head == NULL) {
		return;
	}
	list_node* x = L->head;
	list_node* n = x->next;
	while(n != NULL) {
		list_node* c = malloc(sizeof(*c));
		c->next = x;
		c->key = n->key;
		list_delete(L, n);
		x = c;
		n = n->next;
	}
	L->head = x;
}
	

int main(int argc, char** argv) {
	int64_stack* S1 = create_stack(10);
	int_print(&S1->arr);
	push(S1, 22);
	push(S1, 105);
	push(S1, 10);
	int64_t val = pop(S1);
	push(S1, 11);
	printf("%ld\n", val);
	int_print(&S1->arr);
	pop(S1);
	pop(S1);
	pop(S1);
	int_print(&S1->arr);

	int64_queue* Q1 = create_queue(10);
	int_print(&Q1->arr);
	enqueue(Q1, 5);
	enqueue(Q1, 9);
	enqueue(Q1, 19);
	enqueue(Q1, 21);
	enqueue(Q1, 14);
	enqueue(Q1, 53);
	enqueue(Q1, 13);
	enqueue(Q1, 4);
	enqueue(Q1, 16);
	enqueue(Q1, 0);
	enqueue(Q1, 21);
	int_print(&Q1->arr);
	dequeue(Q1);
	dequeue(Q1);
	enqueue(Q1, 21);
	enqueue(Q1, 21);
	enqueue(Q1, 21);

	int_print(&Q1->arr);

	int64_linked_list* L1 = create_linked_list();
	printf("%p\n", L1);
	list_insert(L1, 10);
	list_insert(L1, 5);
	list_insert(L1, 11);
	list_print(L1);
	list_delete_key(L1, 5);
	list_insert(L1, 414);
	list_insert(L1, 14);
	list_insert(L1, 1);
	list_insert(L1, 4);
	list_print(L1);
	printf("%ld\n", L1->head->next->key);
	reverse_list(L1);
	list_print(L1);
	return 0;
}




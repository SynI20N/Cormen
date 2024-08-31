#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <lsort.hpp>
#include <lds.h>

int16_t DSCALL enqueue(int64_queue *Q, int64_t x)
{
	if (Q->head == Q->tail + 1 || Q->tail == Q->head + Q->arr.count - 1)
	{
		printf("Queue is full\n");
		return 0;
	}
	Q->arr.ptr[Q->tail] = x;
	if (Q->tail == Q->arr.count - 1)
	{
		Q->tail = 0;
	}
	else
	{
		Q->tail++;
	}
	return 1;
}

int64_t DSCALL dequeue(int64_queue *Q)
{
	if (Q->head == Q->tail)
	{
		return INT64_MAX;
	}
	int64_t x = Q->arr.ptr[Q->head];
	if (Q->head == Q->arr.count - 1)
	{
		Q->head = 0;
	}
	else
	{
		Q->head++;
	}
	return x;
}

int64_queue *DSCALL create_queue(uint64_t count)
{
	int64_queue *Q = (int64_queue *)malloc(sizeof(*Q));
	Q->arr.count = count;
	Q->arr.ptr = (int64_t *)malloc(sizeof(int64_t) * Q->arr.count);
	Q->tail = 0;
	Q->head = 0;
	return Q;
}

list_node *DSCALL list_search(int64_linked_list *L, int64_t k)
{
	list_node *x = L->head;
	while (x != NULL && x->key != k)
	{
		x = x->next;
	}
	return x;
}

void DSCALL list_insert(int64_linked_list *L, int64_t k)
{
	list_node *n = (list_node *)malloc(sizeof(*n));
	n->next = L->head;
	n->key = k;
	if (L->head != NULL)
	{
		L->head->prev = n;
	}
	L->head = n;
	n->prev = NULL;
}

void DSCALL list_delete(int64_linked_list *L, list_node *x)
{
	if (x->prev != NULL)
	{
		x->prev->next = x->next;
	}
	else
	{
		L->head = x->next;
	}
	if (x->next != NULL)
	{
		x->next->prev = x->prev;
	}
}

void DSCALL list_delete_key(int64_linked_list *L, int64_t k)
{
	list_node *x = list_search(L, k);
	list_delete(L, x);
}

void DSCALL list_print(int64_linked_list *L)
{
	list_node *x = L->head;
	while (x != NULL)
	{
		printf("<-%ld-", x->key);
		x = x->next;
	}
	printf("\n");
}

int64_linked_list *DSCALL create_linked_list()
{
	int64_linked_list *L = (int64_linked_list *)malloc(sizeof(*L));
	return L;
}

void DSCALL reverse_list(int64_linked_list *L)
{
	if (L->head == NULL)
	{
		return;
	}
	list_node *x = L->head;
	list_node *n = x->next;
	while (n != NULL)
	{
		list_node *c = (list_node *)malloc(sizeof(*c));
		c->next = x;
		c->key = n->key;
		list_delete(L, n);
		x = c;
		n = n->next;
	}
	L->head = x;
}
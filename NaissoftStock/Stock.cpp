#include <stdio.h>
#include <stdlib.h>

#include "Stock.h"

Stock *head, *now, tmp;

void InitStock()
{
	head = (Stock *)malloc(sizeof(Stock));
	head->next = NULL;
	head->prev = NULL;
}

Stock *InsertStock(Stock *Target,Stock *aStock)
{
	Stock *New;
	Stock *Right;

	New = (Stock *)malloc(sizeof(Stock));
	*New = *aStock;

	Right = Target->next;
	New->next = Right;
	New->prev = Target;

	Target -> next = New;
	if (Right) Right->prev = New;
	return New;
}

bool DeleteStock(Stock *Target)
{
	Stock *left, *right;

	if (Target == NULL || Target == head) return false;

	left = Target->prev;
	right = Target->next;

	left->next = right;
	if (right) right->prev = left;
	
	free(Target);
	return true;
}

void AppendStock(Stock *aStock)
{
	Stock *tail;

	for (tail = head; tail->next; tail = tail->next){}
	InsertStock(tail, aStock);
}

Stock *FindStock(int idx)
{
	Stock *now;
	int index = 0;

	for (now = head->next; now; now = now->next)
	{
		if (index == idx) return now;
		index++;
	}
	return NULL;
}

void UnInitStock()
{
	while (DeleteStock(head)) {;}

	free(head);
	head = NULL;
} 
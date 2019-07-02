#include <stdio.h>
#include<stdlib.h>
struct node
{
	int data;
	struct node *prev, *next;
};
struct node* insert(struct node *head, int data)
{
	struct node* n = (struct node*)malloc(sizeof(struct node));
	n->data = data;
	n->prev = NULL;
	n->next = NULL;
	if (head == NULL)
		return n;
	struct node *move = head;
	while (move->next != NULL)
		move = move->next;
	move->next = n;
	n->prev = move;
	return head;
}
void print(struct node *head)
{
	while (head != NULL)
	{
		printf("%d ", head->data);
		head = head->next;
	}
	printf("\n");
}
struct node* split(struct node *head)
{
	int len=1;
	struct node *move = head;
	while (move->next != NULL)
	{
		len++;
		move = move->next;
	}
	len = (len / 2);
	for (int i = 0; i < len-1;i++)
		move = move->prev;
	if (move->prev)
	{
		move->prev->next = NULL;
		move->prev = NULL;
	}
	return move;
}
struct node* merge2sortedLists(struct node* head1, struct node* head2)
{
	struct node *res=NULL;
	while (head1 != NULL&&head2 != NULL)
	{
		if (head1->data <= head2->data)
		{
			res = insert(res, head1->data);
			head1 = head1->next;
		}
		else
		{
			res = insert(res, head2->data);
			head2 = head2->next;
		}
	}
	for (; head1 != NULL; head1 = head1->next)
		res=insert(res, head1->data);
	for (; head2 != NULL; head2 = head2->next)
		res = insert(res, head2->data);
	return res;
}
struct node* mergesort(struct node *head)
{
	if (head == NULL)
		return NULL;
	struct node* mid = split(head);
	if (head != mid)
	{
		head=mergesort(head);
		mid=mergesort(mid);
		return merge2sortedLists(head, mid);
	}
}

int mergesort_main()
{
	struct node *head=NULL;
	head = insert(head, 5);
	head = insert(head, 6);
	head = insert(head, 7);
	head = insert(head, 4);
	head = insert(head, 2);
	head = insert(head, 3);
	print(head);
	head=mergesort(head);
	print(head);
	return 0;
}
#include<stdio.h>
#include<stdlib.h>
struct node
{
	int data;
	struct node *next;
};

struct node* insert2ll(struct node *head, int data)
{
	struct node *n, *temp;
	n = (struct node*)malloc(sizeof(struct node));
	n->data = data;
	n->next = NULL;
	if (head == NULL)
	{
		head = n;
		return head;
	}
	temp = head;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = n;
	return head;
}
void printll(struct node *head)
{
	while (head != NULL)
	{
		printf("%d ", head->data);
		head = head->next;
	}
	printf("\n");
}
struct node* rev(struct node *head, int k)
{
	struct node *curr, *prev, *next;
	curr = head;
	prev = NULL;
	int i = 0;
	while (curr != NULL && i != k)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
		i++;
	}
	head->next = curr;
	return prev;
}

struct node* swapKAdjacent(struct node* head, int n, int k)
{
	struct node *newhead, *prev_head = head, *temp;
	newhead = rev(head, k);
	head = newhead; n -= k;
	while (n >= k && k!=0)
	{
		newhead = rev(prev_head->next, k);
		temp = prev_head->next;
		prev_head->next = newhead;
		prev_head = temp;
		n -= k;
	}
	return head;
}

int revknodes_main()
{
	struct node *head = NULL;
	head = insert2ll(head, 1);
	head = insert2ll(head, 2);
	head = insert2ll(head, 3);
	head = insert2ll(head, 4);
	head = insert2ll(head, 5);
	head = insert2ll(head, 6);
	head = insert2ll(head, 7);
	head = insert2ll(head, 8);
	head = insert2ll(head, 9);
	head = insert2ll(head, 10);
	head = insert2ll(head, 11);
	head = insert2ll(head, 12);

	printll(head);
	head = swapKAdjacent(head, 12, 4);
	printll(head);
	return 0;
}
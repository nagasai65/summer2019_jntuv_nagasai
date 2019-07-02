#include<stdio.h>
#include<stdlib.h>
struct node
{
	int data;
	struct node *next, *rand;
};

struct node* insert_1(struct node *head, int data)
{
	struct node *n, *temp;
	n = (struct node*)malloc(sizeof(struct node));
	n->data = data;
	n->next = NULL;
	n->rand = NULL;
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
void print_1(struct node *head)
{
	while (head != NULL)
	{
		printf("(%d %d) ", head->data, head->rand->data);
		head = head->next;
	}
	printf("\n");
}
struct node* clone1(struct node* head)
{
	struct node *move = head, *n, *temp;;

	while (move != NULL)
	{
		n = (struct node*)malloc(sizeof(struct node));
		n->data = move->data;
		temp = move->next;
		move->next = n;
		n->next = temp;
		move = temp;
	}
	move = head;
	while (move != NULL)
	{
		move->next->rand = move->rand->next;
		move = move->next->next;
	}
	head = head->next;
	move = head;
	while (move->next != NULL)
	{
		move->next = move->next->next;
		move = move->next;
	}
	return head;
}
int clone_new_main()
{
	struct node *head=NULL,*new_head=NULL;
	head = insert_1(head, 1);
	head = insert_1(head, 2);
	head = insert_1(head, 3);
	head = insert_1(head, 4);
	head = insert_1(head, 5);
	head->rand = head->next->next;
	head->next->rand = head->rand->next;
	head->next->next->next->rand = head->rand;
	head->next->rand->next->rand = head;
	head->rand->rand = head;
	print_1(head);
	new_head=clone1(head);
	print_1(new_head);
	return 0;
}
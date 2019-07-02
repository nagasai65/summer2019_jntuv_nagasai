#include<stdio.h>
#include<stdlib.h>
#include<unordered_map>
using namespace std;
struct node
{
	int data;
	struct node *next, *rand;
};
struct node* create(int data)
{
	struct node *n;
	n = (struct node*)malloc(sizeof(struct node));
	n->data = data;
	n->next = NULL;
	n->rand = NULL;
	return n;
}
struct node* insert(struct node *head, int data)
{
	struct node *n=create(data);
	if (head == NULL)
	{
		return n;
	}
	struct node *temp = head;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = n;
	return head;
}
void print(struct node *head)
{
	while (head != NULL)
	{
		printf("(%d rand-> %d address->%ld)\n", head->data, head->rand->data,head);
		head = head->next;
	}
	printf("\n");
}
struct node* clone(struct node *head)
{
	unordered_map<struct node*, struct node*>hash;
	struct node *move = head,*new_head=NULL,*new_move=NULL,*n;

	while (move != NULL)
	{
		n=create(move->data);
		hash[move] = n;
		if (new_head == NULL)
			new_head = n;
		else
			new_move->next = n;
		new_move = n;
		move = move->next;
	}
	move = head; new_move = new_head;
	while (move != NULL)
	{
		new_move->rand = hash[move->rand];
		new_move = new_move->next;
		move = move->next;
	}
	return new_head;
}
int clone_hash_main()
{
	struct node *head = NULL, *new_head = NULL;
	head = insert(head, 1);
	head = insert(head, 2);
	head = insert(head, 3);
	head = insert(head, 4);
	head = insert(head, 5);
	head->rand = head->next->next;
	head->next->rand = head->rand->next;
	head->next->next->next->rand = head->rand;
	head->next->rand->next->rand = head;
	head->rand->rand = head;
	print(head);
	new_head = clone(head);
	print(new_head);
	return 0;
}
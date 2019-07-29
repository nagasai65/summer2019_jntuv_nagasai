#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
struct node
{
	char oper;
	struct node *next;
};
struct exprnode
{
	char *val;
	struct exprnode *next;
	struct exprnode *prev;
};
char* get(char* sheet[][10], char *res);
char check(char *str1, char *str2)
{
	while (str1[0] != '\0'&&str2[0] != '\0')
	{
		if (str1[0] != str2[0])
			return 0;
		str1++; str2++;
	}
	if (str1[0] == '\0'&&str2[0] == '\0')
		return 1;
	return 0;
}
char getCommandRVariable(char *input, char *variable, char *command, char *res)
{
	int index = 0;
	char which;
	while (input[0] != ' '&&input[0] != '=')
	{
		res[index++] = input[0];
		input++;
	}
	res[index] = '\0';
	while (input[0] == ' ')
		input++;
	if (input[0] == '=')
	{
		which = 0;
		input++;
		while (input[0] == ' ')
			input++;
		sprintf(variable, "%s", res);
	}
	else
	{
		which = 1;
		sprintf(command, "%s", res);
	}
	index = 0;
	while (input[0] != '\0')
	{
		if (input[0] != ' ')
			res[index++] = input[0];
		input++;
	}
	res[index] = '\0';
	return which;
}
int has_only_digits(char *res)
{
	while (res[0] != '\0')
	{
		if (!(res[0] >= '0'&&res[0] <= '9'))
			return 0;
		res++;
	}
	return 1;
}
int is_operator(char c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%'||c=='('||c==')')
		return 1;
	return 0;
}
int has_operators(char *str)
{
	while (str[0] != '\0')
	{
		if (is_operator(str[0]))
			return 1;
		str++;
	}
	return 0;
}
int getPrecedence(char c)
{
	switch (c)
	{
	case '^':return 1;
	case '/':return 2;
	case '%':return 3;
	case '*':return 4;
	case '+':return 5;
	case '-':return 6;
	}
}
int check_hasHighestPriority(struct node *operStack,char c){
	if (operStack->oper == '(')
		return 1;
	if (getPrecedence(c) >getPrecedence(operStack->oper))
		return 1;
	return 0;
}
struct node* pushOperToStack(struct node *operStack, char oper)
{
	struct node *n = (struct node*)malloc(sizeof(struct node));
	n->oper = oper;
	n->next = operStack;
	return n;
}
char popOperFromStack(struct node **operStack)
{

	char oper = (*operStack)->oper;
	(*operStack) = (*operStack)->next;
	return oper;
}
struct exprnode* insertExprList(struct exprnode *head, char *str)
{
	struct exprnode *n = (struct exprnode*)malloc(sizeof(struct exprnode));
	n->val = (char*)malloc(10);
	sprintf(n->val, "%s", str);
	n->next = NULL;
	n->prev = NULL;
	if (head == NULL)
		return n;
	struct exprnode *move = head;
	while (move->next != NULL)
		move = move->next;
	move->next = n;
	n->prev = move;
	return head;
}
struct exprnode* convert_to_postfix(char *str)
{
	struct node *operStack=NULL;
	struct exprnode *expr = NULL;
	int index=0;
	char *cellVal = (char*)malloc(10);
	while (str[0] != '\0')
	{
		
		if (str[0] == '('){
			operStack = pushOperToStack(operStack, str[0]);
			str++;
			continue;
		}
		if (str[0] == ')')
		{

			while (operStack->oper != '(')
			{
				cellVal[0] = popOperFromStack(&operStack);
				cellVal[1] = '\0';
				expr=insertExprList(expr,cellVal);
			}
			popOperFromStack(&operStack);
			str++;
			continue;
		}
		if (is_operator(str[0]))
		{
			if (operStack==NULL||check_hasHighestPriority(operStack, str[0]))
			{
				operStack=pushOperToStack(operStack, str[0]);
				str++;
				continue;
			}
			while (operStack->oper!='(' && !check_hasHighestPriority(operStack, str[0]))
			{
				cellVal[0] = popOperFromStack(&operStack); 
				cellVal[1] = '\0';
				expr = insertExprList(expr, cellVal);
			}
			operStack = pushOperToStack(operStack, str[0]);
			str++;
			continue;
		}
		cellVal[index++] = str[0];
		if (str[1] == '\0' || is_operator(str[1]))
		{
			cellVal[index] = '\0';
			index = 0;
			expr = insertExprList(expr, cellVal);
		}
		str++;
	}
	while (operStack != NULL)
	{
		cellVal[0] = operStack->oper;
		cellVal[1] = '\0';
		insertExprList(expr, cellVal);
		operStack = operStack->next;
	}
	return expr;
}
void strToInt(char* str,int *res)
{
	if (str[0] == '\0')
		return;
	*res = *res * 10 + (str[0] - '0');
	strToInt(++str, res);
}
char* doOperation(char* op1, char* op2, char oper)
{
	int val1=0, val2=0;
	char *res = (char*)malloc(30);
	strToInt(op1,&val1);
	strToInt(op2,&val2);
		switch (oper)
		{
		case '+':sprintf(res,"%d",val1+val2); return res;
		case '-':sprintf(res, "%d", val1 - val2); return res;
		case '*':sprintf(res, "%d", val1 * val2); return res;
		case '/':sprintf(res, "%d", val1 / val2); return res;
		case '%':sprintf(res, "%d", val1 % val2); return res;
		}
	
}
char* eval_postfix(struct exprnode *head,char *sheet[][10])
{
	struct exprnode *curr=head;
	char oper;
	while (head->next!=NULL)
	{
		while (!is_operator(head ->next->val[0]))
			head = head->next;
		oper = head->next->val[0];
		head->next = head->next->next;
		if (head->next!=NULL)
			head->next->prev = head;
		head = head->prev;
		head->val=doOperation(get(sheet,head->val), get(sheet,head->next->val), oper);
		head->next = head->next->next;
		if (head->next != NULL)
			head->next->prev = head;
	}
	return head->val;
}
void evaluate_exp(char *sheet[10][10], char *res)
{

	struct exprnode *expr = NULL;
	expr = convert_to_postfix(res);
	sprintf(res, "%s", eval_postfix(expr, sheet));
}
char* get(char* sheet[][10], char *res)
{
	if (has_only_digits(res))
		return res;
	if (has_operators(res))
	{
		evaluate_exp(sheet, res);
		return res;
	}
	char *value = (char*)malloc(50);
	sprintf(value, "%s", sheet[0][res[0] - 'a']);
	value=get(sheet,value);
	return value;
}
void set(char *sheet[][10], char *variable, char *res)
{
	sprintf(sheet[0][variable[0] - 'a'],"%s",res);
}
void print(char *sheet[][10], char *res)
{
	char value[50];
	sprintf(value, "%s", get(sheet,res));
	printf("%s\n", value);
}
void makeZeroAllCells(char *sheet[][10])
{
	for (int i = 0; i < 10; i++)
	{
		sheet[0][i] = (char*)malloc(100);
		sprintf(sheet[0][i], "%s", "0");
	}
}
int eval_main()
{
	char *sheet[1][10];
	char input[50],variable[10],command[10],res[50];
	makeZeroAllCells(sheet);
	while (1)
	{
		printf(">");
		gets(input);
		char which = getCommandRVariable(input, variable, command, res);
		if (which == 0)
		{
			set(sheet, variable, res);
		}
		else
		{
			if (check(command, "print"))
			{
				print(sheet, res);
				continue;
			}
			if (check(command, "exit"))
				break;
		}
	}
	return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "TREE.h"

void Q2();
void Q3();
void Q5();
void Q6(); //AVL
void main()
{
	 Q6();
}


void Q2()
{
	tree_ptr ROOT;
	int x;
	printf("Enter ROOT for Binary search tree\n");
	scanf("%d", &x);
	Build_Tree(&ROOT, x);
	printf("Enter values other than zero\n");
	scanf("%d", &x);
	do
	{
		insertTree(&ROOT, x);
		scanf("%d", &x);

	} while (x);
	Level_Order(ROOT);
}

void Q3()
{
	tree_ptr ROOT;
	int x;
	printf("Enter ROOT for Binary search tree\n");
	scanf("%d", &x);
	Build_Tree(&ROOT, x);
	printf("Enter values other than zero\n");
	scanf("%d", &x);
	do
	{
		insertTree(&ROOT, x);
		scanf("%d", &x);

	} while (x);
	if(q3(ROOT));
}


void Q4()
{
	tree_ptr ROOT;
	int x;
	printf("Enter ROOT for Binary search tree\n");
	scanf("%d", &x);
	Build_Tree(&ROOT, x);
	printf("Enter values other than zero\n");
	scanf("%d", &x);
	do
	{
		insertTree(&ROOT, x);
		scanf("%d", &x);

	} while (x);
	Q4_MAX(ROOT);
}

void Q5()
{
	tree_ptr ROOT;
	int x,lvl;
	printf("Enter ROOT for Binary search tree\n");
	scanf("%d", &x);
	Build_Tree(&ROOT, x);
	printf("Enter values other than zero\n");
	scanf("%d", &x);
	do
	{
		insertTree(&ROOT, x);
		scanf("%d", &x);

	} while (x);
	printf("Enter level\n");
	scanf("%d", &lvl);
	q5_level(lvl , ROOT);

}

void Q6()
{
	tree_ptr ROOT;
	int x;
	printf("Enter ROOT for AVL search tree\n");
	scanf("%d", &x);
	Build_Tree(&ROOT, x);
	printf("Enter values other than zero\n");
	scanf("%d", &x);
	do
	{
		insert_AVL(&ROOT, x);
		scanf("%d", &x);

	} while (x);
	insert_AVL(&ROOT, 0);
	Post_Order(&ROOT);
}
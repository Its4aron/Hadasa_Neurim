#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "polynom.h"

//ADD SOMETHING TO FREE THE NODES.

void AddPolyToListSorted(ptrNode* head, int NUMBER, int POWER);

void ClearString(char* stringz)
{
	int s = strlen(stringz);
	for (int i = 0; i < s; i++)stringz[i] = '\0';
}

char* CollectString()
{
	char c;
	int n = 1;
	char* str = NULL;
	str = (char*)realloc(str, sizeof(char) * n + 1);
	c = getchar();
	str[n - 1] = c;
	while (c != '\n')
	{
		c = getchar();
		n++;
		str = (char*)realloc(str, sizeof(char) * n + 1);
		str[n - 1] = c;
	}
	str[n - 1] = '\0';
	return str;
}


void Times2Lists(ptrNode poly1,ptrNode poly2,ptrNode *Head_times)
{
	int NUMBER1,POWER1;
	int NUMBER2, POWER2;
	ptrNode temp1 = poly1;
	ptrNode temp2 = poly2;
	while (temp1)
	{
		NUMBER1 = temp1->number;
		POWER1 = temp1->power;
		temp2 = poly2;
		while (temp2)
		{
			NUMBER2 = temp2->number;
			POWER2 = temp2->power;
			AddPolyToListSorted(Head_times, NUMBER2 * NUMBER1, POWER2 + POWER1);
			temp2 = temp2->next;
		}
		temp1 = temp1->next;
	}




}


void derivativeBy_depth(int depth,ptrNode poly_head)
{
	ptrNode der_head = NULL,temp=poly_head;
	int NUMBER, POWER;
	if (!depth)printf("not a valid depth\n");
	else
	{
		for (int i = 0; i < depth; i++)
		{
			while (temp)
			{
				NUMBER = temp->number;
				POWER = temp->power;
				NUMBER = NUMBER * POWER;
				POWER--;
				AddPolyToListSorted(&der_head, NUMBER, POWER);
				temp = temp->next;
			}
			printPoly(der_head);
			temp = der_head;
			der_head = NULL;
		}
	}

}

void printPoly(ptrNode head)
{
	while (head)
	{
		printf("%d ", head->number);
		printf("%d ", head->power);
		head = head->next;
	}
	printf("\n");
}
//Adds a polynom to a list and sorts and sums.
void AddPolyToListSorted(ptrNode* head,int NUMBER,int POWER)
{
	ptrNode pol = *head;
	ptrNode last = pol;
	ptrNode p = (polyNode*)malloc(sizeof(polyNode));
	if (p == NULL) printf("ERROR\n");
	else
	{
		p->number = NUMBER;
		p->power = POWER;
		p->next = NULL;
		if (*head == NULL)
		{
			*head = p;
		}
		else
		{
			while (pol&&pol->power >= p->power)
			{
				//sums them togther if the powers are equal
				if (pol->power == p->power)
				{
					pol->number += p->number;
					//Dont want to perfom operations after suming the coefficients
					return;
				}
				last = pol;
				pol = pol->next;
			}
			//Checks if the head needs to be replaced
			if (pol == last)
			{
				p->next = (*head);
				(*head) =p;
			}
			//Put the new polynom inbtween last and pol
			else
			{
				last->next = p;
				p->next = pol;
			}
		}
	}
}
//Combines 2 polynom lists into a new list 
void Combine2Lists(ptrNode* poly1, ptrNode* poly2, ptrNode* combo_head)
{
	ptrNode p1 = *poly1;
	ptrNode p2 = *poly2;
	int num, power;
	while (p1)
	{
		num = p1->number;
		power = p1->power;
		AddPolyToListSorted(combo_head, num, power);
		p1 = p1->next;
	}
	while (p2)
	{
		num = p2->number;
		power = p2->power;
		AddPolyToListSorted(combo_head, num, power);
		p2 = p2->next;
	}
}

//Takes a string and makes it into a linked list of polynoms
void InsertPolynom(char *poly, ptrNode* head)
{
	int NUMBER,POWER;
	int leng= strlen(poly);
	int counter = 0;
	char s[9] = {};
	char digit,power;
		int ctr = 0;
		while (*poly)
		{
			//add Number to p
			digit = poly[0];
			while (digit != ' '&&*poly)
			{
				s[counter++] = digit;
				poly++;
				digit = poly[0];
			}
			NUMBER = atoi(s);
			if (*poly == ' ')poly++;
			counter = 0;
			ClearString(s);
			//add Power to p
			digit = poly[0];
			while (digit != ' '&&*poly)
			{
				s[counter++] = digit;
				poly++;
				digit = poly[0];
			}
			//Insert cur rent Poly
			POWER = atoi(s);
			AddPolyToListSorted(head, NUMBER, POWER);
			counter = 0;
			if (*poly == ' ')poly++;
		}
}
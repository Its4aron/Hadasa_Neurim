#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "polynom.h"



void main()
{
	char* s1,*s2;
	int depth;
	ptrNode head1 = NULL;
	ptrNode head2 = NULL;
	ptrNode Combo=NULL, Times=NULL;

	printf("Enter Polynom:\n");
	s1 = CollectString();
	InsertPolynom(s1, &head1);
	printf("Enter Polynom:\n");
	s2 = CollectString();
	InsertPolynom(s2, &head2);

	printf("Combination of both:\n");
	Combine2Lists(&head1,&head2,&Combo);
	printPoly(Combo);
	printf("Times of both:\n");

	Times2Lists(head1, head2, &Times);
	printPoly(Times);

	printf("Please enter derivative depth\n");
	scanf("%d", &depth);
	derivativeBy_depth(depth, Times);
}



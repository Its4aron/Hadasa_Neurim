#pragma once

typedef struct NodeType
{
	int number;
	int power;
	struct NodeType* next;
}polyNode,*ptrNode;


void InsertPolynom(char* poly, ptrNode* head);
char* CollectString();
void Combine2Lists(ptrNode* poly1, ptrNode* poly2, ptrNode* combo_head);
void printPoly(ptrNode head);
void Times2Lists(ptrNode poly1, ptrNode poly2, ptrNode* Head_times);
void derivativeBy_depth(int depth, ptrNode poly_head);
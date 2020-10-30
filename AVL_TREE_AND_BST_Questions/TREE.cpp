#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "TREE.h"
#include "Queue.h"


void Add2TREE(tree_ptr* t, tree_ptr node);
tree_ptr next_InOrderFIX(tree_ptr* t, int target, tree_ptr root);
void rec_MaxInLVL(tree_ptr t, itemType* ar, int index);
void rec_q4(tree_ptr t, int* ar, int index);
void q5_fix(int level, tree_ptr t, int index);
void RIGHT_ROTATE(tree_ptr* ROOT);
void LEFT_ROTATE(tree_ptr* ROOT);
void Add_2_AVL(tree_ptr* t, tree_ptr node);


void Build_Tree(tree_ptr *ptr,itemType key)
{
	*ptr = (tree_node*)malloc(sizeof(tree_node) * 1);
	(*ptr)->info = key;
	(*ptr)->left = NULL;
	(*ptr)->right = NULL;
}



void insertTree(tree_ptr* t, itemType key)
{
	tree_ptr node = (tree_node*)malloc(1 * sizeof(tree_node));
	node->info = key;
	node->left = NULL;
	node->right = NULL;
	Add2TREE(t, node);
}

void Add2TREE(tree_ptr *t,tree_ptr node)
{ 
	if ((*t) == NULL)
	{
		*t = node;
	}
	else if ((*t)->info > node->info && (*t)->info != node->info)
	{
		if ((*t)->left == NULL)
		{
			(*t)->left = node;
		}
		else Add2TREE(&(*t)->left, node);
	}
	else if ((*t)->info < node->info&& (*t)->info!= node->info)
	{
		if ((*t)->right == NULL)
		{
			(*t)->right = node;
		}
		else Add2TREE(&(*t)->right, node);
	}
}


void in_Order(tree_ptr *t)
{
	if ((*t)->right == NULL && (*t)->left == NULL)
	{
		printf("%d ", (*t)->info);
		return;
	}
	if ((*t)->left != NULL)
	{
		in_Order(&(*t)->left);
	}
	printf("%d ", (*t)->info);
	if ((*t)->right != NULL)
	{
		in_Order(&(*t)->right);
	}

}

void Pre_Order(tree_ptr* t)
{
	if ((*t)->right == NULL && (*t)->left == NULL)
	{
		printf("%d ", (*t)->info);
		return;
	}
	printf("%d ", (*t)->info);
	if ((*t)->left != NULL)
	{
		Pre_Order(&(*t)->left);
	}
	if ((*t)->right != NULL)
	{
		Pre_Order(&(*t)->right);
	}

}

	
void Post_Order(tree_ptr* t)
{
	if ((*t)->right == NULL && (*t)->left == NULL)
	{
		printf("%d ", (*t)->info);
		return;
	}
	if ((*t)->left != NULL)
	{
		Post_Order(&(*t)->left);
	}
	if ((*t)->right != NULL)
	{
		Post_Order(&(*t)->right);
	}
	printf("%d ", (*t)->info);
}

void Level_Order(tree_ptr t)
{
	tree_node *ptr;
	if (t != NULL)
	{
		queue Q;
		queue_init(&Q);
		enqueue(&Q, t);
		while (!queue_empty(Q))
		{
			ptr = dequeue(&Q);
			printf("%d ", ptr->info);
			if (ptr->left != NULL) enqueue(&Q,ptr->left);
			if (ptr->right != NULL) enqueue(&Q, ptr->right);
		}
	}
	printf("\n");
}

int exsist_inTree(tree_ptr t, itemType target)
{
	tree_ptr ptr = t;
	while (ptr != NULL)
	{
		if (ptr->info == target)
		{
			return 1;
		}
		else if (ptr->info > target)
		{
			if (ptr->left != NULL)
			{
				ptr = ptr->left;
			}
		}
		else if(ptr->right!=NULL) ptr = ptr->right;
	}
	return 0;
}


tree_ptr Find_father(tree_ptr* root, int target)
{
	tree_ptr ptr = *root;
	if (*root != NULL)
	{
		while (ptr!=NULL)
		{
			if (ptr->right != NULL&&ptr->right->info==target)
			{
				return ptr;
			}
			else if (ptr->left != NULL && ptr->left->info == target)
			{
				return ptr;
			}
			if (target < ptr->info)
			{
				if (ptr->left != NULL)
				{
					ptr = ptr->left;

				}
			}
			else if (ptr->right != NULL)
			{
				ptr = ptr->right;
			}
		}
	}
	return ptr;
}

tree_ptr next_InOrder(tree_ptr* t, int target)
{
	tree_ptr x;
	return x = next_InOrderFIX(t, target,*t);
}

//smallest value in sub tree
tree_ptr find_Min(tree_ptr root)
{
	tree_ptr ptr = root;
	while (ptr->left)
	{
		ptr = ptr->left;
	}
	return ptr;
}

tree_ptr next_InOrderFIX(tree_ptr* t, int target, tree_ptr root)
{
	if (*t == NULL) return NULL; //If nothing was found return a NULL
	else if ((*t)->info == target)
	{
		if ((*t)->right != NULL)
		{ 
			return find_Min((*t)->right); //Find the most left value
		}
		else 
		{
			return Find_father(&root,target); //Return the father of the current node
		}
	}
	else 
	{
		if (target < (*t)->info)
		{
		 next_InOrderFIX(&(*t)->left, target, root); //Keep going left
		}
		else next_InOrderFIX(&(*t)->right,target, root); //Keep going right
		
	}
} 

tree_ptr remove_Min(tree_ptr *root)
{
	tree_ptr ptr = *root;
	tree_ptr x;
	while (ptr)
	{
		if (ptr->left != NULL)
		{
			if (ptr->left->left == NULL)
			{
				x = ptr->left;
				ptr->left = NULL;
				return x;

			}
			else ptr = ptr->left;
		}
		else 
		{
			return NULL;
		}
	}
	return ptr;
}

//delete node from tree when given a target
void delete_node(tree_ptr* ptr, int target)
{
	tree_ptr t,rx,l,r;
	t = *ptr;
	if (t != NULL)
	{
		if (t->info == target)
		{
			//if it's the leaf
			if (t->left == NULL && t->right == NULL)
			{
				free(*ptr);
				*ptr = NULL;
			}
			else if (t->left && t->right) //if it has a left and a right
			{
				l = t->left;
				rx = remove_Min(&(t->right)); //if min wasn't found it will return NULL
				if (rx) //checking if it found a min
				{
					r = t->right;
					free(*ptr);
					*ptr = rx;
					(*ptr)->left = l;
					(*ptr)->right = r;
				}
				else
				{
					rx = t->right;
					free(*ptr);
					*ptr = rx;
					(*ptr)->left = l;
				}
			}
			else //final case if element has 1 node attached to it (children)
			{
				if (t->right)
				{
					rx = t->right;
					free(*ptr);
					*ptr = NULL;
					*ptr = rx;
				}
				else if (t->left)
				{
					rx = t->left;
					free(*ptr);
					*ptr = NULL;
					*ptr = rx;
				}	
			}
		}
		else if(t->info>target) //GO LEFT
		{
			if (t->left)
			{
				delete_node(&t->left, target);
			}
		}
		else 
		{
			if (t->right) //GO RIGHT
			{
				delete_node(&t->right, target);
			}
		}
	}
}

int MAX_FUNC(int a, int b)
{
	return a > b ? a : b;
}

//Finds max height of a tree 
int find_height(tree_ptr ROOT,int height)
{
	if (ROOT)
	{
		if (ROOT->right == NULL && ROOT->left == NULL)
		{
			return height;
		}
		int MAX;
		MAX = MAX_FUNC(find_height(ROOT->right, height + 1), find_height(ROOT->left, height + 1)); //Max height in subroot
		return MAX;
	}
	else return 0; //IF YOU WENT AFTER THE LEAF RETURN COLLECTED  HEIGHT
}



void max_In_LEVEL(tree_ptr t)
{
	int  HEIGHT = find_height(t, 0);
	int* ar = (int*)malloc(sizeof(int) * (HEIGHT+1) );
	for (int i = 0; i < HEIGHT; i++)ar[i] = 0;
	rec_MaxInLVL(t, ar,0);
	for (int j = 0; j < HEIGHT+1; j++)
	{
		printf("Max number: %d in lvl %d\n", ar[j], j);
	}
}

void rec_MaxInLVL(tree_ptr t, int* ar,int index)
{
	if (!t)
	{
		return;
	}
	ar[index] = MAX_FUNC(ar[index], t->info);
	//call the func recursivly 
	rec_MaxInLVL(t->right, ar, index + 1);
	rec_MaxInLVL(t->left, ar, index + 1);
}

int count_nodes(tree_ptr root)
{
	if (!root)
	{
		return 0;
	}
	else
	{
		return 1 + count_nodes(root->right) + count_nodes(root->left);
	}
}


//recursive way to solve question 3

int q3(tree_ptr root)
{
	if (!root) return 1; //if you finished a sub tree than that tree answers the requriements so return TRUE
	else
	{
		if (root->left && root->right) //if it has a sub right tree and a sub left we need left to be bigger 
		{
			if (count_nodes(root->right) < count_nodes(root->left)) //if the left amount of nodes is bigger than right 
			{ 
				return q3(root->right) * q3(root->left); //than repeat the process on left and right 
			}
			else return 0; //if the amount of nodes on the right is larger than left return 0 causing the end result to be zero/FALSE
		}
		else if (root->left == NULL && root->right) return 0; 
		else return 1;
	}
}


void Q4_MAX(tree_ptr t)
{
	int max,level;
	int  HEIGHT = find_height(t, 0);
	int* ar = (int*)malloc(sizeof(int) * (HEIGHT + 1));
	for (int i = 0; i < HEIGHT+1; i++)ar[i] = 0;
	rec_q4(t, ar, 0);

	//Finding max in counting array
	max = ar[0];
	level = 0;
	for (int k = 1; k < HEIGHT + 1; k++)
	{
		if (max < ar[k])
		{
			max = ar[k];
			level = k;
		}
	}
	printf("MAX AMOUNT OF NODES IS %d, in level %d", max, level);
}


//each level is repersented by an index in ar
void rec_q4(tree_ptr t, int* ar, int index)
{
	if (!t) //if there are no more nodes to count in current sub tree don't do anything
	{
		return;
	}
	ar[index]++; //count amount of nodes in currnet level 
	//call the func recursivly 
	rec_q4(t->right, ar, index + 1); //repeat the process on right sub trees
	rec_q4(t->left, ar, index + 1); //repeat on left
}


void q5_level(int level, tree_ptr t)
{
	q5_fix(level, t, 0);
	printf("\n");
}

void q5_fix(int level, tree_ptr t,int index)
{
	if(!t)
	{
		return;
	}
	if (index == level)
	{
		if (t->right || t->left)
		{
			printf("%d ", t->info);
		}
	}
	q5_fix(level, t->right, index + 1);
	q5_fix(level, t->left, index + 1);
}

//returns zero if a tree is not AVL else returns 
int check_AVL(tree_ptr ROOT)
{
	int HR, HL;
	if (ROOT!=NULL)
	{
		HR = find_height(ROOT->right, 0);
		HL = find_height(ROOT->left, 0);
		if (abs(HR - HL) > 1)
		{
			return 0;
		}
		else
		{
			return (check_AVL(ROOT->right) && check_AVL(ROOT->left));
		}
	}
	else return 1;
}


void insert_AVL(tree_ptr* t, itemType key)
{
	tree_ptr node = (tree_node*)malloc(1 * sizeof(tree_node));
	node->info = key;
	node->left = NULL;
	node->right = NULL;
	Add_2_AVL(t, node);
}

void Add_2_AVL(tree_ptr* t, tree_ptr node)
{
	//INSERT INTO A BINARY SEARCH TREE
	if (!(*t))
	{
		*t = node;
		return;
	}
	if ((*t)->info > node->info)
	{
	  Add_2_AVL(&(*t)->left, node);
	}
	else if ((*t)->info < node->info)
	{
	  Add_2_AVL(&(*t)->right, node);
	}
	else return; //IN A BST NO DUPES

	// ---PERFORM CHECK OF INBALANCE AND REBALANCE--- //
	int key = node->info;
	int BFAC;
	tree_ptr CHILD;
	BFAC = getBfactor((*t));

	//IMBLANCE ON THE RIGHT
	if (BFAC < -1)
	{
		CHILD = (*t)->right;

		if (CHILD->left&&key<CHILD->info) //RIGHT LEFT ROTATION 
		{
			RIGHT_ROTATE(&(*t)->right);
			LEFT_ROTATE(t);
		}
		else if(CHILD->right&&key>CHILD->info) // LEFT LEFT ROTATION
		{
			LEFT_ROTATE(t);		
		}
	}
	else if(BFAC > 1)	//IMBLANCE ON THE LEFT
	{
		CHILD = (*t)->left;
		if (CHILD->left&&key<CHILD->info) //RIGHT ROTATION 
		{
			RIGHT_ROTATE(t);
		}
		else if (CHILD->right&&key>CHILD->info) // LEFT RIGHT ROTATION
		{
			LEFT_ROTATE(&(*t)->right);
			RIGHT_ROTATE(t);
		}
	}
}

void RIGHT_ROTATE(tree_ptr* ROOT)
{
	tree_ptr CHILD;
	tree_ptr x;
	tree_ptr y;

	x = (*ROOT);
	CHILD = (*ROOT)->left;
	y = CHILD->right;
	CHILD->right = x;
	(*ROOT) = CHILD;
	x->left = y;
}

void LEFT_ROTATE(tree_ptr* ROOT)
{
	tree_ptr CHILD;
	tree_ptr x;
	tree_ptr y;

	x = (*ROOT);
	CHILD = (*ROOT)->right;
	y = CHILD->left;
	CHILD->left = x;
	(*ROOT) = CHILD;
	x->right = y;
}

int getBfactor(tree_ptr ROOT)
{
	if (!ROOT) return NULL;
	else return (find_height(ROOT->left,1) - find_height(ROOT->right, 1));
}
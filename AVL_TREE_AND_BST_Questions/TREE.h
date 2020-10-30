#pragma once
#include <stdlib.h>
#include <stdio.h>

typedef int itemType;

typedef struct TREE_NODE
{
	itemType info;
	struct TREE_NODE* left;
	struct TREE_NODE* right;
}tree_node,*tree_ptr;

void Q4_MAX(tree_ptr t);
void Build_Tree(tree_ptr* ptr, itemType key);
void insertTree(tree_ptr* t, itemType key);
void in_Order(tree_ptr* t);
void Pre_Order(tree_ptr* t); 
void Post_Order(tree_ptr* t);
void Level_Order(tree_ptr t);
int exsist_inTree(tree_ptr t, itemType target);
tree_ptr next_InOrder(tree_ptr* t, int target);
tree_ptr Find_father(tree_ptr* root, int target);
void delete_node(tree_ptr* ptr, int target);
int find_height(tree_ptr ROOT, int height);
void max_In_LEVEL(tree_ptr t);
int count_nodes(tree_ptr root);
void q5_level(int level, tree_ptr t);
int q3(tree_ptr root);
int check_AVL(tree_ptr ROOT);
void insert_AVL(tree_ptr* t, itemType key);
int getBfactor(tree_ptr ROOT);
void AVL_IFY(tree_ptr* ROOT);

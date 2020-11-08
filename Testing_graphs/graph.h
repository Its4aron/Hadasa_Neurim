#pragma once

enum { DIRECTED = 10, UNDIRECTED = 11 };

typedef struct AdjNode_type
{
	int dest;
	int w;
	struct AdjNode_type* next;

}adj_node;




typedef struct AdjList_type
{
	adj_node* head; //the head of a list of adj nodes

}adj_list;

typedef struct graph_type
{
	int V; //amount of vertices

	adj_list* array; //Array of all the pointers to each node

}graph;


//func prot
graph* create_Graph(int V);
void add_Edge(graph* g, int src, int dest, int CHECK);
adj_node* create_node(int dest);
void BFS(graph* g);
void DFS(graph* g);
void SCC_func(graph* g);
void Topological_sort(graph* g);
void add_Edge_w(graph* g, int src, int dest, int CHECK, int w);
void Dij_algo(int src, graph* g);
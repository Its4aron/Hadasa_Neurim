#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "queue.h"

typedef enum{FALSE,TRUE} BOOL;

typedef enum{WHITE,GRAY,BLACK} color;

typedef struct 
{
	char edge_type;
	int src;
	int dest;
}edge_type;


void BFS_func(graph* g, BOOL used[], int P[], int dist[], int src);
void DFS_VIST(graph* g, color c_ar[], int P[], int d[], int f[], edge_type** edge_ar, int* time, int u, int* e_ctr);

//Create a graph with V amount of vertices 
graph *create_Graph(int V)
{
	int i;
	graph* g=NULL;
	
	//give g enough size for a graph
	g = (graph*)malloc(sizeof(graph));
	g->V = V;
	g->array = (adj_list*)malloc(sizeof(adj_list) * V);

	for (i = 0; i < V; i++)
		g->array[i].head = NULL;
	
	return g;
}

//Adds an edge from source to dest (becuase graph is undirected the func will also add an edge from dest to src)
void add_Edge(graph* g,int src,int dest)
{
	// -- Add edge from dest to the source -- //
	adj_node *node = create_node(dest);
	node->next = g->array[src].head;
	g->array[src].head = node;
	
	// -- Add edge from source to the dest -- //
	node = create_node(src);
	node->next = g->array[dest].head;
	g->array[dest].head = node;
}
 

adj_node* create_node(int dest)
{
	adj_node* node = NULL;
	node = (adj_node*)malloc(sizeof(adj_node));
	node->dest = dest;
	node->next = NULL;

	return node;
}




void BFS(graph *g)
{
	int src = 0; //from where to start the search

	int i,size = g->V;
	BOOL* used = (BOOL*)malloc(sizeof(BOOL) * size);

	int* P = (int*)malloc(sizeof(int) * size); //an array to hold each parent

	int* dist = (int*)malloc(sizeof(int) * size); //distance from SOURCE


	for (i = 0; i < size; i++)
	{
		used[i] = FALSE;
		P[i] = 0;
		dist[i] = -1;
	}
	
	BFS_func(g, used, P, dist, src);
}

void BFS_func(graph *g,BOOL used[],int P[],int dist[],int src)
{
	int cur,prev,i;
	adj_node* ptr=NULL;
	queue Q;
	queue_init(&Q);

	used[src] = TRUE;
	dist[src] = 0;
	enqueue(&Q, src);

	while (!queue_empty(Q))
	{
		prev = dequeue(&Q);
		ptr = g->array[prev].head;
		//Collect all its children
		while(ptr)
		{
			cur = ptr->dest;
			if (used[cur] == FALSE)
			{
				used[cur] = TRUE;
				dist[cur] = dist[prev] + 1; //update dist from source
				P[cur] = prev;
				enqueue(&Q, cur);
			}
			ptr = ptr->next;
		}
	}
	
	printf("INFO ON EACH NODE'S PARENT AND DISTANCE FROM SRC\n");
	for (i = 0; i < (g->V); i++)
	{
		printf("vertc : %d , parent: %d , distance: %d\n", i, P[i], dist[i]);
	}
}



void DFS(graph* g)
{
	int size,i;
	size = g->V;
	 
	//Array to display the current state of each 
	color* color_array = NULL;
	color_array = (color*)malloc(sizeof(color) * size);

	//Time arrays
	int* d = NULL;
	int* f = NULL;
	d = (int*)calloc(size,sizeof(int));
    f = (int*)calloc(size, sizeof(int));

	//parent array 
	int* P = NULL;
	P = (int*)malloc(sizeof(int) * size);

	//edge type array
	edge_type* edge_array = NULL;


	for (i = 0; i < size; i++)
	{
		color_array[i] = WHITE;
		P[i] = -1;
	}

	int time=0,edge_counter=0;
	for (i = 0; i < size; i++)
	{
		if (color_array[i] == WHITE)
		{
			DFS_VIST(g, color_array, P, d, f, &edge_array, &time, i,&edge_counter);
	    }
	}

	printf("PRINTING ALL INFO ON EACH NODE\n");
	for (i = 0; i < size; i++)
	{
		printf("node: %d, begining time: %d , end time : %d, parent : %d\n", i, d[i], f[i], P[i]);
	}
	printf("PRINTING ALL INFO ON EDGES\n");
	for (i = 0; i < size; i++)
	{
		printf("SOURCE: %d, DEST: %d,TYPE OF EDGE : %c\n", edge_array[i].src, edge_array[i].dest, edge_array[i].edge_type);
	}
	free(color_array);
	free(P);
	free(d);
	free(f);
	free(edge_array);
}

void DFS_VIST(graph* g, color *c_ar, int *P, int *d, int *f, edge_type** edge_ar, int* time, int u, int* e_ctr)
{
	adj_node* ptr = NULL;

	c_ar[u] = GRAY;
	(*time)++;
	d[u] = *time;

	int cur;
	ptr = g->array[u].head;
	while (ptr)
	{
		cur = ptr->dest;
		if (c_ar[cur] == WHITE)
		{
			(*e_ctr)++; //add to the edge counter 
			(*edge_ar) = (edge_type*)realloc((*edge_ar), sizeof(edge_type) * (*e_ctr));
			(*edge_ar)[(*e_ctr) - 1].src = u;
			(*edge_ar)[(*e_ctr) - 1].dest = cur;
			(*edge_ar)[(*e_ctr) - 1].edge_type = 'T';

			P[cur] = u;
			DFS_VIST(g, c_ar, P, d, f, edge_ar, time,cur,e_ctr);
		}
		else if (c_ar[cur] == GRAY)
		{
			(*e_ctr)++; //add to the edge counter 
			(*edge_ar) = (edge_type*)realloc(*edge_ar, sizeof(edge_type) * (*e_ctr));
			(*edge_ar)[(*e_ctr) - 1].src = u;
			(*edge_ar)[(*e_ctr) - 1].dest = cur;
			(*edge_ar)[(*e_ctr) - 1].edge_type = 'B';
		}
		else
		{
			if (d[cur] > d[u])
			{
				(*e_ctr)++; //add to the edge counter 
				(*edge_ar) = (edge_type*)realloc(*edge_ar, sizeof(edge_type) * (*e_ctr));
				(*edge_ar)[(*e_ctr) - 1].src = u;
				(*edge_ar)[(*e_ctr) - 1].dest = cur;
				(*edge_ar)[(*e_ctr) - 1].edge_type = 'F';
			}
			else
			{
				(*e_ctr)++; //add to the edge counter 
				(*edge_ar) = (edge_type*)realloc(*edge_ar, sizeof(edge_type) * (*e_ctr));
				(*edge_ar)[(*e_ctr) - 1].src = u;
				(*edge_ar)[(*e_ctr) - 1].dest = cur;
				(*edge_ar)[(*e_ctr) - 1].edge_type = 'C';
			}


		}
		ptr = ptr->next;
	}
	c_ar[u] = BLACK;
	(*time)++;
	f[u] = *time;
}


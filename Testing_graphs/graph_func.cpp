#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "queue.h"
#include "stack.h"

typedef enum { FALSE, TRUE } BOOL;

typedef enum { WHITE, GRAY, BLACK } color;

typedef struct
{
	char edge_type;
	int src;
	int dest;
}edge_type;

adj_node* create_node_w(int dest, int w);
void BFS_func(graph* g, BOOL used[], int P[], int dist[], int src);
void DFS_VIST(graph* g, color c_ar[], int P[], int d[], int f[], edge_type** edge_ar, int* time, int u, int* e_ctr);
void DFS_VIST_SCC(graph* g, color* c_ar, int* P, int* d, int* f, edge_type** edge_ar, int* time, int u, int* e_ctr, stack* s);
void DFS_SCC(graph* g, int* st, int* end, int** end_arr);
void dfs2(int* vis, int* SCC_REP, int u, int rep, graph* g);
void dfs1(int* vis, stack* s, int u, graph* g);
int min_distance(int* dist, int* temp,int size);
void Dij_search(int src, graph* g, int** g_matrix);

//Create a graph with V amount of vertices 
graph* create_Graph(int V)
{
	int i;
	graph* g = NULL;

	//give g enough size for a graph
	g = (graph*)malloc(sizeof(graph));
	g->V = V;
	g->array = (adj_list*)malloc(sizeof(adj_list) * V);

	for (i = 0; i < V; i++)
		g->array[i].head = NULL;

	return g;
}

//Adds an edge from source to dest (becuase graph is undirected the func will also add an edge from dest to src)
void add_Edge(graph* g, int src, int dest,int CHECK)
{
	// -- Add edge from dest to the source -- //
	adj_node* node = create_node(dest);
	node->next = g->array[src].head;
	g->array[src].head = node;

	if (CHECK == UNDIRECTED)
	{
		// -- Add edge from source to the dest -- //
		node = create_node(src);
		node->next = g->array[dest].head;
		g->array[dest].head = node;
	}
}

adj_node* create_node(int dest)
{
	adj_node* node = NULL;
	node = (adj_node*)malloc(sizeof(adj_node));
	node->dest = dest;
	node->next = NULL;
	node->w = 0;

	return node;
}

void BFS(graph* g)
{
	int src = 0; //from where to start the search

	int i, size = g->V;
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

void BFS_func(graph* g, BOOL used[], int P[], int dist[], int src)
{
	int cur, prev, i;
	adj_node* ptr = NULL;
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
		while (ptr)
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
	int size, i;
	size = g->V;

	//Array to display the current state of each 
	color* color_array = NULL;
	color_array = (color*)malloc(sizeof(color) * size);

	//Time arrays
	int* d = NULL;
	int* f = NULL;
	d = (int*)calloc(size, sizeof(int));
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

	int time = 0, edge_counter = 0;
	for (i = 0; i < size; i++)
	{
		if (color_array[i] == WHITE)
		{
			DFS_VIST(g, color_array, P, d, f, &edge_array, &time, i, &edge_counter);
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

void DFS_VIST(graph* g, color* c_ar, int* P, int* d, int* f, edge_type** edge_ar, int* time, int u, int* e_ctr)
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
			DFS_VIST(g, c_ar, P, d, f, edge_ar, time, cur, e_ctr);
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

void Topological_sort(graph* g)
{
	int des,i,size = g->V;

	queue q;
	queue_init(&q);

	int* indegree = NULL;
	indegree = (int*)calloc(size,sizeof(int));
	if (!indegree) exit(1);

	adj_node* ptr=NULL;
	for (i = 0; i < size; i++)
	{
		ptr = g->array[i].head;
		while (ptr)  //if you have edge go in 
		{
			des = ptr->dest; 
			indegree[des]++;  //add to indegree 
			ptr = ptr->next; //move to the next node you are connected to
		}
	}

	//add all the nodes with no indegree to a queue
	for (i = 0; i < size; i++)
	{
		if (!indegree[i])
			enqueue(&q, i);
	}

	int u;
	while (!queue_empty(q))
	{
		des = dequeue(&q);
		printf("%d ", des);
		ptr = g->array[des].head;
		while (ptr)
		{
			u = ptr->dest;
			ptr = ptr->next;
			indegree[u]--;
			if (!indegree[u]) enqueue(&q, u);
		}
	}
	printf("\n");

	for (i = 0; i < size; i++)
	{
		if (indegree[i]) printf("CYCLE\n");
	}
}

void SCC_func(graph* g)
{
	int i,size = g->V;

	int* vis1 = NULL;
	vis1 = (int*)calloc(size, sizeof(int));

	stack s;
	stack_init(&s);

	for (i = 0; i < size; i++)
	{
		if(!vis1[i])
		   dfs1(vis1, &s, i, g);
	}
	// --REV GRAPH -- //
	graph *flipped_g;
	flipped_g = create_Graph(size);

	adj_node* ptr=NULL;
	int u;
	for (i = 0; i < size; i++)
	{
		ptr = g->array[i].head;
		while (ptr)
		{
			u = ptr->dest;
			add_Edge(flipped_g, u, i, DIRECTED);
			ptr = ptr->next;
		}
	}

	int* vis = NULL;
	int* SCC_rep  = NULL;
	vis = (int*)calloc(size, sizeof(int));
	SCC_rep = (int*)calloc(size, sizeof(int));

	// --CREATE AN ARRAY HOLDING THE REPERSENTIVE FOR EACH SCC-- //
	for (i = 0; i < size; i++)
	{
		u = stack_top(s);
		stack_pop(&s);

		if (!vis[u])
			dfs2(vis, SCC_rep, u, u,flipped_g);
	}

	for (i = 0; i < size; i++)
	{
		printf("NODE %d HAS A REP OF: %d\n", i, SCC_rep[i]);
	}

}

void dfs1(int* vis,stack *s, int u,graph* g)
{
	int v;

	vis[u] = 1;

	adj_node* ptr = NULL;
	ptr = g->array[u].head;
	while (ptr)
	{
		v = ptr->dest;
		if (!vis[v])
			dfs1(vis, s, v, g);
		ptr = ptr->next;
	}
	stack_push(s, u);
}

void dfs2(int* vis, int* SCC_REP, int u, int rep,graph *g)
{
	int v;

	vis[u] = 1;
	SCC_REP[u] = rep;
	
	adj_node* ptr = NULL;
	ptr = g->array[u].head;
	while (ptr)
	{
		v = ptr->dest;
		if(!vis[v])
			dfs2(vis, SCC_REP,v,rep,g);
		ptr = ptr->next;
	}
}


adj_node* create_node_w(int dest,int w)
{
	adj_node* node = NULL;
	node = (adj_node*)malloc(sizeof(adj_node));
	node->dest = dest;
	node->next = NULL;
	node->w = w;

	return node;
}

void add_Edge_w(graph* g, int src, int dest, int CHECK,int w)
{
	// -- Add edge from dest to the source -- //
	adj_node* node = create_node_w(dest,w);
	node->next = g->array[src].head;
	g->array[src].head = node;

	if (CHECK == UNDIRECTED)
	{
		// -- Add edge from source to the dest -- //
		node = create_node_w(src,w);
		node->next = g->array[dest].head;
		g->array[dest].head = node;
	}
}

void Dij_algo(int src, graph* g)
{
	//Create a matrix holding each weight between node 
	int j,i,size = g->V;
	int** g_matrix=NULL;
	g_matrix = (int**)malloc(sizeof(int) * size);

	for (i = 0; i < size; i++) g_matrix[i] = (int*)malloc(sizeof(int) * size);
	
	adj_node *ptr = NULL;
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			g_matrix[i][j] = 0;
		}
	}

	int x;
	//row
	for (i = 0; i < size; i++)
	{
			ptr = g->array[i].head;
			g_matrix[i][i] = 0;
			while (ptr)
			{
				x = ptr->dest;
				g_matrix[i][x] = ptr->w;
				ptr = ptr->next;
			}
			for (j = 0; j < size; j++)
			{
				if (i == j)g_matrix[i][i] = 0;
				else if (g_matrix[i][j] == 0)
					g_matrix[i][j] = INT_MAX;
			}
	}
	Dij_search(src, g, g_matrix);
}


void Dij_search(int src, graph* g,int **g_matrix)
{
	int i,size;
	size = g->V;

	//Parent array
	int* Pa = NULL;
	Pa = (int*)calloc(size, sizeof(int));
	if (!Pa) exit(1);
	else Pa[src] = -1;
	
	//Distance array
	int* dist = NULL;
	dist = (int*)malloc(sizeof(int)*size);
	if (!dist) exit(1);
	else dist[src] = 0;

	for (i = 0; i < size; i++)
	{
		if (i == src) continue;
		dist[i] = INT_MAX;
	}

	//P
	int p_counter = 0;
	int* P = NULL;
	P = (int*)calloc(size, sizeof(int));
	if (!P)exit(1);
	else P[p_counter++] = src;
    
	//Temp
	int tsize=size-1,check=0;
	int* temp = NULL;
	temp = (int*)calloc(size, sizeof(int));
	if (!temp)exit(1);
	else
	{
		for (i = 0; i < size; i++)
		{
			if (i == src) 
			{
				continue;
			}
			temp[i] = 1;
		}
	}

	//Declaring the distance array 
	
	for (i = 0; i < size; i++)
	{
		if (i == src) continue;
		dist[i] = g_matrix[src][i];

		if (dist[i] != INT_MAX) Pa[i] = src; //find all the nodes connected to the source 
		else Pa[i] = -1;
	}
	

	
	int K,num;
	int x,y;
	while (1)
	{
		K = min_distance(dist, temp, size);
		if (K == -1)
		{
			break;
		}

		P[p_counter++] = K;

		//Delete from temp the curr smallest index
		if (temp[K])
		{
			temp[K] = 0;
		}

		for (i = 0; i < size; i++)
		{
			if (temp[i])
			{
				if (dist[K] == INT_MAX || g_matrix[K][i] == INT_MAX)
				{
					x = INT_MAX;
				}
				else x = dist[K] + g_matrix[K][i];


				y = dist[i];
				if (x < y)
				{
					Pa[i] = K;
				}
				dist[i] = x < y ? x : y;
			}
		}
	}

	for (i = 0; i < size; i++)
	{
		printf("Node %d parent is ->>>> %d\n", i, Pa[i]);
		
	}
	for (i = 0; i < size; i++)
	{
		printf("Node dist  %d is ->>> %d \n", i, dist[i]);
	}
	for (i = 0; i < size; i++)
	{
		printf("P NUMBER:%d IS %d \n", i, P[i]);
	}

	free(temp);
	free(Pa);
	free(P);
	free(dist);
	for (i = 0; i < size; i++)
	{
		free(g_matrix[i]);
	}
	free(g_matrix);

}



int min_distance(int* dist, int* temp,int size)
{
	int i, cur_index;
	int min_index=-1;
	int min = INT_MAX;

	

	for (i = 0; i < size; i++)
	{	
		cur_index = i;
		if (temp[i]&&dist[cur_index]<=min)
		{
			min = dist[cur_index];
			min_index = cur_index;
		}
	}
	return min_index;
}








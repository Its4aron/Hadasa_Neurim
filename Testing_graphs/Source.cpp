#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"



void main()
{
	graph *g;
	g = create_Graph(4);
	add_Edge(g, 0, 2);
	add_Edge(g, 0, 1);
	add_Edge(g, 1, 2);
	add_Edge(g, 2, 3);
	DFS(g);
	
}
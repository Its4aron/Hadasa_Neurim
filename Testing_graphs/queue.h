#pragma once

typedef int queue_item;

typedef struct node_type
{
	queue_item info;
	struct node_type* next;
}node;

typedef struct
{
	node* head;
	node* rear;

}queue;

void queue_init(queue* q);

void enqueue(queue* q, queue_item x);

queue_item dequeue(queue* q);

queue_item queue_top(queue q);

int queue_empty(queue q);

void queue_print(queue* q);



#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include "queue.h"

void queue_init(queue* q)
{
    q->head = q->rear = NULL;
}

void enqueue(queue* q, queue_item x)
{
    node* a = (node*)malloc(sizeof(node));
    a->info = x;
    a->next = NULL;
    if (queue_empty(*q))
    {
        q->head = q->rear = a;
    }
    else
    {
        q->rear->next = a;
        q->rear = a;
    }
}

queue_item dequeue(queue* q)
{
    queue_item x = q->head->info;
    node* a = q->head;
    q->head = q->head->next;
    if (q->head == NULL) q->rear = NULL;
    free(a);
    return x;
}


queue_item queue_top(queue q)
{
    return q.head->info;
}

int queue_empty(queue q)
{
    return q.head == NULL;
}

void queue_print(queue* q)
{
    queue temp;
    queue_init(&temp);
    while (!queue_empty(*q))
    {
        printf("%d ", queue_top(*q));
        enqueue(&temp, dequeue(q));
    }
    printf("\n");
    while (!queue_empty(temp))
    {
        enqueue(q, dequeue(&temp));
    }
}
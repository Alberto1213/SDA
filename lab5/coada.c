#include <stdio.h>
#include <stdlib.h>

typedef struct qnode
{
    int val;
    struct qnode *next;
} qnode;

typedef struct Queue
{
    struct qnode *front;
    struct qnode *rear;
} Queue;

void init_queue(Queue **q)
{
    *q = malloc(sizeof(Queue));
    (*q)->front = malloc(sizeof(qnode));
    (*q)->rear = malloc(sizeof(qnode));
    (*q)->front = NULL;
    (*q)->rear = NULL;
}

struct qnode *new_qnode(int val)
{
    qnode *temp = malloc(sizeof(qnode));      
    temp->val = val;               
    temp->next = NULL;
    return temp;
}

void enqueue(Queue *q, int val)
{
    qnode *temp = new_qnode(val);            
    if (q->rear == NULL && q->front == NULL) 
    {
        q->front = temp;
        q->rear = temp;
        return;
    }
    else 
    {
        q->rear->next = temp;
        q->rear = q->rear->next;
    }
}

int dequeue(Queue *q)
{
    if (q->front == NULL)
    {
        return;
    }
    else
    {
        qnode *temp = q->front;
        q->front = q->front->next;
        return temp;
    }
}

int isEmpty(Queue *q)
{
    if(q->front == NULL)
        return 1;
    else return 0;    
}

int first(Queue *q)
{
    if(isEmpty(q) == 0)
        return q->front->val;
    else exit(1);    
}

int last(Queue *q)
{
    if(isEmpty(q) == 0)
        return q->rear->val;
    else exit(1);    
}

int main()
{
    Queue *q;
    init_queue(&q);
    printf("%d\n", isEmpty(q));
    enqueue(q,1);
    enqueue(q,2);
    enqueue(q,3);
    printf("%d\n", first(q));
    printf("%d\n", last(q));
    dequeue(q);
    printf("%d", first(q));

    return 0;
}

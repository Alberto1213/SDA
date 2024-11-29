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
        exit(-1);
    }
    else
    {
        qnode *temp = q->front;
        q->front = q->front->next;
        return temp->val;
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
struct Queue *f4(Queue *c)
{
    Queue *r;
    init_queue(&r);
    int temp;
    while(isEmpty(c) != 1)
    {
        temp = dequeue(c);
        if(temp % 2 == 0)
            enqueue(r,temp);
    }
    return r;
}
void print_queue(Queue *q)
{
    qnode *temp = q->front;
    while(temp != NULL)
    {
        printf("%d ", temp->val);
        temp  = temp->next;
    }
}
int main()
{
    Queue *c;
    init_queue(&c);
    Queue *r;
    int n;
    scanf("%d", &n);
    for(int i = 0; i <= n; i++)
        enqueue(c,i);           
    r = f4(c);
    print_queue(r);
    return 0;
}
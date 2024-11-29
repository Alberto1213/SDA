#include <stdio.h>
#include <stdlib.h>

typedef struct graf
{
    int n;
    int **mat;
} graf;

void init(graf **g, int n)
{
    *g = (graf *)malloc(sizeof(graf));
    (*g)->n = n;
    (*g)->mat = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
        (*g)->mat[i] = (int *)malloc(n * sizeof(int));
}

void add_edge(graf **g, int i, int j)
{
    (*g)->mat[i][j] = 1;
    (*g)->mat[j][i] = 1;
}

void delete_edge(graf **g, int i, int j)
{
    (*g)->mat[i][j] = 0;
    (*g)->mat[j][i] = 0;
}

void print_edges(graf *g)
{
    for (int i = 0; i < (g->n) - 1; i++)
        for (int j = i + 1; j < g->n; j++)
            if (g->mat[i][j] == 1)
                printf("%d -> %d\n", i, j);
}
int grad(graf *g, int i)
{
    int res = 0;
    for (int j = 0; j < g->n; j++)
        if (g->mat[i][j] == 1)
            res++;

    return res;
}

void dfs(graf *g, int start, int *v)
{
    v[start] = 1;
    printf("%d ", start);
    for (int i = 0; i < g->n; i++)
        if (g->mat[start][i] == 1 && v[i] == 0)
            dfs(g, i, v);
}

void conex(graf *g, int start, int *v)
{
    int count = 0;
    for (int i = 0; i < g->n; i++)
        if (v[i] == 0)
        {
            printf("conex \n");
            dfs(g, i, v);
            count++;
            printf("\n");
        }
    printf("\nnumar de componente conexe:%d\n", count);
}

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

void dequeue(Queue *q)
{
    if (q->front == NULL)
    {
        return;
    }
    else
    {
        qnode *temp = q->front;
        q->front = q->front->next;
        free(temp);
    }
}

int isEmpty(Queue *q)
{
    if (q->front == NULL)
        return 1;
    else
        return 0;
}

int first(Queue *q)
{
    if (isEmpty(q) == 0)
        return q->front->val;
    else
        exit(1);
}

int last(Queue *q)
{
    if (isEmpty(q) == 0)
        return q->rear->val;
    else
        exit(1);
}

void bfs(graf *g, int start)
{
    int *v = malloc(g->n * sizeof(int));
    for(int i = 0; i < g->n; i++)
        v[i] = 0;

    Queue *q;
    init_queue(&q);
    
    enqueue(q,start);
    v[start] = 1;

    while(q->front != NULL)
    {
        int node = q->front->val;
        dequeue(q);
        printf("%d ", node);

        for(int i = 0; i < g->n; i++)
        {
            if(v[i] == 0 && g->mat[node][i] == 1)
            {
                //printf("\n%d - %d\n", start, i);
                enqueue(q,i);
                v[i] = 1;
            }
        }
    }
}
int main()
{
    graf *g;
    int n;
    scanf("%d", &n);
    init(&g, n);
    for (int i = 0; i < n - 1; i++)
        add_edge(&g, i, i + 1);

    add_edge(&g, 1, 3);
    print_edges(g);
    delete_edge(&g, 1, 2);
    printf("%d\n", grad(g, 1));

    int *v_dfs = malloc(n * sizeof(int));
    int *v_conex = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
    {
        v_dfs[i] = 0;
        v_conex[i] = 0;
    }
    printf("\n----------------DFS----------------\n");
    dfs(g, 1, v_dfs);
    printf("\n----------------BFS----------------\n");
    bfs(g, 1);
    printf("\n----------------CONEX----------------\n");
    conex(g, 1, v_conex);
    return 0;
}

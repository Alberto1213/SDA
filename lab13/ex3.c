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
}

void print_edges(graf *g)
{
    for (int i = 0; i < (g->n); i++)
        for (int j = 1; j < g->n; j++)
            if (g->mat[i][j] == 1)
                printf("%d -> %d\n", i, j);
}
int grad_in(graf *g, int i)
{
    int res = 0;
    for (int j = 0; j < g->n; j++)
        if (g->mat[j][i] == 1)
            res++;

    return res;
}

int main()
{
    graf *g;
    int n,m;
    scanf("%d %d", &n, &m);
    init(&g, n);
    add_edge(&g,1,3);
    add_edge(&g,1,4);
    add_edge(&g,3,2);
    add_edge(&g,3,4);
    add_edge(&g,4,2);
    add_edge(&g,5,2);
    add_edge(&g,5,4);
    add_edge(&g,5,1);
    print_edges(g);
    int max = 0;
    for(int i = 1; i <= g->n; i++)
        if(grad_in(g,i) > max)
            max = grad_in(g,i);

    for(int i = 1; i <= g->n; i++)
        if(grad_in(g,i) == max)
            printf("%d ", i);        
    return 0;
}
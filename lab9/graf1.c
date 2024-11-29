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

void delete_edge(graf **g, int i, int j)
{
    (*g)->mat[i][j] = 0;
}

void print_edges(graf *g)
{
    for (int i = 0; i < (g->n) - 1; i++)
        for (int j = i + 1; j < g->n; j++)
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

int grad_ext(graf *g, int i)
{
    int res = 0;
    for (int j = 0; j < g->n; j++)
        if (g->mat[i][j] == 1)
            res++;

    return res;
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
    // delete_edge(&g, 1, 2);
    printf("%d\n", grad_in(g, 1));
    printf("%d\n", grad_ext(g, 1));
    return 0;
}

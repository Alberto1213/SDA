#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

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

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            (*g)->mat[i][j] = INT_MAX;

    for (int i = 0; i < n; i++)
        (*g)->mat[i][i] = 0;
}

void add_edge(graf **g, int i, int j, int cost)
{
    (*g)->mat[i][j] = cost;
}

void print_edges(graf *g)
{
    for (int i = 0; i < (g->n) - 1; i++)
        for (int j = i + 1; j < g->n; j++)
            if (g->mat[i][j] == 1)
                printf("%d -> %d\n", i, j);
}

void print_mat(int **mat, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        printf("\n");
        for (int j = 0; j < m; j++)
            printf("%d ", mat[i][j]);
    }
    printf("\n");
}

void BellmanFord(graf *g, int s, int *distance, int *previous)
{
    for (int i = 0; i < g->n; i++)
    {
        distance[i] = INT_MAX;
        previous[i] = -1;
    }

    distance[s] = 0;
    for(int k = 0; k < g->n - 1; k++){
    for (int i = 0; i < g->n; i++)
        for (int j = 0; j < g->n; j++)
        {
            if (g->mat[j][i] != 0 && distance[j] != INT_MAX && g->mat[j][i] != INT_MAX) //fiind pe matricea de adiacenta trebuie sa verificam daca muchia exista si e diferita de inf
            {
                int tempdist = distance[j] + g->mat[j][i];
                if (tempdist < distance[i])
                {
                    distance[i] = tempdist;
                    previous[i] = j;
                }
            }
        }
        }

    /*for (int i = 0; i < g->n; i++)
        for (int j = 0; j < g->n; j++)
            if (g->mat[i][j] != 0)
                if (distance[i] + g->mat[i][j] < distance[j])
                {
                    printf("ERROR\n");
                    return;
                }*/
}

int main()
{
    int n;
    int src;
    scanf("%d", &n);
    scanf("%d", &src);
    graf *g;
    init(&g, n);
    add_edge(&g, 0, 1, 4);
    add_edge(&g, 0, 3, 5);
    // add_edge(&g,1,0,4);
    add_edge(&g, 1, 2, 3);
    add_edge(&g, 3, 1, -2);
    add_edge(&g, 3, 2, 10);

    int *distance = malloc(g->n * sizeof(int));
    int *previous = malloc(g->n * sizeof(int));

    BellmanFord(g, src, distance, previous);

    for (int i = 0; i < g->n; i++)
    {
        printf("Distances:\n");
        printf("%d-%d: %d", src, i, distance[i]);
        printf("\n");
        printf("Parent of node %d is:%d", i, previous[i]);
        printf("\n");
    }

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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

void add_edge(graf **g, int i, int j,int cost)
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

void print_mat(int **mat,int n)
{
    for(int i = 0; i < n; i++)
    {   
        printf("\n");
        for(int j = 0; j < n; j++) 
            printf("%d ", mat[i][j]);
    }
    printf("\n");
}
int **floyd_warshall(graf *g)
{
    int n = g->n;
    int **d = (int **)malloc(n * sizeof(int*));
    for(int i = 0; i < n; i++)
        d[i] = (int *)malloc(n * sizeof(int));

    for(int i = 0; i < n; i++)
        {   
            d[i][i] = 0;
            for(int j = 0; j < n; j++)
                {
                    if(g->mat[i][j] != 0)
                    d[i][j] = g->mat[i][j];
                else 
                if(i != j)
                    d[i][j] = 1000;
                }
        }    
    print_mat(d,n);

    for(int k = 0; k < n; k++)
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                if(d[i][j] > d[i][k] + d[k][j])
                    d[i][j] = d[i][k] + d[k][j];   
    return d;    
}
int solve(int **mat,int n)
{
    int min_sum = INT_MAX;
    int line = -1;
    for(int i = 0; i < n; i++)
    {
        int sum = 0;
        for(int j = 0; j < n; j++)
            sum += mat[i][j];
        if(sum < min_sum)
            {
                min_sum = sum;
                line = i;
            }            
    }
    return line;
}
int main()
{
    graf *g;
    int n;
    scanf("%d", &n);
    init(&g, n);
    /*add_edge(&g,0,1,1);
    add_edge(&g,0,2,10);
    add_edge(&g,1,2,2);*/
    add_edge(&g,0,2,5);
    add_edge(&g,0,3,5);
    add_edge(&g,0,4,4);
    add_edge(&g,1,2,5);
    add_edge(&g,1,3,1);
    add_edge(&g,1,4,2);
    add_edge(&g,2,5,2);
    add_edge(&g,3,5,4);
    add_edge(&g,4,5,4);
    print_mat(g->mat,n);
    printf("\n");

    int  **f = floyd_warshall(g);
    print_mat(f,n);
    printf("\n");
    printf("%d", solve(f,n));
    return 0;
}
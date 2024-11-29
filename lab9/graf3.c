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

    for (int i = 0; i < n; i++)
	    for (int j = 0; j < n; j++)
			(*g)->mat[i][j] = INT_MAX;
	
    for (int i = 0; i < n; i++)
		(*g)->mat[i][i] = 0;    
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
int minimum_distance (int *dist, int *visited, int n)
{
	int min = INT_MAX, position;
	for (int i = 0; i < n; i++)
	{
		if (visited[i] == 0 && dist[i] <= min)
		{
			min = dist[i];
			position = i;
		}
	}
	return position;
}
void Dijkstra (graf *graph, int src)
{
	int n = graph->n;
	int *visited = (int *) malloc (n * sizeof(int));
	int *dist = (int *) malloc (n * sizeof(int));

	for (int i = 0; i < n; i++)
	{
		visited[i] = 0;
		dist[i] = graph->mat[src][i];
	}
	dist[src] = 0;
	visited[src] = 1;
	for (int i = 0; i < n-1; i++)
	{
		int u = minimum_distance(dist, visited, n);
		visited[u] = 1;
		
		for (int v = 0; v < n; v++)
		{
			if ((visited[v] == 0) && (dist[u] != INT_MAX) && (dist[u] + graph->mat[u][v] < dist[v]) && (graph->mat[u][v] !=0) && (graph->mat[u][v] != INT_MAX))
			{
				dist[v] = dist[u] + graph->mat[u][v];
			}
		}
	}
	for (int i = 0; i < n; i++)
		printf("%d ", dist[i]);
	printf("\n");
	free(visited);
	free(dist);
}
int main()
{
    graf *g;
    int n;
    scanf("%d", &n);
    init(&g, n);
    add_edge(&g,0,1,1);
    add_edge(&g,0,2,10);
    add_edge(&g,1,2,2);
    print_mat(g->mat,n);
    printf("\n");
    Dijkstra(g, 0);
    return 0;
}
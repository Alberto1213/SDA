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
    (*g)->mat[j][i] = cost;
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
int* Dijkstra (graf *graph, int src)
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
	/*for (int i = 0; i < n; i++)
		printf("%d ", dist[i]);
	printf("\n");*/
    return dist;
	free(visited);
	free(dist);
}
int main()
{
    int min = 1000;
    int poz = -1;
    graf *g;
    int n;
    scanf("%d", &n);
    int c;
    scanf("%d", &c);
    init(&g, n);
    add_edge(&g,0,1,4);
    add_edge(&g,0,4,1);
    add_edge(&g,0,6,2);
    add_edge(&g,1,2,9);
    add_edge(&g,1,3,2);
    add_edge(&g,1,5,2);
    add_edge(&g,1,6,1);
    add_edge(&g,4,5,7);
    print_mat(g->mat,n);

    int nr_porti;
    scanf("%d", &nr_porti);
    int *porti = malloc(nr_porti * sizeof(int));
    for(int i = 0;i < nr_porti; i++)
    {
        scanf("%d", &porti[i]);
        int *dist = Dijkstra(g,porti[i]);
        
        if(min > dist[c])
        {
            min = dist[c];
            poz = porti[i] + 1;
        }
        free(dist);
    }     
    printf("\n");
    printf("%d", poz);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct graf
{
    int n;
    int m;
    int **mat;
} graf;

void init(graf **g, int n, int m)
{
    *g = (graf *)malloc(sizeof(graf));
    (*g)->n = n;
    (*g)->m = m;
    (*g)->mat = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
        (*g)->mat[i] = (int *)malloc(n * sizeof(int));

    //for (int i = 0; i < n; i++)
	    //for (int j = 0; j < n; j++)
			//(*g)->mat[i][j] = INT_MAX;
	
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

void print_mat(int **mat,int n,int m)
{
    for(int i = 0; i < n; i++)
    {   
        printf("\n");
        for(int j = 0; j < m; j++) 
            printf("%d ", mat[i][j]);
    }
    printf("\n");
}

int **mat_to_edges(graf *g)
{ 
    int **edges = (int **)malloc(g->m *  sizeof(int*));
    for(int i = 0; i < g->m; i++)
        edges[i] = (int *)malloc(3 * sizeof(int));

    int k = 0;
    for(int i = 0; i < g->n; i++)
        for(int j = i; j < g->n; j++) 
            if(g->mat[i][j] != 0)
            {
                edges[k][0] = i;
                edges[k][1] = j;
                edges[k][2] = g->mat[i][j];
                k++;
            }

    return edges;        
}
// Comparator function to use in sorting
int comparator(const void* p1, const void* p2)
{
	const int(*x)[2] = p1;
	const int(*y)[2] = p2;

	return (*x)[2] - (*y)[2];
}

// Initialization of parent[] and rank[] arrays
void makeSet(int *parent, int *rank, int n)
{
	for (int i = 0; i < n; i++) {
		parent[i] = i;
		rank[i] = 0;
	}
}

// Function to find the parent of a node
int findParent(int *parent, int component)
{
	if (parent[component] == component)
		return component;

	return parent[component]
		= findParent(parent, parent[component]);
}

// Function to unite two sets
void unionSet(int u, int v, int *parent, int *rank, int n)
{
	// Finding the parents
	u = findParent(parent, u);
	v = findParent(parent, v);

	if (rank[u] < rank[v]) {
		parent[u] = v;
	}
	else if (rank[u] > rank[v]) {
		parent[v] = u;
	}
	else {
		parent[v] = u;

		// Since the rank increases if
		// the ranks of two sets are same
		rank[u]++;
	}
}

// Function to find the MST
void kruskalAlgo(graf *g)
{
    int **edge = mat_to_edges(g);
	// First we sort the edge array in ascending order
	// so that we can access minimum distances/cost
	qsort(edge, g->m, sizeof(edge[0]), comparator);
    print_mat(edge,g->m,3);
    printf("\n");
	int *parent = malloc(g->m * sizeof(int));
	int *rank = malloc(g->m * sizeof(int));

	// Function to initialize parent[] and rank[]
	makeSet(parent, rank, g->m);

	// To store the minimun cost
	int minCost = 0;

	printf(
		"Following are the edges in the constructed MST\n");
	for (int i = 0; i < g->m; i++) {
		int v1 = findParent(parent, edge[i][0]);
		int v2 = findParent(parent, edge[i][1]);
		int wt = edge[i][2];

		// If the parents are different that
		// means they are in different sets so
		// union them
		if (v1 != v2) {
			unionSet(v1, v2, parent, rank, g->m);
			minCost += wt;
			printf("%d -- %d == %d\n", edge[i][0],
				edge[i][1], wt);
		}
	}

	printf("Minimum Cost Spanning Tree: %d\n", minCost);
}

int main()
{
    int n;
    int m;
    graf *g;
    scanf("%d%d", &n, &m);
    init(&g,n,m);
    add_edge(&g,0,1,6);
    add_edge(&g,0,5,5);
    add_edge(&g,1,2,1);
    add_edge(&g,1,5,7);
    add_edge(&g,2,3,2);
    add_edge(&g,2,4,9);
    add_edge(&g,2,5,8);
    add_edge(&g,3,4,3);
    add_edge(&g,4,5,4);
    add_edge(&g,6,7,4);
    add_edge(&g,6,8,3);
    add_edge(&g,7,8,1);
    kruskalAlgo(g);
    printf("\n");
    int **edge = mat_to_edges(g);
    print_mat(edge,m,3);   
    return 0;
}
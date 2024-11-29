#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

typedef struct graf
{
    int n;
    int m;
    int **mat;
} graf;

void init(graf **g, int n)
{
    *g = (graf *)malloc(sizeof(graf));
    (*g)->n = n;
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


// A utility function to find the vertex with
// minimum key value, from the set of vertices
// not yet included in MST
int minKey(int *key, bool *mstSet,int n)
{
	// Initialize min value
	int min = INT_MAX;
    int min_index;

	for (int v = 0; v < n; v++)
		if (mstSet[v] == false && key[v] < min)
			min = key[v], min_index = v;

	return min_index;
}

// A utility function to print the
// constructed MST stored in parent[]
int printMST(int *parent, graf *g)
{
	printf("Edge \tWeight\n");
	for (int i = 1; i < g->n; i++)
		printf("%d - %d \t%d \n", parent[i], i,
			g->mat[i][parent[i]]);
}

// Function to construct and print MST for
// a graph represented using adjacency
// matrix representation
void primMST(graf *g)
{
	// Array to store constructed MST
	int *parent = malloc(g->n *  sizeof(int));
	// Key values used to pick minimum weight edge in cut
	int *key = malloc(g->n * sizeof(int));
	// To represent set of vertices included in MST
	bool *mstSet = malloc(g->n * sizeof(bool));

	// Initialize all keys as INFINITE
	for (int i = 0; i < g->n; i++)
		{
            key[i] = INT_MAX;
            mstSet[i] = false;
        }

	// Always include first 1st vertex in MST.
	// Make key 0 so that this vertex is picked as first
	// vertex.
	key[0] = 0;

	// First node is always root of MST
	parent[0] = -1;

	// The MST will have V vertices
	for (int count = 0; count < g->n - 1; count++) {
		
		// Pick the minimum key vertex from the
		// set of vertices not yet included in MST
		int u = minKey(key, mstSet,g->n);

		// Add the picked vertex to the MST Set
		mstSet[u] = true;

		// Update key value and parent index of
		// the adjacent vertices of the picked vertex.
		// Consider only those vertices which are not
		// yet included in MST
		for (int v = 0; v < g->n; v++)

			// graph[u][v] is non zero only for adjacent
			// vertices of m mstSet[v] is false for vertices
			// not yet included in MST Update the key only
			// if graph[u][v] is smaller than key[v]
			if (g->mat[u][v] && mstSet[v] == false
				&& g->mat[u][v] < key[v])
				{
                    parent[v] = u;
                    key[v] = g->mat[u][v];
                }
	}

	// print the constructed MST
	printMST(parent, g);
}

// Driver's code
int main()
{
    int n;
    scanf("%d", &n);
    graf *g;
    init(&g,n);
    add_edge(&g,0,1,2);
    add_edge(&g,0,3,6);
    add_edge(&g,1,2,3);
    add_edge(&g,1,3,8);
    add_edge(&g,1,4,5);
    add_edge(&g,2,4,7);
    add_edge(&g,3,4,9);
    primMST(g);

	return 0;
}
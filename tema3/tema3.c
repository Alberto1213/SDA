/*RADU ALBERTO-MIHAI 331CC*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    int index;
    int cost;
    struct node *next;
} node;

typedef struct list
{
    struct node *src;
} list;

typedef struct graf
{
    int n;
    int m;
    struct list **array_of_lists;
} graf;

struct node *new_node(int cost, int index)
{
    node *new = malloc(sizeof(node));
    new->index = index;
    new->cost = cost;
    return new;
}

void init_graf(graf **g, int n, int m)
{
    *g = malloc(sizeof(graf));
    (*g)->m = m;
    (*g)->n = n;
    (*g)->array_of_lists = malloc(n * sizeof(list*));
    for (int i = 0; i < (*g)->n; i++)
    {
        (*g)->array_of_lists[i] = malloc(sizeof(list));
        (*g)->array_of_lists[i]->src = NULL;
    }
}

int check_node(int n, char *name, char **arr)
{
    int ok = 0;
    for (int i = 0; i < n; i++)
        if (strcmp(arr[i], name) == 0)
        {
            ok = 1;
            break;
        }
    return ok;
}

int get_index(int n, char *name, char **arr)
{
    int index = -1;
    for (int i = 0; i < n; i++)
        if (strcmp(arr[i], name) == 0)
        {
            index = i;
            break;
        }
    return index;
}

void add_edge(graf *g, int src, int dest, int cost)
{
    node *new1 = new_node(cost, dest);
    node *new2 = new_node(cost, src);

    if (g->array_of_lists[src]->src == NULL)
    {
        g->array_of_lists[src]->src = new1;
        g->array_of_lists[src]->src->next = NULL;
    }
    else
    {
        new1->next = g->array_of_lists[src]->src;
        g->array_of_lists[src]->src = new1;
    }

    if (g->array_of_lists[dest]->src == NULL)
    {
        g->array_of_lists[dest]->src = new2;
        g->array_of_lists[dest]->src->next = NULL;
    }
    else
    {
        new2->next = g->array_of_lists[dest]->src;
        g->array_of_lists[dest]->src = new2;
    }
}

void dfs_util(graf *g, int *visited, int src)
{
    visited[src] = 1;
    node *temp = g->array_of_lists[src]->src;
    while (temp != NULL)
    {
        if (visited[temp->index] == 0)
            dfs_util(g, visited, temp->index);
        temp = temp->next;
    }
}

int conex(graf *g, int *visited)
{
    int count = 0;
    for (int i = 0; i < g->n; i++)
    {
        if (visited[i] == 0)
        {
            dfs_util(g, visited, i);
            count++;
        }
    }
    return count;
}
int main(int argc, char **argv)
{
    int cerinta;
    if (argc < 1)
    {
        exit(-1);
    }
    else
    {
        cerinta = atoi(argv[1]);
    }
    printf("%d", cerinta);
    FILE *fp = fopen("tema3.in", "r+");   // am deschiz fisierul de input
    FILE *fp2 = fopen("tema3.out", "w+"); // am deschis fisierul de output
    graf *g;
    int n, m;
    char *line = malloc(100 * sizeof(char));
    fscanf(fp, "%d%d \n", &n, &m);
    init_graf(&g, n, m);
    int cnt = 0;
    char **nodes = malloc(n * sizeof(char *));
    for (int i = 0; i < n; i++)
    {
        nodes[i] = malloc(100 * sizeof(char));
    }
    if (fp != NULL)
    {
        for (int i = 0; i < m; i++)
        {
            fgets(line, 100, fp);
            line[strlen(line) - 1] = '\0';
            char *x = strtok(line, " ");
            if (!check_node(cnt, x, nodes))
            {
                strcpy(nodes[cnt], x);
                cnt++;
            }
            char *y = strtok(NULL, " ");
            if (!check_node(cnt, y, nodes))
            {
                strcpy(nodes[cnt], y);
                cnt++;
            }
            char *c = strtok(NULL, " ");
            int cost = atoi(c);
            int src = get_index(n, x, nodes);
            int dest = get_index(n, y, nodes);
            add_edge(g, src, dest, cost);
        }
    }
    int *visited = calloc(n, sizeof(int));
    int cc = conex(g, visited);
    if (cerinta == 1)
        fprintf(fp2, "%d", cc);

    fclose(fp);
    free(visited);
    for (int i = 0; i < n; i++)
        free(nodes[i]);
    free(nodes);
    free(line);
    for (int i = 0; i < n; i++)
    {
        free(g->array_of_lists[i]);
    }
    free(g->array_of_lists);
    free(g);
    return 0;
}

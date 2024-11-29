#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int val;
    struct Node *next;
} Node;

typedef struct List
{
    struct Node *first;
    struct Node *last;
} List;

struct Node *new_node(int x)
{
    Node *new = malloc(sizeof(Node));
    new->val = x;
    return new;
}

void init_list(List **list)
{
    *list = (List *)malloc(sizeof(List));
    List *l = *list;
    l->first = NULL;
    l->last = NULL;
}

void print_list(List *list)
{
    Node *temp = list->first;
    while (temp != list->last)
    {
        printf("%d ", temp->val);
        temp = temp->next;
    }
    printf("%d ", temp->val);
}

void append(List *l, int x)
{
    Node *new = new_node(x);
    new->next = l->first;

    if (l->first == NULL)
    {
        l->first = new;
        l->last = new;
        l->first->next = l->last;
    }
    else
    {
        l->last->next = new;
        l->first = new;
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    List *list;
    init_list(&list);
    for (int i = 0; i < n; i++)
    {
        append(list, i);
    }
    print_list(list);
    return 0;
}

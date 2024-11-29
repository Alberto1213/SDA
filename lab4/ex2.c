#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int val;
    struct Node *next;
    struct Node *prev;
} Node;

typedef struct List
{
    struct Node *first;
} List;

struct Node *new_node(int x)
{
    Node *new = malloc(sizeof(Node));
    new->val = x;
}

void init_list(List **list)
{
    *list = (List *)malloc(sizeof(List));
    (*list)->first = malloc(sizeof(Node));
    (*list)->first = NULL;
}

void add(List *l, int x)
{
    Node *new = new_node(x);
    new->next = NULL;

    if (l->first == NULL)
    {
        l->first = new;
    }
    else
    {
        Node *temp = l->first;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = new;
        new->prev = temp;
    }
}

struct Node *delete (List *l, int x)
{
    Node *del;
    if (l->first->val == x)
    {
        del = l->first;
        l->first = l->first->next;
        l->first->prev = NULL;
    }
    Node *temp = l->first;
    while (temp->next != NULL)
    {
        if (temp->val == x)
        {
            del = temp;
            Node *aux = temp->prev;
            aux->next = temp->next;
            temp->next->prev = aux;
        }
        temp = temp->next;
    }
    if (temp->val == x)
    {
        del = temp;
        temp->prev->next = NULL;
    }
    return del;
}
void print_list(List *list)
{
    Node *temp = list->first;
    while (temp != NULL)
    {
        printf("%d ", temp->val);
        temp = temp->next;
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
        add(list, i);
    }
    Node *del = delete (list, 0);
    print_list(list);
    printf("\n%d", del->val);
    return 0;
}

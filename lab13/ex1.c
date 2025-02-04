#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int val;
    struct node *next;
}node;

typedef struct list
{
    struct node *first;
    struct node *last;
}list;

struct node* new_node(int x)
{
    node *new = malloc(sizeof(node));
    new->val = x;
    
    return new;
}
void init_list(list **l)
{
    (*l) = malloc(sizeof(list));
    (*l)->first = NULL;
    (*l)->last = NULL;
}

void add(list **l, int x)
{
    node *new = new_node(x);
    if((*l)->first == NULL)
    {
        (*l)->first = new;
        (*l)->first->next = (*l)->last;
        (*l)->last = (*l)->first;
    }
    else
    {
        new->next = (*l)->first;
        (*l)->last->next = new;
        (*l)->last = new;
    }
}

void find(list *l, int x)
{
    int cnt = 0;
    node *temp = l->first;
    while(temp != l->last)
    {
        if(temp->val == x)
            cnt++;
        temp = temp->next;
    }
    if(temp->val == x)
        cnt++;
    printf("%d", cnt);
}

int main()
{
    int x;
    scanf("%d", &x);
    list *l;
    init_list(&l);
    add(&l,4);
    add(&l,5);
    add(&l,6);
    add(&l,5);
    add(&l,6);
    add(&l,5);
    add(&l,6);
    add(&l,5);
    add(&l,6);
    find(l,6);
    return 0;
}
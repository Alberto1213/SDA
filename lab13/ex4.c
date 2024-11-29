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
}

void add(list **l, int x)
{
    node *new = new_node(x);
    if((*l)->first == NULL)
    {
        (*l)->first = new;
        (*l)->first->next = (*l)->first;
    }
    else
    {
        node *temp = (*l)->first;
        while(temp->next != (*l)->first)
            temp = temp->next;
        
        temp->next = new;
        new->next = (*l)->first;    
    }
}

/*void find(list *l, int x)
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
}*/

int main()
{
    int x;
    scanf("%d", &x);
    list *l;
    init_list(&l);
    add(&l,4);
    add(&l,5);
    add(&l,6);
    
    //find(l,6);
    printf("%d", l->first->next->next->next->val);
    return 0;
}
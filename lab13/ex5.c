#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int val;
    struct node *next;
}node;

typedef struct list
{
    struct node *santinela; 
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
    (*l)->santinela = malloc(sizeof(node));
    (*l)->santinela->next = (*l)->santinela;
}

void add(list **l, int x)
{
    node *new = new_node(x);
    if((*l)->santinela->next == NULL)
    {
        (*l)->santinela->next = new;
        new->next = (*l)->santinela;
    }
    else
    {
        node *temp = (*l)->santinela->next;
        while(temp->next != (*l)->santinela)
            temp = temp->next;

        temp->next = new;
        new->next = (*l)->santinela;     
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
    printf("%d", l->santinela->next->next->next->next->next->val);
    return 0;
}
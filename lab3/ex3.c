#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int val;
    struct Node *next;
}Node;

void init(Node **l)
{
    *l= (Node *) malloc(sizeof(Node));
    *l = NULL;
}

void print(Node *l)
{
    Node *temp = l;
    while(temp != NULL)
    {
        printf("%d ", temp->val);
        temp = temp -> next;
    }
}

void append(Node **l, int x)
{
    Node *new_node = malloc(sizeof(Node));
    new_node -> val = x;

    if(*l == NULL)
    {
        *l = new_node;
        new_node->next == NULL;    
    }
    else
    {
        new_node -> next = *l;
        *l = new_node;
    }
}

void f3(Node *list)
{
    Node *temp1 = list;
    Node *temp2 = list;

    while(temp1->next != NULL && temp1->next->next != NULL)
    {
        temp1 = temp1->next->next;
        temp2 = temp2->next;
    }
    printf("%d", temp2->val);
}
int main()
{
    Node *list;
    init(&list);

    append(&list,9);
    append(&list,8);
    append(&list,7);
    append(&list,6);
    append(&list,5);
    append(&list,4);
    append(&list,3);
    append(&list,2);
    append(&list,1);

    f3(list);
}


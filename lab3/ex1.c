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
void f1(Node *list)
{
    Node *temp = list;
    int idx = 1;
    while(temp->next != NULL)
    {
        if(temp->val % 2 == temp->next->val % 2)
        {
            printf("(%d, %d", idx, idx+1);
            printf("): %d %d", temp->val, temp->next->val);
            printf("\n");
        }
        idx++;
        temp = temp -> next;
    }
}
int main()
{
   Node *list;
   init(&list);
   append(&list,14);
   append(&list,6);
   append(&list,9);
   append(&list,20);
   append(&list,10);
   append(&list,2);
   append(&list,7);
   append(&list,6);
   append(&list,4);
   print(list);
   printf("\n");
   f1(list);
   return 0;
}
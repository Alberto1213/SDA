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

void f2(Node *l)
{
    int start_idx = 1;
    int end_idx = 1;
    Node *temp = l;

    while(temp != NULL) 
    {
        if(temp->next != NULL)
        {
            if(temp->next->val > temp->val)
            {
                end_idx++;
            }
            else
            {
                if(end_idx - start_idx >= 1)
                    {
                        printf("%d %d", start_idx, end_idx);
                        printf("\n");
                    }
                start_idx = end_idx + 1;    
                end_idx++;
            }
            temp = temp->next;
        }
        else
        {
            if(end_idx - start_idx >= 1)
                {
                    printf("%d %d", start_idx, end_idx);
                    printf("\n");
                }
            break;
        } 
    }
}
int main()
{
    Node *list;
    init(&list);
    append(&list,2);
    append(&list,1);
    append(&list,7);
    append(&list,6);
    append(&list,5);
    append(&list,1);
    append(&list,8);
    append(&list,7);
    append(&list,4);
    append(&list,1);
    append(&list,2);
    append(&list,1);
    append(&list,1);
    append(&list,2);
    append(&list,3);
    append(&list,3);
    append(&list,2);
    append(&list,1);
    print(list);
    printf("\n");
    f2(list);
    return 0;
}
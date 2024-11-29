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
void f3(List *list)
{
    Node *temp = list->first;
    if(temp->next->next == NULL)
    {
        if(temp == NULL)
            return;

        if(temp->val % 2 == temp->next->val % 2)
        {
            int med = (temp->val + temp->next->val)/2;
            Node *new = new_node(med);
            new->prev = temp;
            new->next = temp->next;
            temp->next->prev = new;
            temp->next = new;
        }
    }
    else
    {
         while(temp->next!= NULL)
        {
            if(temp->val % 2 == temp->next->val % 2)
            {
                int med = (temp->val + temp->next->val)/2;
                Node *new = new_node(med);
                new->prev = temp;
                new->next = temp->next;
                temp->next->prev = new;
                temp->next = new;
            }
            temp = temp->next;
        }
    }

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
    List *list2;
    init_list(&list2);
    add(list2,2);
    add(list2,4);
    add(list2,6);
    add(list2,3);
    add(list2,1);
    add(list2,2);
    printf("\n");
    f3(list2);
    print_list(list2);
    return 0;
}
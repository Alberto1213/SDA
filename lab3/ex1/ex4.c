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

void add(Node **l, int x)
{
    Node *new_node = malloc(sizeof(Node));
    new_node -> val = x;
    new_node -> next = NULL;

    if(*l == NULL)
    {
        *l = new_node;
    }
    else
    {
        Node *temp = *l;
        while(temp ->next != NULL)
        {
            temp = temp -> next;
        }
        temp ->next = new_node;
        
    }
}

Node* f3(Node **list, int k)
{
    Node *new_list;
    init(&new_list);

    if((*list)->val % k == 0)
    {
        append(&new_list,(*list)->val);
        *list = (*list)->next;
    }

    Node *temp_prec = *list;
    Node *temp_curr = temp_prec->next;
    while(temp_curr != NULL)
    {
        if(temp_curr->val % k == 0)
        {
            Node *new_node = malloc(sizeof(Node));
            new_node->val = temp_curr->val;

            if(new_list == NULL)
            {
                new_list = new_node;
                new_list->next = NULL;
            }

            else
            {
                
                if(new_list->next == NULL)
                    {
                        if(new_node->val > new_list->val)
                            add(&new_list,new_node->val);
                        else append(&new_list,new_node->val);
                    }
                else 
                {
                    if(new_node->val <= new_list->val)
                        append(&new_list,new_node->val);
                    else 
                    {    
                        Node *temp2 = new_list;
                        while(temp2->next != NULL)
                            {
                                if(temp2->next->val > new_node->val)
                                {
                                    new_node->next = temp2->next;
                                    temp2->next = new_node;
                                    break;
                                }
                                temp2 = temp2->next;
                            }
                        if(temp2->next == NULL)
                        {
                            temp2->next = new_node;
                            new_node->next = NULL;
                        }
                    }
                }
            }
            Node *aux = temp_curr->next;
            temp_prec->next = aux;
        }
        if(temp_curr->val % k == 0 )    
            {  
                temp_curr = temp_prec->next;
            }
        else
            {
                temp_prec = temp_prec->next;
                temp_curr = temp_curr->next;
            }
    }
    return new_list;
}
int main()
{
    int k;
    Node *list;
    init(&list);
    add(&list, 100);
    add(&list, 3);
    add(&list, 10);
    add(&list, 5);
    add(&list, 7);
    add(&list, 8);
    add(&list, 15);
    add(&list, 13);
    add(&list, 20);
    add(&list, 10);
    add(&list, 30);
    add(&list, 0);
    add(&list, 8);
    print(list);
    printf("\n");
    print(f3(&list,5));
    printf("\n");
    print(list);
    return 0;
}
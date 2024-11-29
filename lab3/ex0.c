#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int val;
    struct Node *next;
} Node;

void init(Node **l)
{
    //*l = (Node *)malloc(sizeof(Node)); //l-ul nu va fi niciodata null asa, deoarece are mem alocata, pentru cazu asta atri, trebuie initialozara din main valoarea capului.
    *l = NULL;
}

void print(Node *l)
{
    Node *temp = l;
    while (temp != NULL)
    {
        printf("%d ", temp->val);
        temp = temp->next;
    }
}

void append(Node **l, int x)
{
    Node *new_node = malloc(sizeof(Node));
    new_node->val = x;
    new_node->next == NULL;

    if (*l == NULL)
    {
        *l = new_node;
    }
    else
    {
        new_node->next = *l;
        *l = new_node;
    }
}

void add(Node **l, int x)
{
    Node *new_node = malloc(sizeof(Node));
    new_node->val = x;
    new_node->next = NULL;

    if (*l == NULL)
    {
        *l = new_node;
    }
    else
    {
        Node *temp = *l;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}
void delete_first(Node **l)
{
    if (*l == NULL)
    {
        return;
    }
    else
    {
        *l = (*l)->next;
    }
}

void delete_given_value(Node **l, int x)
{
    if (*l == NULL)
    {
        return;
    }
    else
    {
        Node *temp = *l;
        if (temp->val == x)
        {
            *l = (*l)->next;
        }
        else
        {
            while (temp != NULL)
            {
                if (temp->next->val == x)
                {
                    Node *temp2 = temp->next->next;
                    temp->next = temp2;
                    break;
                }
                temp = temp->next;
            }
        }
    }
}
Node *reverse_list(Node *l)
{
    Node *temp = l;
    Node *rev_l;
    init(&rev_l);
    while (temp != NULL)
    {
        append(&rev_l, temp->val);
        temp = temp->next;
    }
    return rev_l;
}
int main()
{
    int n;
    scanf("%d", &n);
    Node *list01, *list02;
    init(&list01);
    init(&list02);
    for (int i = 0; i < n; i++)
    {
        add(&list01, 2 * i);
    }
    print(list01);
    delete_first(&list01);
    //delete_given_value(&list01, 8); //n >= 5
    printf("\n");
    print(reverse_list(list01));
    printf("\n");
    print(list01);
    printf("\n");
    printf("-------------------------------");
    printf("\n");
    for (int i = 0; i < n; i++)
    {
        append(&list02, i);
    }
    print(list02);
    delete_first(&list02);
    delete_given_value(&list02, 8);
    printf("\n");
    print(reverse_list(list02));
    printf("\n");
    print(list02);
    return 0;
}

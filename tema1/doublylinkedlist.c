#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

typedef struct node
{
    char c;
    int idx;
    struct node *next;
    struct node *prev;
} node;

typedef struct List
{
    struct node *santinela;
    struct node *current;
} List;

struct node *new_node(char c)
{
    node *new = malloc(sizeof(node));
    new->c = c;
    return new;
}

void init_list(List **list)
{
    *list = (List *)malloc(sizeof(List));
    List *l = *list;
    l->santinela = (node *)malloc(sizeof(node));
    l->santinela->prev = NULL;
    l->current = new_node('#');
    l->current->idx = 1;
    l->current->prev = l->santinela;
    l->current->next = NULL;
    l->santinela->next = l->current;
}

void move_left(List *l, Stack *Undo)
{
    if (l->current->prev != l->santinela)
    {
        push(Undo,l->current->idx);
        l->current = l->current->prev;
    }
    else
    {
        return;
    }
}

void move_right(List *l, Stack *Undo)
{
    push(Undo,l->current->idx);
    if (l->current->next != NULL)
        l->current = l->current->next;
    else
    {
        node *new = new_node('#');
        new->idx = l->current->idx + 1;
        l->current->next = new;
        new->prev = l->current;
        new->next = NULL;
        l->current = l->current->next;
    }
}

void write(List *l, char c)
{
    l->current->c = c;
}

void move_left_char(List *l, char c)
{
    node *temp = l->current;
    while (temp != l->santinela)
    {
        if (temp->c == c)
        {
            l->current = temp;
            break;
        }
        else
            temp = temp->prev;
    }
    if (temp == l->santinela)
    {
        printf("ERROR\n");
    }
}

void move_right_char(List *l, char c)
{
    node *temp = l->current;
    while (temp->next != NULL)
    {
        if (temp->c == c)
        {
            l->current = temp;
            break;
        }
        else
            temp = temp->next;
    }
    if (temp->next == NULL)
    {
        if (temp->c != c)
        {
            node *new = new_node('#');
            new->idx = temp->idx + 1;
            temp->next = new;
            new->prev = temp;
            new->next = NULL;
            l->current = new;
        }
        else
        {
            l->current = temp;
        }
    }
}

void insert_left(List *l, char c)
{
    if (l->current->prev != l->santinela)
    {
        node *new = new_node(c);
        new->idx = l->current->idx;

        l->current->prev->next = new;
        new->prev = l->current->prev;
        l->current->prev = new;
        new->next = l->current;
        l->current = l->current->prev;

        node *temp = l->current->next;
        while (temp != NULL)
        {
            temp->idx++;
            temp = temp->next;
        }
    }
    else
    {
        printf("ERROR\n");
    }
}
void insert_right(List *l, char c)
{
    node *new = new_node(c);
    new->idx = l->current->idx + 1;

    if (l->current->next != NULL)
    {
        l->current->next->prev = new;
        new->next = l->current->next;
        l->current->next = new;
        new->prev = l->current;

        l->current = l->current->next;
        node *temp = l->current->next;
        while (temp != NULL)
        {
            temp->idx++;
            temp = temp->next;
        }
    }
    else
    {
        l->current->next = new;
        new->prev = l->current;
        new->next = NULL;
        l->current = l->current->next;
    }
}
void show(List *list)
{
    node *temp = list->santinela->next;
    while (temp != NULL)
    {
        if (temp == list->current)
        {
            printf("|%c|", temp->c);
        }
        else
        {
            printf("%c", temp->c);
        }
        temp = temp->next;
    }
    printf("\n");
}

void show_current(List *l)
{
    printf("%c\n", l->current->c);
}
void undo(List *l,Stack *Undo,Stack *Redo)
{
    push(Redo,l->current->idx);
    if(Undo->top->val > l->current->idx)
    {   
        while(Undo->top->val > l->current->idx)
            l->current = l->current->next;
    }
    else
    {
        while(Undo->top->val < l->current->idx)
            l->current = l->current->prev;
    }        
    pop(Undo);
}

void redo(List *l, Stack *Undo, Stack *Redo)
{
    push(Undo,l->current->idx);
    if(Redo->top->val > l->current->idx)
    {   
        while(Redo->top->val > l->current->idx)
            l->current = l->current->next;
    }
    else
    {
        while(Redo->top->val < l->current->idx)
            l->current = l->current->prev;
    }   
    //push(Undo,l->current->idx);  
    pop(Redo);
}
int main()
{
    List *l;
    init_list(&l);
    Stack *Undo;
    init_stack(&Undo);
    Stack *Redo;
    init_stack(&Redo);

    /*printf("---------------Testul1---------------\n");
    write(l,'x');
    show(l);ok*/
    /*printf("---------------Testul2---------------\n");
    move_right(l);
    write(l, 'x');
    show(l);ok*/
    /*printf("---------------Testul3---------------\n");
    insert_right(l,'x');
    show_current(l);
    show(l);ok*/
    /*printf("---------------Testul4---------------\n");
    insert_left(l,'x');
    show(l);ok*/
    /*printf("---------------Testul5---------------\n");
    move_right(l);
    write(l,'x');
    move_right(l);
    write(l,'y');
    move_right(l);
    write(l,'z');
    move_left_char(l,'x');
    show(l);ok*/
    /*printf("---------------Testul6---------------\n");
    move_right_char(l,'x');
    show(l);*/
    /*printf("---------------Testul7---------------\n");
    write(l,'x');
    move_right(l);
    move_left_char(l,'y');
    show(l);ok*/
    printf("---------------Testul8---------------\n");
    move_right(l,Undo);
    write(l, 'x');
    move_right(l,Undo);
    write(l, 'y');
    move_left(l,Undo);
    move_right(l,Undo);
    show(l);
    undo(l,Undo,Redo);
    show(l);
    undo(l,Undo,Redo);
    show(l);
    redo(l,Undo,Redo);
    show(l);
    return 0;
}
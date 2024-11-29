/*RADU ALBERTO MIHAI 331CC*/
// In acest header am implementat operatiile cerute in tema prin functiile de mai jos
// Am folosit headerul "stack.h" pentru undo/redo

#include "stack.h"

typedef struct node // am definit o structura de nod pentru lista dubla inlantuita
{
    char c;
    int idx; // am folosit un camp in care se retine indexul nodului curent, camp folosit pentru operatiile de undo/redo
    struct node *next;
    struct node *prev;
} node;

typedef struct List // am definit o structura de lista dubla inlantuita cu santinela, cu doua campuri, unul care retine nodul curent si altul care retina santinela listei
{
    struct node *santinela;
    struct node *current;
} List;

struct node *new_node(char c) // functie care creaza un nou nod ce retine caracterul dat ca parametru
{
    node *new = malloc(sizeof(node));
    new->c = c;
    return new;
}

void init_list(List **list) // functie care initializeaza o lista dublu inlantuita cu santinela, respectiv campurile ei si primul nod din lista cu caracterul '#'
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

void move_left(List *l, Stack *Undo) // functia care muta nodul curent la stanga cu o pozitie
{
    if (l->current->prev != l->santinela)
    {
        push(Undo, l->current->idx); // am adaugat indexul nodului curent in stiva pentru operatia undo
        l->current = l->current->prev;
    }
    else
    {
        return; // daca nodul curent este primul nod al listei, nu se intampla nimic
    }
}

void move_right(List *l, Stack *Undo) // functia care muta nodul curent la dreapta cu o pozitie
{
    push(Undo, l->current->idx); // am adaugat indexul nodului curent in stiva pentru operatia undo
    if (l->current->next != NULL)
        l->current = l->current->next;
    else // daca nodul curent este ultimul nod al liste care este neNULL, se adauga un nou nod la dreapta
    {
        node *new = new_node('#');
        new->idx = l->current->idx + 1;
        l->current->next = new;
        new->prev = l->current;
        new->next = NULL;
        l->current = l->current->next;
    }
}

void write(List *l, char c) // functia care modifica caracterul nodului curent
{
    l->current->c = c;
}

void move_left_char(List *l, char c, FILE *fp)
{
    // functia care muca nodul curent la stanga pana se gaseste un caracter dat ca parametru
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
    // daca se ajunga la santinela, se va afisa "ERROR"
    if (temp == l->santinela)
    {
        fprintf(fp, "ERROR\n");
    }
}

void move_right_char(List *l, char c)
{
    // functia care muca nodul curent la stanga pana se gaseste un caracter dat ca parametru
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
    // daca se ajunge la cel mai din dreapta nod, se va creea un nou nod la dreapta acestuia
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

void insert_left(List *l, char c, FILE *fp)
{
    // functia care insereaza un nou nod la stanga celui curent
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
    // daca nodul curent este primul nod al listei, nu se poate insera, deci se afiseaza"ERROR"
    else
    {
        fprintf(fp, "ERROR\n");
    }
}
void insert_right(List *l, char c)
{
    // functia care insereaza un nou nod la dreapta celui curent
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
    // daca nodul curent este cel mai din dreapta, adaugam un nou nod creat la dreapta acestuia
    else
    {
        l->current->next = new;
        new->prev = l->current;
        new->next = NULL;
        l->current = l->current->next;
    }
}
void show(List *list, FILE *fp)
{
    // functia care printeza lista noastea
    node *temp = list->santinela->next;
    while (temp != NULL)
    {
        if (temp == list->current)
        {
            fprintf(fp, "|%c|", temp->c); // se evidentiaza nodul curent
        }
        else
        {
            fprintf(fp, "%c", temp->c);
        }
        temp = temp->next;
    }
    fprintf(fp, "\n");
}

void show_current(List *l, FILE *fp)
{
    // functia care printeaza nodul curent
    fprintf(fp, "%c\n", l->current->c);
}

void undo(List *l, Stack *Undo, Stack *Redo)
{
    // functia care realizeaza operatia de undo
    push(Redo, l->current->idx); // se retine in stiva de redo pozitia curenta a nodului
    // se cauta pozitia anterioara ca nodului in functie de idexulul retinut in stiva undo
    if (Undo->top->val > l->current->idx)
    {
        while (Undo->top->val > l->current->idx)
            l->current = l->current->next;
    }
    else
    {
        while (Undo->top->val < l->current->idx)
            l->current = l->current->prev;
    }
    pop(Undo); // se elimina varful stivei de undo dupa ce am realizat operatia
}

void redo(List *l, Stack *Undo, Stack *Redo)
{
    // functia care realizeaza operatia de redo
    push(Undo, l->current->idx); // se retine in stiva de undo pozitia curenta a nodului
    // se cauta pozitia anterioara ca nodului in functie de idexulul retinut in stiva redo
    if (Redo->top->val > l->current->idx)
    {
        while (Redo->top->val > l->current->idx)
            l->current = l->current->next;
    }
    else
    {
        while (Redo->top->val < l->current->idx)
            l->current = l->current->prev;
    }
    pop(Redo); // se elimina varful stivei de redo dupa ce am realizat operatia
}

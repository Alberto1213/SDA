#include <stdio.h>
#include <stdlib.h>

typedef struct snode
{
    int val;
    struct snode *link;
} snode;

typedef struct Stack
{
    struct snode *top;
} Stack;

struct snode *new_node_stack(int val)
{
    snode *new = malloc(sizeof(snode));
    new->val = val;
    new->link = NULL;

    return new;
}

void init_stack(Stack **s)
{
    *s = malloc(sizeof(Stack));
    (*s)->top = malloc(sizeof(snode));
    (*s)->top = NULL;
}

int isEmpty(Stack *s)
{
    return s->top == NULL;
}

void push(Stack *s, int val)
{
    snode *new = new_node_stack(val);
    if (s->top == NULL)               
    {
        s->top = new;
    }
    else
    {
        new->link = s->top;
        s->top = new;
    }
}

void pop(Stack *s)
{
    if (s->top == NULL)
    {
        return;
    }
    else
    {
        snode *temp = s->top;
        s->top = s->top->link;
        free(temp);
    }
}

int top(Stack *s)
{
    if (s->top != NULL)
        return s->top->val;

    else
        exit(1);
}

int main()
{
    Stack *s;
    init_stack(&s);
    printf("%d\n", isEmpty(s));
    push(s,4);
    push(s,4);
    push(s,5);
    printf("%d\n", top(s));
    pop(s);
    printf("%d", top(s));

}

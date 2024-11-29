#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct snode
{
    char val;
    struct snode *link;
} snode;

typedef struct Stack
{
    struct snode *top;
} Stack;

struct snode *new_node_stack(char val)
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
    if(s->top == NULL)
        return 1;
    else return 0;    
}

void push(Stack *s, char val)
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

char top(Stack *s)
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
    char *str = malloc(30*sizeof(char));
    fgets(str,30,stdin);
    int ok = 1;
    int len = strlen(str);
    for(int i = 0; i < len - 1; i++)
    {
        if(str[i] == '[' || str[i] == '(' || str[i] == '{')
            push(s,str[i]);
        else
        {
            if(isEmpty(s) == 0)
                {
                    if((str[i] == '}' & top(s) != '{' ) || (str[i] == ']' & top(s) != '[') || (str[i] == ')' & top(s) != '(' ))
                    {
                        ok = 0;
                        break;
                    }
                    else
                    {
                        pop(s);
                    }
                }
            else 
            {
                ok = 0;
                break;
            }    
        }    
    }

    if(ok == 1)
    {
        printf("Parantezele sunt ok");
    }
    else
    {
        printf("Parantezele nu sunt ok");
    }
    printf("%c", str[0]);
    return 0;
}

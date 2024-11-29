/*RADU ALBERTO MIHAI 331CC*/
// In acest header am implementat functionalitatile specifice stivei

// am definit un nod pentru stiva
typedef struct snode
{
    int val;
    struct snode *link;
} snode;

// am definit o structura de stiva
typedef struct Stack
{
    struct snode *top;
} Stack;

// functie care creeaza un nou nod pentru stiva
struct snode *new_node_stack(int val)
{
    snode *new = malloc(sizeof(snode));
    new->val = val;
    new->link = NULL;

    return new;
}

// functie care initializeaza stiva
void init_stack(Stack **s)
{
    *s = malloc(sizeof(Stack));
    (*s)->top = malloc(sizeof(snode));
    (*s)->top = NULL;
}

// functia care adauga un nou nod in varful stivei, nod care are o valoare data ca parametru
void push(Stack *s, int val)
{
    snode *new = new_node_stack(val); // cream un nou nod care va contine valoarea data ca parametru
    if (s->top == NULL)               // adaugam nodul in varful stivei
    {
        s->top = new;
    }
    else
    {
        new->link = s->top;
        s->top = new;
    }
}

// functie care elimina varful stivei
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

// functie care returneaza valoarea retinuta in varful stivei
int peek(Stack *s)
{
    if (s->top != NULL)
        return s->top->val;

    else
        exit(1);
}

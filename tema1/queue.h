/*RADU ALBERTO MIHAI 331CC*/
// In acest header am implementat functionalitatile necesare pentru coada

// am definit o structura pentru nodul unei cozei
typedef struct qnode
{
    char *command;
    struct qnode *next;
} qnode;

// am definit o structura pentru o coada
typedef struct Queue
{
    struct qnode *front;
    struct qnode *rear;
} Queue;

// am implementat functia de initializare a unei cozi
void init_queue(Queue **q)
{
    *q = malloc(sizeof(Queue));
    (*q)->front = malloc(sizeof(qnode));
    (*q)->rear = malloc(sizeof(qnode));
    (*q)->front = NULL;
    (*q)->rear = NULL;
}

// am implementat o functie care creeaza un nod pentru coada noastra
struct qnode *new_qnode(char *s)
{
    qnode *temp = malloc(sizeof(qnode));       // alocam memorie pentru nodul nostru
    temp->command = malloc(30 * sizeof(char)); // alocam memorie pentru campul char* al nodului nostru
    strcpy(temp->command, s);                  // copiem stringul dat ca parametru in campul char* al nodului nostru
    temp->next = NULL;
    return temp;
}

// functie care adauga un nou nod, ce contine un string dat ca parametru, la finalul cozii
void enqueue(Queue *q, char *s)
{
    qnode *temp = new_qnode(s);              // cream nou nod
    if (q->rear == NULL && q->front == NULL) // daca coada e goala, adaugam noul nod in nodurile ce pointeaza catre inceputul si sfarsitul cozii
    {
        q->front = temp;
        q->rear = temp;
        return;
    }
    else // altfel adaugam nodul la finalul cozii
    {
        q->rear->next = temp;
        q->rear = q->rear->next;
    }
}

// functie ce elimina primul element din coada
void dequeue(Queue *q)
{
    if (q->front == NULL)
    {
        return;
    }
    else
    {
        qnode *temp = q->front;
        q->front = q->front->next;
        free(temp);
    }
}

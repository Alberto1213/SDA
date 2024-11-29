/*RADU ALBERTO MIHAI 331CC*/
// In acest fisier am citit comenzile date in fisierul .in, am retinut comezile de tip UPDATE intr o structura de coada si am realizat operatile date
// Am folosit headerele "doublylinkedlist.h" si "queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "doublylinkedlist.h"
#include "queue.h"

int main()
{
    // am declarat cele doua stive Undo/Redo pentru operatiile undo/redo, o coada pentru comenzile de tip UPDATE si o lista pentru continul benzii, le-am initializat pe toate
    Queue *q;
    init_queue(&q);
    List *l;
    init_list(&l);
    Stack *Undo;
    init_stack(&Undo);
    Stack *Redo;
    init_stack(&Redo);

    FILE *fp = fopen("tema1.in", "r+");   // am deschiz fisierul de input
    FILE *fp2 = fopen("tema1.out", "w+"); // am deschis fisierul de output
    int n;
    char *line = malloc(30 * sizeof(char));
    if (fp != NULL)
    {
        fscanf(fp, "%d \n", &n);
        while (fgets(line, 30, fp) != NULL)
        {
            if ((strcmp(line, "EXECUTE\n") != 0) && (strcmp(line, "REDO\n") != 0) && (strcmp(line, "UNDO\n") != 0) && (strcmp(line, "SHOW\n") != 0) && (strcmp(line, "SHOW_CURRENT\n") != 0))
            {
                // daca comanda data e una de tip UPDATE, scoate '\n' de la final si adaugam comanda in coada
                if (q->front == NULL)
                    init_queue(&q);

                line[strlen(line) - 1] = '\0';
                enqueue(q, line);
            }

            if (strcmp(line, "EXECUTE\n") == 0)
            {
                // daca comanda e una de tip EXECUTE, incepem sa aplicam comenzi de tip UPDATE retinute in coada
                // in continuare se verifica ce comanda este in varful cozii, si se extrage caracterul dat ca parametru pentru comenzile care au nevoie
                if (strstr(q->front->command, "WRITE") != NULL)
                {
                    int len = strlen(q->front->command) - 1;
                    char c = q->front->command[len];
                    write(l, c);
                }

                if (strstr(q->front->command, "INSERT_LEFT") != NULL)
                {
                    int len = strlen(q->front->command) - 1;
                    char c = q->front->command[len];
                    insert_left(l, c, fp2);
                }

                if (strstr(q->front->command, "INSERT_RIGHT") != NULL)
                {
                    int len = strlen(q->front->command) - 1;
                    char c = q->front->command[len];
                    insert_right(l, c);
                }

                if (strstr(q->front->command, "MOVE_LEFT_CHAR") != NULL)
                {
                    int len = strlen(q->front->command) - 1;
                    char c = q->front->command[len];
                    move_left_char(l, c, fp2);
                }

                if (strstr(q->front->command, "MOVE_RIGHT_CHAR") != NULL)
                {
                    int len = strlen(q->front->command) - 1;
                    char c = q->front->command[len];
                    move_right_char(l, c);
                }

                if (strcmp(q->front->command, "MOVE_LEFT") == 0)
                {
                    move_left(l, Undo);
                }

                if (strcmp(q->front->command, "MOVE_RIGHT") == 0)
                {
                    move_right(l, Undo);
                }
                dequeue(q); // dupa ce am realizat operatia de tip UPDATE din varful cozii, o eliminam
            }
            else
            {
                // daca comanda e "SHOW", afisam lista
                if (strcmp(line, "SHOW\n") == 0)
                {
                    show(l, fp2);
                }
                // daca comanda e "SHOW_CURRENT" afisam nodul curent
                if (strcmp(line, "SHOW_CURRENT\n") == 0)
                {
                    show_current(l, fp2);
                }
                // daca comanda e "UNDO", aplicam operatia de undo pe lista
                if (strcmp(line, "UNDO\n") == 0)
                {
                    undo(l, Undo, Redo);
                }
                // daca comanda e "REDO", aplicam comanda de REDO pe lista
                if (strcmp(line, "REDO\n") == 0)
                {
                    redo(l, Undo, Redo);
                }
            }
        }
    }
    fclose(fp);
    free(q);
    return 0;
}

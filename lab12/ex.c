#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define DIM 10

typedef struct Student
{
    char *nume;
    int nr_matricol;
    float medie;
}Student;

typedef struct table_node
{
    Student val;
    char *key;
    struct table_node *next; 
}table_node;

typedef struct HashTable
{
    int dim;
    struct table_node **array;
}HashTable;

Student new_student(char *name, int nr_matricol, float medie)
{
    Student new;
    new.nume = malloc(strlen(name) * sizeof(char));
    strcpy(new.nume,name);
    new.medie = medie;
    new.nr_matricol = nr_matricol;
    return new;
}
char* hash_function(Student s)
{
    int len = strlen(s.nume) - 1;
    char *res = malloc(len * sizeof(char));
    for(int i = len; i >= 0; i--)
        res[len - i] = s.nume[i];

    return res;    
}

void init_table(HashTable **table, int dim)
{
    *table = malloc(sizeof(HashTable));
    (*table)->dim = dim;
    (*table)->array = malloc(dim * sizeof(table_node*));
    for(int i = 0; i < dim; i++)
        (*table)->array[i] = NULL;  
}

table_node *search(HashTable *table, Student s)
{
	char *k = hash_function(s);
	table_node *one;
	one = table->array[strlen(k) - 1];
	if (one == NULL)
        return NULL;
    while (one != NULL)
    {
        if (strcmp(one->key, s.nume) == 0)
            return one;
        one = one->next;
    }
    return NULL;
}

void insert (HashTable **table, Student s)
{
	table_node *a = search((*table), s);
    table_node *b;
	char *i;
    if (a != NULL)
        strcpy(a->key,s.nume);
    else
    {
        b = (table_node *) malloc (sizeof(table_node));
        b->val.medie = s.medie;
        b->val.nr_matricol = s.nr_matricol;
        strcpy(b->key,s.nume);
        i = hash_function(s);
        b->next = (*table)->array[strlen(i) - 1];
        (*table)->array[strlen(i) - 1] = b;
    }

}

char* get_key (HashTable *table, Student s)
{
	table_node *found = search(table,s);
	if (found == NULL)
		return " ";
	else
		return found->key;
}

void print_hash (HashTable *table)
{
	table_node *one;
    for (int i = 0; i < table->dim; i++)
    {
        one = table->array[i];
        while (one != NULL)
        {
            printf("Element \"%d %f %s\" with key %s\n", one->val.nr_matricol, one->val.medie, one->val.nume, one->key);
            one = one->next;
        }
    }
}
int main()
{
    HashTable *table;
    init_table(&table,DIM);
    Student s = new_student("Andrei", 10, 10.0);
    insert(&table,s);
    insert(&table,new_student("Mihai",1,5.87));
    print_hash(table);
    printf("%s", hash_function(s));
    return 0;
}

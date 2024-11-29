#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b)
{
    int aux = *a;
    *a = *b;
    *b = aux;
}

int pozitionare1(int *v,int st, int dr)
{
    int m = (st+dr)/2;
    int pivot = v[m];
    int poz = st;

    for(int i = st; i <= dr; i++)
    {
        if(v[i] < pivot) // luam doar elementele mai mici decat pivotul
            {
                swap(&v[i],&v[poz]); //le pozitionam inaintea pivotului
                poz++; // crestem pozitia
            }
    }
    int sol = poz; // dupa terminarea primei bucle poz va fi pozitia pivotului datorita ultimei incrementari
    for(int i = st;i <= dr; i++)
    {
        if(v[i] == pivot) //luam elementele egale cu pivotul si le asezam
            {
                swap(&v[i],&v[poz]);
                poz++;
            }
    }
    //swap(&v[poz], &v[m]); merge doar pt m = high, daca nu pun si pivotii la locul lor
    return sol; //returna prima pozitie a pivotului, se poate returna si ultima(poz-1) 
}

int pozitionare2(int *v,int st, int dr)
{
    int m = (st+dr)/2;
    int pivot = v[m];
    int poz = st - 1;

    for(int i = st; i <= dr; i++)
    {
        if(v[i] < pivot) // luam doar elementele mai mici decat pivotul
            {
            	poz++; // crestem pozitia
             	swap(&v[i],&v[poz]); //le pozitionam inaintea pivotului   
            }
    }
    int sol = poz + 1; // dupa terminarea primei bucle poz+1 va fi pozitia pivotului
    for(int i = st;i <= dr; i++)
    {
        if(v[i] == pivot) //luam elementele egale cu pivotul si le asezam
            {
               poz++;
               swap(&v[i],&v[poz]);
                
            }
    }
    //swap(&v[sol], &v[m]); //nu merge daca m nu e high si elem egale cu piv nu sunt la locul lor
    return sol; //returna prima pozitie a pivotului, se poate returna si ultima(poz) 
}

int cautare(int *v, int st, int dr, int k)
{
    int poz = pozitionare1(v,st,dr);
    if(k == poz)
        return v[k];
    else 
    {
        if(poz < k)
            return cautare(v,poz + 1,dr,k);
        if(poz > k)
            return cautare(v,st,poz - 1,k);    
    }   
}
void quicksort1(int *v, int l, int r)
{
	if(l < r)
	{
		int position = pozitionare1(v, l, r);
		quicksort1(v, l, position - 1);
		quicksort1(v, position + 1, r);
	}
}

void quicksort2(int *v, int l, int r)
{
	if(l < r)
	{
		int position = pozitionare2(v, l, r);
		quicksort2(v, l, position - 1);
		quicksort2(v, position + 1, r);
	}
}
int main()
{
    int n;
    scanf("%d", &n);
    int k;
    scanf("%d", &k);
    int *v = malloc((n+1)*sizeof(int));
    for(int i = 1; i <= n; i++)
        scanf("%d", &v[i]);
    int element = cautare(v,1,n,n-k+1);
    printf("%d\n", element);
    quicksort2(v, 1, n);
    for(int i = 1; i <= n; i++)
        printf("%d ", v[i]);
    return 0;    
}

#include <stdio.h>
#include <stdlib.h>

int f1_aux(int *v, int n)
{
    if(n == 0)
        {
            if(v[n]%2 == 0)
                return v[n];
            else return 0;    
        }

    else
        {
            if(v[n]%2==0)
                return v[n]+f1_aux(v,n-1);
            else return f1_aux(v,n-1);    
        }    
}
int f1(int *v)
{
    int size = sizeof(v)/sizeof(int);  
    return f1_aux(v,size);
}
int main()
{
    int n;
    int *v = malloc(sizeof(int));
    scanf("%d", &n);

    for(int i = 0; i < n; i++)
    {
        v[i] = 2*i;
        printf("%d ", v[i]);
    }
    printf("%s", "\n");
    printf("%d ", f1(v));
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

int sum(int *v,int l, int r)
{
    int s = 0;
    if(l == r )
        return v[l];
    if(l > r)
        return 0;    
    else
    {
        int m = (l+r)/2;
        s += sum(v,l,m - 1) + sum(v,m + 1,r) + v[m];
    }    

    return s;
}

int main()
{
    int n;
    scanf("%d", &n);
    int *v = malloc(n*sizeof(int));
    for(int i = 0; i < n; i++)
        scanf("%d", &v[i]);

    int suma = sum(v,0,n-1);
    printf("%d", suma);    
}
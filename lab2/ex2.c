#include <stdio.h>
#include <stdlib.h>

int binarysearch(int *v,int l,int r,int x)
{
    if (r >= l)
    {
        int m = (l+r)/2;
        if(v[m] == x)
            return 1;
        else
        {
            if(v[m] > x)
                return binarysearch(v, l, m - 1, x);
            if(v[m] < x)
                return binarysearch(v, m+1, r, x);    
        }    
    }  

    else return 0;  
}

int main()
{
    int n,m;
    scanf("%d%d", &n, &m);
    int *x = malloc(n*sizeof(int));
    int *y = malloc(m*sizeof(int));

    for(int i = 0;i < n; i++)
        scanf("%d", &x[i]);

    for(int i = 0; i < m; i++)
            scanf("%d", &y[i]);
    for(int i = 0; i < m; i++)
    {
        if(binarysearch(x,0,n - 1, y[i]) == 1)
                printf("1 ");
        else printf("0 ");
    }
    return 0;     
}
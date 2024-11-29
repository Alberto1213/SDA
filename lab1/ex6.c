#include <stdio.h>
#include <stdlib.h>

int binarysearch(int *v,int x,int s,int d)
{
    int st = s;
    int dr = d;
    int m = (st+dr)/2;

    if(v[m] == x)
        return m;
    if(v[m] > x)
        {
            return binarysearch(v,x,st,m - 1);
        }    
    if(v[m] < x)
        {
            return binarysearch(v,x,m + 1,dr);
        }    
}

int main()
{
    int n,x;
    int poz;
    int *v = malloc(n*sizeof(int));
    scanf("%d%d", &n, &x);
    for(int i = 0;i < n;i++)
        scanf("%d", &v[i]);
    poz = binarysearch(v,x,0,n-1);
    //int i = poz;
    //int j = poz; 
    //printf("%d", poz);
    for(int i = poz;i>=0;i--)
    {
        if(v[i]!=v[poz])
            {
                printf("%d", i+1);
                break;
            }
    }
    for(int i = poz;i<n;i++)
    {
        if(v[i]!=v[poz])
            {
                printf(" %d", i-1);
                break;
            }
    }    
    return 0;
}
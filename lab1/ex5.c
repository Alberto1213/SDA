#include <stdio.h>
#include <stdlib.h>

int max(int a,int b)
{
    if(a>b)
        return a;
    else return b;    
}

int min(int a,int b)
{
       if(a<b)
        return a;
    else return b;    
}

void f5(int n, int *x, int *mini, int *maxi, int *sum)
{
    if(n == 0)
    {
        *sum = x[n];
        *mini = x[n];
        *maxi = x[n];
        return;
    }
    else
    {
        f5(n-1,x,mini,maxi,sum);
        *sum += x[n];
        *maxi = max(x[n],*maxi);
        *mini = min(x[n],*mini);
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    int *v = malloc(n*sizeof(int));
    for(int i = 0;i < n;i++)
        scanf("%d", &v[i]);
    int maxx;
    int minn;
    int sum;
    f5(n-1,v,&minn,&maxx,&sum);
    printf("%d %d %d", minn, maxx, sum);
    return 0;
}

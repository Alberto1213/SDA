#include <stdio.h>
#include <stdlib.h>

int f2(int n,int c)
{
    if(n ==0 )
        return 0;
    else
    {
        if(n%10 == c)
            return f2(n/10,c);
        else return f2(n/10,c)*10+n%10;
    }    
}

int main()
{
    int n;
    int c;
    scanf("%d%d", &n, &c);
    printf("%d", f2(n,c));
    return 0;
}
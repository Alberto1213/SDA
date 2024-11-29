#include <stdio.h>
#include <stdlib.h>

int f4(int k)
{
    if(k==1)
        return 0;
    if(k==2)
        return 1;
    else return f4(k-1)+f4(k-2);        
}

int main()
{
    int k;
    scanf("%d", &k);
    printf("%d", f4(k));
    return 0;
}
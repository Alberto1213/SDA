#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int f3_aux(char *s,int n)
{
    char s1[]="aAeEiIoOuU \n";
    if(n == 0)
        return 0;
    else 
    {
        if(strchr(s1,s[n])!=NULL)
            return f3_aux(s,n-1);
        else return 1+f3_aux(s,n-1);    
    }    
}
int f3(char *s)
{
    int size = strlen(s);
    return f3_aux(s,size);
}

int main()
{
    char *s = malloc(100*sizeof(char));
    fgets(s,100,stdin);
    printf("%d", f3(s));
    return 0;
}
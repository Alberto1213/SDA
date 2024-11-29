#include <stdio.h>
#include <stdlib.h>

void my_merge(int *v, int l, int r, int m)
{
    int dim1 = m - l + 1;
    int dim2 = r - m;

    int *v1 = malloc(dim1*sizeof(int));
    int *v2 = malloc(dim2*sizeof(int));

    for(int i = 0; i < dim1; i++)
        v1[i] = v[l + i];

    for(int i = 0;i < dim2; i++)
        v2[i] = v[i + m + 1];    

    int i = 0;
    int j = 0;
    int k = l;

    while(i < dim1 && j < dim2)
    {
        if(v1[i] < v2[j])
            {
                v[k] = v1[i];
                i++;
            }
        else 
        {
            v[k] = v2[j];
            j++;
        }
        k++;
    }

    while(i < dim1)
    {
        v[k] = v1[i];
        i++;
        k++;
    }

    while(j < dim2)
    {
        v[k] = v2[j];
        j++;
        k++;
    }
}

void merge_sort(int *v, int l, int r)
{
    if(l < r)
    {
        int m = (l + r)/2;

        merge_sort(v,l,m);
        merge_sort(v,m+1,r);
        my_merge(v,l,r,m);
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    int *v = malloc(n*sizeof(int));

    for(int i = 0; i < n; i++)
        scanf("%d", &v[i]);

    merge_sort(v,0,n-1);
     for(int i = 0; i < n; i++)
        printf("%d ", v[i]);

    return 0;    
}


#include <stdio.h>
#include <stdlib.h>

typedef struct Nod
{
    int val;
    struct Nod *left;
    struct Nod *right;
}Nod;

void init(Nod **root)
{
    (*root) = (Nod*)malloc(sizeof(Nod));
    (*root) = NULL;
}

struct Nod* new_node(int val)
{
    Nod *new = malloc(sizeof(Nod));
    new->val = val;
    new->left = NULL;
    new->right = NULL;

    return new;
}
void add(Nod **root, int val)
{
    if((*root) == NULL)
    {
        (*root) = new_node(val);
    }
    else
    {
        if(val < (*root)->val)
            add(&((*root)->left),val);
        if(val > (*root)->val)
            add(&((*root)->right),val);    
    }
}

void inorder(Nod *root)
{   
    if(root != NULL)
    {
        inorder(root->left);
        printf("%d ", root->val);
        inorder(root->right);
    }
}
void solve(Nod *root)
{
    Nod *temp1 = root;
    Nod *temp2 = root;
    Nod *parent1, *parent2;
    while(temp1->right != NULL)
    {
        parent1 = temp1;
        temp1 = temp1->right;
    }

    while(temp2->left != NULL)
    {
        parent2 = temp2;
        temp2 = temp2->left;
    }
    if(parent1->val * temp1->val > parent2->val * temp2->val)
        printf("%d", parent1->val * temp1->val);
    else printf("\n%d", parent2->val * temp2->val); 
}
int main()
{
    Nod *root;
    init(&root);
    int n;
    scanf("%d", &n);
    add(&root,-8);
    add(&root,3);
    add(&root,9);
    add(&root,-1);
    add(&root,-2);
    add(&root,7);
    add(&root,-10);
    inorder(root);
    solve(root);
    
    return 0;
}
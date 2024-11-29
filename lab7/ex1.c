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

void preorder(Nod *root)
{
    if(root != NULL)
    {
        printf("%d ", root->val);
        inorder(root->left);
        inorder(root->right);
    }
}
void postorder(Nod *root)
{
    if(root != NULL)
    {
        inorder(root->left);
        inorder(root->right);
        printf("%d ", root->val);
    }
}

struct Nod *lca(Nod *root, int node1, int node2)
{
    if(root == NULL)
        return NULL;
    else
    {
        if(root->val > node1 && root->val > node2)
            lca(root->left,node1,node2);
        if(root->val < node1 && root->val <node2)
            lca(root->right,node1,node2);
        else return root;    
    }    
}
void invers(Nod **root)
{
    if(*root == NULL)
        return;

    struct Nod *temp = (*root)->left;
    (*root)->left = (*root)->right;
    (*root)->right = temp;

    invers(&((*root)->left));
    invers(&((*root)->right));    
}
int count(Nod *root, int n)
{
    int sol = 0;

    if(root == NULL)
        sol = 0;
    if(n < 0)
        sol = 0;

    if(n == 1)
    {
        if(root->val % 2 == 0)
            sol += 1;
        else sol = 0;   
    }        
    else
    {
        if(root->val % 2 == 0)
            sol += 1 + count(root->left,n-1) + count(root->right,n-1); 
        else sol += count(root->left,n-1) + count(root->right,n-1);
    }
    return sol;
}
int numberofnodes(Nod *root)
{
    if(root == NULL)
        return 0;
    else return 1 + numberofnodes(root->left) + numberofnodes(root->right);    
}
float percent(Nod *root,int n)
{
    float res;
    int n1 = numberofnodes(root);
    int n2 = count(root,n);

    res = (100 * n2) / (float)n1;
    return res;
}
int main()
{
    int n;
    scanf("%d", &n);
    Nod *root;
    init(&root);
    add(&root,5);
    add(&root,3);
    add(&root,1);
    add(&root,4);
    add(&root,7);
    add(&root,6);
    add(&root,8);
    //add(&root,12);
    inorder(root);
    Nod *LCA = lca(root,6,12);
    printf("\n%d\n", LCA->val);
    printf("\n%f\n", percent(root, n));
    invers(&root);
    inorder(root);
}
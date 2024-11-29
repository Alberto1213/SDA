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

int f3(Nod *root)
{
    if(root == NULL)
        return 0;
    else
    {
        if(root->left != NULL && root->right != NULL && (2 * root->val > root->left->val + root->right->val))
            return 1+f3(root->left)+f3(root->right);
        else return f3(root->left)+f3(root->right);
    }    
}
void f4(Nod *root)
{
    int count = 0;
    if(root != NULL)
    {
        f4(root->left);
        f4(root->right);
        if(root->left == NULL && root->right != NULL)
        {   
            count++; 
            printf("%d %d\n", root->val, count);
        }
    }    
}
int f5(Nod *root)
{
    int ok = 1;
    if(root->left != NULL && root->right != NULL)
    {
        ok = f5(root->left)&&f5(root->right);
    }
    else
    {
        if((root->left == NULL && root->right!=NULL) || (root->left != NULL && root->right == NULL)) 
        {
            ok = 0;
        }
    }
    return ok;
}
void duplicate(Nod **root)
{
    if(*root == NULL)
        return;
    else
    {
        if((*root)->left == NULL && (*root)->right != NULL)
        {
            Nod *new = new_node((*root)->val);
            (*root)->left = new;
        }
        if((*root)->left != NULL && (*root)->right == NULL)
        {
            Nod *new = new_node((*root)->val);
            new->left = (*root)->left; 
            (*root)->left = new;
        }
        else
        {
            duplicate(&((*root)->left));
            duplicate(&((*root)->right));
        }
    }    
}
int main()
{
    Nod *root;
    init(&root);
    int n;
    add(&root,5);
    add(&root,3);
    add(&root,1);
    add(&root,4);
    add(&root,10);
    add(&root,6);
    add(&root,11);
    add(&root,12);
    inorder(root);
    printf("\n%d", f3(root));
    printf("\n");
    f4(root);
    printf("%d", f5(root));
    printf("\n");
    duplicate(&root);
    inorder(root);
}
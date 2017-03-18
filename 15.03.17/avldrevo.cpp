#include <iostream>
#include <stdio.h>
#include <queue>

struct node{
int height;
node* left;
node* right;
int data;
}*root;

class avlTree{
public:

    avlTree(){ 
        root = NULL;
    }

    void deleteTree(node* n){
if (n == NULL)
    return;
    deleteTree(n -> left);
    deleteTree(n -> right);
    delete n;
}


    ~avlTree(){
    deleteTree(root);
    }

int height(node *p)
{
    int h = 0;
    if (p != NULL)
    {
        int l_height = height (p ->left);
        int r_height = height (p ->right);
        int max_height = std::max (l_height, r_height);
        h = max_height + 1;
    }
    return h;
}

bool DFS (int data, node* n){
if (n == NULL)
    return false;
    if (n -> data == data)
        return true;
        if (DFS(data, n->left))
            return true;
        if (DFS(data, n->right))
            return true;
        return false;
}

int bfactor (node* p){
return height(p -> left) - height(p -> right);
 }

node* rotateright(node* p)
{
	node* q = p-> right;
	p->right= q->left;
	q-> left = p;
	return q;
}

node* rotateleft(node* p)
{
    node* q = p-> left;
    p -> left = q-> right;
    q->right = p;
    return q;
}

node* rotatelr(node *p) 
{
    node* q= p->left;
    p->left = rotateright (q);
    return rotateleft (p);
}

node* rotaterl(node* p) 
{
    node* q = p->right;
    p->right = rotateleft (q);
    return rotateright (p);
}

node* balance(node *q)
{
    if (bfactor(q) > 1)
    {
        if (bfactor (q->left) > 0)
            q = rotateleft (q);
            q = rotatelr (q);
    }
    else if (bfactor(q) < -1)
    {
        if (bfactor (q->right) > 0)
            q = rotaterl (q);
        else
            q = rotateright(q);
    }
    return q;
}

node* insert(node *root, int value)
{
    if (root == NULL)
    {
        root = new node;
        root->data = value;
        root->left = NULL;
        root->right = NULL;
        return root;
    }
    else if (value < root->data)
    {
        root->left = insert(root->left, value);
        root = balance (root);
    }
    else if (value >= root->data)
    {
        root->right = insert(root->right, value);
        root = balance (root);
    }
    return root;
}

node* findmin(node* p)
{
	return p->left?findmin(p->left):p;
}

node* removemin(node* p)
{
	if( p->left == 0 )
		return p->right;
	p->left = removemin(p->left);
	return balance(p);
}

node* remove(node* p, int value)
{
	if( !p ) return 0;
	if( value < p ->data )
		p->left = remove(p->left,value);
	else if( value > p->data )
		p->right = remove(p->right,value);
			else
	{
		node* q = p->left;
		node* r = p->right;
		delete p;
		if( !r ) return q;
		node* min = findmin(r);
		min->right = removemin(r);
		min->left = q;
		return balance(min);
	}
		return balance(p);
}

void display(node* ptr, int level) 
{
    int i;
    if (ptr!=NULL)
    {
        display(ptr->right, level + 1);
        printf("\n");
        if (ptr == root)
        std::cout<<"Root -> ";
        for (i = 0; i < level && ptr != root; i++)
            std::cout<<"        ";
        std::cout<<ptr->data;
        display(ptr->left, level + 1);
    }
}

};

int main(){
    avlTree mytree;

    root = mytree.insert(root, 24);
    root = mytree.insert(root, 48);
    root = mytree.insert (root, 20);
    root = mytree.insert(root, 49);
    root = mytree.insert(root, 50);
    mytree.display(root, 1);
    std::cout << std::endl;
    std::cout << mytree.DFS(24, root) << std::endl;
    root = mytree.remove(root, 24);
    mytree.display(root, 1);

return 0;
}

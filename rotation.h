struct Tree * SingleRotateWithLeft(struct Tree *);
struct Tree * SingleRotateWithRight(struct Tree *);
struct Tree * DoubleRotateWithLeft(struct Tree *);
struct Tree * DoubleRotateWithRight(struct Tree *);
int AVLTreeHeight(struct Tree * );
int Max(int, int);
struct Tree * SingleRotateWithLeft(struct Tree * k2)
{
    struct Tree * k1;
    k1=k2->left;
    k2->left=k1->right;
    k1->right=k2;
    k2->height=Max(AVLTreeHeight(k2->left), AVLTreeHeight(k2->right))+1;
    k1->height=Max(AVLTreeHeight( k1->left), k2->height)+1;
    return k1;
}
// this works if most right side of the tree got too big
struct Tree * SingleRotateWithRight(struct Tree * k1)
{
    struct Tree * k2;
    k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k1->height = Max(AVLTreeHeight(k1->left), AVLTreeHeight(k1->right)) + 1;
    k2->height = Max(AVLTreeHeight(k2->right), k1->height) + 1;
    return k2;
}
// fixing the right side of the left subtree of initial node
struct Tree * DoubleRotateWithLeft(struct Tree * k3)
{
    k3->left= SingleRotateWithRight(k3->left);
    return SingleRotateWithLeft(k3);
}
// fixing the left side of the right subtree of initial node
struct Tree * DoubleRotateWithRight(struct Tree * k3)
{
    k3->right= SingleRotateWithLeft(k3->right);
    return SingleRotateWithRight(k3);
}
int Max(int x, int y)
{
    if (x >= y)
        return x;
    else
        return y;
}
int AVLTreeHeight(struct Tree * t)
{
    if (t == NULL)
        return -1;
    else
        return t->height;
}
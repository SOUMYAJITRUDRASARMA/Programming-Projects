#include "splay_tree.h"

using namespace std;

void setTree1(SplayTree &t)
{
    t.root = new SplayTreeNode(10);

    (t.root)->setLeftChild(new SplayTreeNode(4));
        (t.root)->left->setLeftChild(new SplayTreeNode(2));
            (t.root)->left->left->setLeftChild(new SplayTreeNode(1));
            (t.root)->left->left->setRightChild(new SplayTreeNode(3));
        (t.root)->left->setRightChild(new SplayTreeNode(6));
            (t.root)->left->right->setLeftChild(new SplayTreeNode(5));
            (t.root)->left->right->setRightChild(new SplayTreeNode(7));

    (t.root)->setRightChild(new SplayTreeNode(14));
        (t.root)->right->setLeftChild(new SplayTreeNode(12));
            (t.root)->right->left->setLeftChild(new SplayTreeNode(11));
            (t.root)->right->left->setRightChild(new SplayTreeNode(13));
        (t.root)->right->setRightChild(new SplayTreeNode(16));
            (t.root)->right->right->setLeftChild(new SplayTreeNode(15));
            (t.root)->right->right->setRightChild(new SplayTreeNode(17));
}

void setTree2(SplayTree &t)
{
    t.root = new SplayTreeNode(5);
    (t.root)->setLeftChild(new SplayTreeNode(1));
    (t.root)->left->setRightChild(new SplayTreeNode(2));
    (t.root)->left->right->setRightChild(new SplayTreeNode(3));
    (t.root)->left->right->right->setRightChild(new SplayTreeNode(4));
}

void Find(SplayTree &t,int key)
{
    SplayTreeNode *result = t.search(key);
    if(result==nullptr)
        cout<<"Not Found";
    else
        cout<<"Found: "<<result->key;
}

int main()
{

    SplayTree t;
    setTree2(t);

    t.printPreOrderTraversal(); cout<<endl<<endl;

    Find(t,4); cout<<endl;
    t.printPreOrderTraversal(); cout<<endl<<endl;

    return 0;
}

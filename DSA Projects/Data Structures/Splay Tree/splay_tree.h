#include <bits/stdc++.h>

using namespace std;

class SplayTreeNode
{

public:

    int key;
    SplayTreeNode *left, *right, *parent;

    SplayTreeNode(int key=0);
    SplayTreeNode(const SplayTreeNode &node);
    static SplayTreeNode * leftRotate(SplayTreeNode *node);
    static SplayTreeNode * rightRotate(SplayTreeNode *node);
    void setLeftChild(SplayTreeNode *node);
    void setRightChild(SplayTreeNode *node);

};

class SplayTree
{

public:
    SplayTreeNode *root;

    SplayTreeNode * splay(int key);
    void preOrderTraversalHelper(SplayTreeNode *node);


    SplayTree();
    void printPreOrderTraversal();
    SplayTreeNode * search(int key);

};

SplayTreeNode::SplayTreeNode(int key)
{
    this->key=key;
    left=right=parent=nullptr;
}

SplayTreeNode::SplayTreeNode(const SplayTreeNode &node)
{
    key=node.key;
    left=node.left;
    right=node.right;
    parent=node.parent;
}

SplayTreeNode * SplayTreeNode::leftRotate(SplayTreeNode *node)
{
    SplayTreeNode *n1=node->right;
    if(n1==nullptr)
        return nullptr;

    n1->parent=node->parent;
    node->parent=n1;

    node->right=n1->left;
    n1->left=node;

    return n1;
}

SplayTreeNode * SplayTreeNode::rightRotate(SplayTreeNode *node)
{
    SplayTreeNode *n1=node->left;
    if(n1==nullptr)
        return nullptr;

    n1->parent=node->parent;
    node->parent=n1;

    node->left=n1->right;
    n1->right=node;

    return n1;
}

void SplayTreeNode::setLeftChild(SplayTreeNode *node)
{
    left = node;
    node->parent = this;
}

void SplayTreeNode::setRightChild(SplayTreeNode *node)
{
    right = node;
    node->parent = this;
}

SplayTree::SplayTree()
{
    root=nullptr;
}

/*string SplayTree::preOrderTraversalHelper(SplayTreeNode *node)
{
    if(node!=nullptr)
        return to_string(node->key)+string(":")+( ((node->left==nullptr)?string(""):string("l")) + ((node->right==nullptr)?string(""):string("r")) ) + string("  ") + preOrderTraversalHelper(node->left) + string("  ") + preOrderTraversalHelper(node->right);
}*/

void SplayTree::preOrderTraversalHelper(SplayTreeNode *node)
{
    if(node!=nullptr)
    {
        cout<<node->key<<":"<<((node->left==nullptr)?"":"l")<<((node->right==nullptr)?"":"r")<<"  ";
        preOrderTraversalHelper(node->left);
        preOrderTraversalHelper(node->right);
    }
}

void SplayTree::printPreOrderTraversal()
{
    preOrderTraversalHelper(root);
}

SplayTreeNode * SplayTree::splay(int key)
{
    SplayTreeNode *node = root;

    while(node != nullptr)
    {
        if(key == node->key)
            break;
        else if(key < node->key)
            node = node->left;
        else
            node = node->right;
    }

    if(node == nullptr)
        return node;

    // Time to splay the found node now
    // int cnt=0; // testing
    while(root != node)
    {
        SplayTreeNode *n1, *n2, *temp;

        if(node->parent == root)
        {
            // ZIG Situation ................
            if(root->left == node)
            {
                //     R
                //   /
                // N

                root = SplayTreeNode::rightRotate(root);
            }
            else
            {
                // R
                //   \
                //     N

                root = SplayTreeNode::leftRotate(root);
            }
        }
        else if((node->key - node->parent->key) * (node->parent->key - node->parent->parent->key) < 0)
        {
            // ZIG ZAG Situation ................
            if((node->key > node->parent->key) && (node->parent->key < node->parent->parent->key))
            {
                //     n2
                //   /
                // n1
                //   \
                //     N

                bool rootFlag = root == node->parent->parent; // pre-computing as node's position will change dynamically later
                n2 = (temp = node->parent->parent)->parent;

                // n1 = node->parent->parent->left;
                node->parent->parent->left = SplayTreeNode::leftRotate(node->parent->parent->left);
                // printPreOrderTraversal(); cout<<endl<<endl; // testing

                if(rootFlag)
                {
                    root = SplayTreeNode::rightRotate(root);
                    // printPreOrderTraversal(); cout<<endl<<endl; // testing
                }
                else
                {
                    if(n2->left == temp)
                        n2->left = SplayTreeNode::rightRotate(n2->left);
                    else
                        n2->right = SplayTreeNode::rightRotate(n2->right);
                    // printPreOrderTraversal(); cout<<endl<<endl; // testing
                }
            }
            else
            {
                // n2
                //   \
                //     n1
                //   /
                // N

                bool rootFlag = root == node->parent->parent; // pre-computing as node's position will change dynamically later
                n2 = (temp = node->parent->parent)->parent;

                // n1 = node->parent->parent->right;
                node->parent->parent->right = SplayTreeNode::rightRotate(node->parent->parent->right);
                // printPreOrderTraversal(); cout<<endl<<endl; // testing

                if(rootFlag)
                {
                    root = SplayTreeNode::leftRotate(root);
                    // printPreOrderTraversal(); cout<<endl<<endl; // testing
                }
                else
                {
                    if(n2->left == temp)
                        n2->left = SplayTreeNode::leftRotate(n2->left);
                    else
                        n2->right = SplayTreeNode::leftRotate(n2->right);
                    // printPreOrderTraversal(); cout<<endl<<endl; // testing
                }
            }
            // cout<<cnt<<"_____________________________________"<<endl<<endl; // testing
        }
        else
        {
            // ZIG ZIG Situation ................
            // We first rotate n2 and then n1 [ little more balanced ]
            if((node->key < node->parent->key) && (node->parent->key < node->parent->parent->key))
            {
                //         n2
                //       /
                //     n1
                //   /
                // N

                if(root == node->parent->parent)
                {
                    root = SplayTreeNode::rightRotate(root);
                    root = SplayTreeNode::rightRotate(root);
                }
                else
                {

                    n2 = (temp = node->parent->parent)->parent;
                    if(n2->left == temp)
                    {
                        n2->left = SplayTreeNode::rightRotate(n2->left);
                        n2->left = SplayTreeNode::rightRotate(n2->left);
                    }
                    else
                    {
                        n2->right = SplayTreeNode::rightRotate(n2->right);
                        n2->right = SplayTreeNode::rightRotate(n2->right);
                    }
                }
            }
            else
            {
                // n2
                //   \
                //     n1
                //       \
                //         N

                if(root == node->parent->parent)
                {
                    root = SplayTreeNode::leftRotate(root);
                    root = SplayTreeNode::leftRotate(root);
                }
                else
                {

                    n2 = (temp = node->parent->parent)->parent;
                    if(n2->left == temp)
                    {
                        n2->left = SplayTreeNode::leftRotate(n2->left);
                        n2->left = SplayTreeNode::leftRotate(n2->left);
                    }
                    else
                    {
                        n2->right = SplayTreeNode::leftRotate(n2->right);
                        n2->right = SplayTreeNode::leftRotate(n2->right);
                    }
                }
            }
        }

        // printPreOrderTraversal(); cout<<endl<<endl; // testing
        // break; // testing
        // cnt++; if(cnt>3) break; // testing
    }

    return node;
}

SplayTreeNode * SplayTree::search(int key)
{
    return splay(key);
}


#include <bits/stdc++.h>

using namespace std;

class T23Node
{
public:
    int key1, key2;
    T23Node *left, *center, *right, *parent;
    bool isBinary;

    T23Node(int key1);
    T23Node(int key1, int key2);
    T23Node(bool isBinary = true);

    void insertLeft(T23Node *n);
    void insertCenter(T23Node *n);
    void insertRight(T23Node *n);
};

class TwoThreeTree
{
    T23Node *head;

    void printPreOrderTraversalHelper(T23Node *node);
    void splitUp(T23Node *n);

public:
    TwoThreeTree();
    void printPreOrderTraversal();
    T23Node * search(int key);
    bool insert(int key);
    bool delete(int key);
};

T23Node::T23Node(int key1)
{
    this->key1 = key1;
    this->key2 = 0;
    isBinary = true;
    left = center = right = parent = nullptr;
}

T23Node::T23Node(int key1, int key2)
{
    this->key1 = key1;
    this->key2 = key2;
    isBinary = false;
    left = center = right = parent = nullptr;
}

T23Node::T23Node(bool isBinary)
{
    this->isBinary = isBinary;
    key1 = key2 = 0;
    left = center = right = parent = nullptr;
}

void T23Node::insertLeft(T23Node *n)
{
    left = n;
    n->parent = this;
}

void T23Node::insertCenter(T23Node *n)
{
    center = n;
    n->parent = this;
}

void T23Node::insertRight(T23Node *n)
{
    right = n;
    n->parent = this;
    if(isBinary) isBinary = false;
}

TwoThreeTree::TwoThreeTree()
{
    head = nullptr;
}

void TwoThreeTree::printPreOrderTraversalHelper(T23Node *node)
{
    if(node == nullptr)
        return;

    cout<<node->key1<<((node->isBinary)? "": "|")<<((node->isBinary)? "": node->key2)<<((node->left == nullptr)? "": "L");
    if(node->isBinary)
        cout<<((node->center == nullptr)? "": "R")<<"  ";
    else
        cout<<((node->center == nullptr)? "": "C")<<((node->right == nullptr)? "": "R")<<"  ";

    printPreOrderTraversalHelper(node->left);
    printPreOrderTraversalHelper(node->center);
    if(!node->isBinary)
        printPreOrderTraversalHelper(node->right);
}

void TwoThreeTree::printPreOrderTraversal()
{
    printPreOrderTraversalHelper(root);
}

T23Node * TwoThreeTree::search(int key)
{
    T23Node *curNode = head;
    while(curNode != nullptr)
    {
        if(key < curNode->key1)
            curNode = curNode->left;
        else if(key == curNode->key1)
            return curNode;
        else if(key > curNode->key1)
        {
            if(curNode->isBinary)
                curNode = curNode->center;
            else
            {
                if(key < curNode->key2)
                    curNode = curNode->center;
                else if(key == curNode->key2)
                    return curNode;
                else
                    curNode = curNode->right;
            }
        }

        return nullptr;
    }
}

void TwoThreeTree::splitUp(T23Node *n)
{
    T23Node *parent = n->parent;
    if(!parent) return;

    char childType = (parent->left == n)? 'L': (parent->center == n)? 'C': 'R';
    if(parent->isBinary)
    {

    }
    else
    {

    }
}

bool TwoThreeTree::insert(int key)
{
    if(head == nullptr)
    {
        head = new T23Node(key);
        return true;
    }

    T23Node *curNode = head;
    while(curNode->left || curNode->center || curNode->right)
    {
        if(key < curNode->key1)
            curNode = curNode->left;
        else if(key == curNode->key1)
            return false;
        else if(key > curNode->key1)
        {
            if(curNode->isBinary)
                curNode = curNode->center;
            else
            {
                if(key < curNode->key2)
                    curNode = curNode->center;
                else if(key == curNode->key2)
                    return false;
                else
                    curNode = curNode->right;
            }
        }

        if(key == curNode->key1 || (!curNode->isBinary && key == curNode->key2)) return false;

        // Now, curNode is the node where we must insert
        if(curNode->isBinary)
        {
            if(key < curNode->key1){ curNode->key2 = curNode->key1; curNode->key1 = key; }
            else curNode->key2 = key;
        }
        else
        {
            T23Node *tmp = new T23Node(key);
            if(key < curNode->key1) curNode->left = tmp;
            else if(key < curNode->key2) curNode->center = tmp;
            else curNode->right = tmp;
            tmp->parent = curNode;
            splitUp(tmp);
        }

        return true;
    }
}

bool TwoThreeTree::delete(int key)
{

}

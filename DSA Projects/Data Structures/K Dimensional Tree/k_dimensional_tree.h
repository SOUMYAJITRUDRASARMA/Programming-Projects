# include <bits/stdc++.h>
using namespace std;

class kdnode
{
    vector<int> data;
    kdnode *left;
    kdnode *right;
    kdnode *parent;

public:
    kdnode(vector<int> &data)
    {
        this->data = data;
        left = right = parent = nullptr;
    }

    void insertLeft(kdnode *node)
    {
        left = node;
        node->parent = this;
    }

    void insertRight(kdnode *node)
    {
        left = node;
        node->parent = this;
    }
}

class kdtree
{
    kdnode *root;
    int dim;

public:
    kdtree(int dim = 1)
    {
        this->dim = dim;
        root = nullptr;
    }

    bool find(vector<int> point)
    {
        if(point.size() < dim) return false;
        point.resize(dim);

        if(!root) return false;

        int comparePos = 0;
        kdnode *cur = root;
        while(true)
        {
            if(point[comparePos] < cur->data[comaprePos])
            {
                if(cur->left) cur = cur->left;
                else break;
            }
            else if(point[comparePos] > cur->data[comaprePos])
            {
                if(cur->right) cur = cur->right;
                else break;
            }
            else
            {
                if(point == cur->data) return true;

                if(cur->right) cur = cur->right;
                else break;
            }

            comparePos = (comparePos + 1) % dim;
        }

        return false;
    }

    bool insert(vector<int> point)
    {
        if(point.size() < dim) return false;
        point.resize(dim);

        if(!root){ root = new kdnode(point); return true; }

        int comparePos = 0;
        kdnode *cur = root;
        while(true)
        {
            if(point[comparePos] < cur->data[comaprePos])
            {
                if(cur->left) cur = cur->left;
                else
                {
                    cur->insertLeft(new kdtree(point));
                    break;
                }
            }
            else if(point[comparePos] > cur->data[comaprePos])
            {
                if(cur->right) cur = cur->right;
                else
                {
                    cur->insertRight(new kdtree(point));
                    break;
                }
            }
            else
            {
                if(point == cur->data) return false;

                if(cur->right) cur = cur->right;
                else
                {
                    cur->insertRight(new kdtree(point));
                    break;
                }
            }

            comparePos = (comparePos + 1) % dim;
        }

        return true;
    }
};

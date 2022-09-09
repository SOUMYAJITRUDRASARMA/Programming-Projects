// https://www.geeksforgeeks.org/implementing-patricia-trie-in-java/


# include <bits/stdc++.h>
using namespace std;

class PTNode
{
public:
    unordered_map<string, PTNode *> children;
    PTNode *parent;
    bool isEnd;

    PTNode();
    bool addChild(string &s);
    bool addChild(string &s, PTNode *n);
    bool hasChild(string &s);
};

class PatriciaTrie
{

    PTNode *root;

    PTNode *searchHelper(PTNode *cur, string &s);
    bool insertHelper(PTNode *cur, string &s);
    void printDfsTraversalHelper(PTNode *cur);
    void clearHelper(PTNode *cur);

public:
    PatriciaTrie();
    PTNode *search(string &s);
    bool insert(string &s);
    bool remove(string &s);
    void printDfsTraversal();
    void clear();
    bool empty();

};

PTNode::PTNode()
{
    parent = nullptr;
    isEnd = false;
}

bool PTNode::addChild(string &s)
{
    if(hasChild(s)) return false;
    children[s] = new PTNode();
    children[s]->parent = this;
    return true;
}

bool PTNode::addChild(string &s, PTNode *n)
{
    if(hasChild(s)) return false;
    children[s] = n;
    children[s]->parent = this;
    return true;
}

bool PTNode::hasChild(string &s)
{
    return children.find(s) != children.end();
}

PatriciaTrie::PatriciaTrie()
{
    root = new PTNode();
}

PTNode *PatriciaTrie::searchHelper(PTNode *cur, string &s)
{
    int n = s.size();
    if(n == 0)
        return (cur->isEnd)? cur: nullptr;;

    string tmp;
    for(int i=0;i<n;i++)
    {
        tmp.push_back(s[i]);
        if(cur->hasChild(tmp))
        { string str(s.begin() + i + 1, s.end()); return searchHelper(cur->children[tmp], str); }
    }

    return nullptr;
}

bool PatriciaTrie::insertHelper(PTNode *cur, string &s)
{
    int n = s.size();
    if(n == 0)
    {
        if(cur->isEnd) return false;
        else{ cur->isEnd = true; return true; }
    }

    string tmp(s), tmp2;
    tmp.push_back('#'); // temp char to be removed ...
    // loop from large to small, so that insertion break (2nd loop) consumes less nodes (less split)
    for(int i=n-1;i>=0;i--)
    {
        // tmp.push_back(s[i]);
        tmp.pop_back();
        if(cur->hasChild(tmp))
        { string str(s.begin() + i + 1, s.end()); return insertHelper(cur->children[tmp], str); }

        // checking if higher size string have tmp as prefix ...
        for(pair<string, PTNode *> p: cur->children)
        {
            if(p.first.size() > i+1)
            {
                tmp2 = p.first.substr(0, i+1);
                if(tmp2 == tmp)
                {
                    PTNode *n = p.second;
                    cur->children.erase(p.first);
                    cur->addChild(tmp);
                    string str2(p.first.begin() + i + 1, p.first.end());
                    cur->children[tmp]->addChild(str2, n);
                    string str(s.begin() + i + 1, s.end());
                    return insertHelper(cur->children[tmp], str);
                }
            }
        }
    }

    cur->addChild(s);
    cur->children[s]->isEnd = true;

    return true;
}

PTNode *PatriciaTrie::search(string &s)
{
    if(!s.size()) return nullptr;

    return searchHelper(root, s);
}

bool PatriciaTrie::insert(string &s)
{
    if(!s.size()) return false;

    return insertHelper(root, s);
}

bool PatriciaTrie::remove(string &s)
{
    PTNode *cur = search(s);
    if(!cur)
        return false;

    PTNode *parent, *child;
    cur->isEnd = false;
    while(cur != root)
    {
        if(!cur->children.empty() || cur->isEnd) break;
        parent = cur->parent;
        for(pair<string, PTNode *> p: parent->children){ if(p.second == cur){ parent->children.erase(p.first); break; } }
        delete cur;
        cur = parent;
    }

    // joining back single child lines
    while(cur != root)
    {
        if(!cur->isEnd && cur->children.size() == 1)
        {
            pair<string, PTNode *> pr = *(cur->children.begin());
            child = pr.second;
            parent = cur->parent;

            string tmp;
            for(pair<string, PTNode *> p: parent->children){ if(p.second == cur){ parent->children.erase(p.first); tmp = p.first; break; } }
            tmp += pr.first;
            parent->addChild(tmp, child);

            delete cur;
            cur = parent;
        }
        else break;
    }

    return true;
}

void PatriciaTrie::printDfsTraversalHelper(PTNode *cur)
{
    if(cur == root) cout<<": "<<cur->children.size()<<"  ";
    else cout<<": "<<cur->children.size()<<": "<<cur->isEnd<<"  ";

    if(!cur->children.empty()) cout<<"(  ";
    for(pair<string, PTNode *> p: cur->children)
    {
        cout<<p.first;
        printDfsTraversalHelper(p.second);
    }
    if(!cur->children.empty()) cout<<")  ";
}

void PatriciaTrie::printDfsTraversal()
{
    if(root->children.empty()){ cout<<"Empty"; return; }

    cout<<"__ROOT__";
    printDfsTraversalHelper(root);
}

void PatriciaTrie::clearHelper(PTNode *cur)
{
    // dfs and delete on recursive callback
    for(pair<string, PTNode *> p: cur->children)
    {
        clearHelper(p.second);
        delete p.second;
    }
}

void PatriciaTrie::clear()
{
    clearHelper(root);
    root->children.clear();
}

bool PatriciaTrie::empty()
{
    return root->children.empty();
}


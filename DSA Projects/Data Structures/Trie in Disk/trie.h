#include "disk_allocation.h"

class Trie
{
    string name;
    DiskAllocator *da;
    TrieNode n;

    void getAllWordsHelper(long long numNode, string &curPath, vector<string> &v)
    {
        TrieNode tn;
        da->loadNode(tn, numNode);
        if(tn.isEnd) v.push_back(curPath);

        for(char ch = 'a'; ch <= 'z'; ch++)
            if(tn.next[ch - 'a'] != NIL)
                curPath.push_back(ch), 
                getAllWordsHelper(tn.next[ch - 'a'], curPath, v), 
                curPath.pop_back();
    }

public:
    string getDiskAllocatorStats()
    {
        return da->getDevStats();
    }

    Trie(string name)
    {
        this->name = name;
        da = new DiskAllocator(this->name);
    }

    ~Trie()
    {
        delete da;
    }

    bool search(string key)
    {
        da->loadNode(n, HEAD);
        for(char ch: key)
        {
            // cout << n << endl << endl;
            if(n.next[ch - 'a'] == NIL) return false;
            else da->loadNode(n, n.next[ch - 'a']);
        }

        // cout << n << endl << endl;
        return n.isEnd;
    }

    bool insert(string key)
    {
        long long curLoc = HEAD;
        da->loadNode(n, HEAD);
        for(char ch: key)
        {
            // cout << "curLoc: " << curLoc << " | " << n << endl << endl;

            if(n.next[ch - 'a'] == NIL)
            {
                n.next[ch - 'a'] = da->allocateNode();
                da->dumpNode(n, curLoc);
            }
            
            da->loadNode(n, curLoc = n.next[ch - 'a']);
        }

        // cout << "curLoc: " << curLoc << " | " << n << endl << endl;

        if(n.isEnd) return false;

        n.isEnd = true;
        da->dumpNode(n, curLoc);
        return true;
    }

    bool remove(string key)
    {
        return false;
    }

    vector<string> getAllWords()
    {
        vector<string> ans;
        string curPath;
        getAllWordsHelper(HEAD, curPath, ans);
        return ans;
    }
};
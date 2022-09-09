#include <bits/stdc++.h>
using namespace std;

#define NUM_CHAR 26
#define NIL -1

class TrieNode
{
public:
    bool isEnd;
    long long next[NUM_CHAR];

    TrieNode()
    {
        isEnd = false;
        for(int i = 0; i < NUM_CHAR; i++) next[i] = NIL;
    }

    friend ostream &operator << (ostream &os, TrieNode &n);
};

ostream &operator << (ostream &os, TrieNode &n)
{
    os << "isEnd: " << ((n.isEnd)? "True": "False") <<endl;
    for(char ch = 'a'; ch <= 'z'; ch++) if(n.next[ch - 'a'] != NIL) os << ch << ": " << n.next[ch - 'a'] << " | ";
    return os;
}
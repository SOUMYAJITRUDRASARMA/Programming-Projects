#include <bits/stdc++.h>
using namespace std;

// 0 - indexed ...
#define PARENT(n, k) (((n) - 1) / (k))
#define LEFTMOST_CHILD(n, k) ((k) * (n) + 1)


class Heap
{
    // Max Heap Implementation ...
    vector<int> v;
    int k;

    void siftUp(int pos)
    {
        int p = PARENT(pos, k);
        if(v[p] < v[pos]) swap(v[p], v[pos]), siftUp(p);
    }

    void siftDown(int pos)
    {
        int lc = LEFTMOST_CHILD(pos, k), maxIndex = lc;
        if(lc >= v.size()) return;
        for(int i = 1; i < k && lc + i < v.size(); i++) if(v[lc + i] > v[maxIndex]) maxIndex = lc + i;
        if(v[maxIndex] > v[pos]) swap(v[maxIndex], v[pos]), siftDown(maxIndex);
    }

public:
    Heap(int k = 2)
    {
        this->k = k;
    }

    vector<int> &getArray()
    {
        return v;
    }

    bool empty()
    {
        return v.empty();
    }

    size_t size()
    {
        return v.size();
    }

    void push(int e)
    {
        v.push_back(e);
        siftUp(v.size() - 1);
    }

    int top()
    {
        if(empty()) return -1;
        else return v.front();
    }

    void pop()
    {
        if(empty()) return;

        v[0] = v.back();
        v.pop_back();
        siftDown(0);
    }
};
#include "k_heap.hpp"

int main()
{
    int NUM = 1000, e;
    srand(time(0));
    vector<int> actual, pred;
    Heap h(14);

    for(int i = 0; i < NUM; i++)
    {
        e = rand() % 1000;
        actual.push_back(e);
        h.push(e);
    }
    // for(int e: h.getArray()) cout << e << " , "; cout << endl;

    sort(actual.begin(), actual.end(), greater<int>());

    while(!h.empty()) pred.push_back(h.top()), h.pop();

    // for(int e: actual) cout << e << " , "; cout << endl;
    // for(int e: pred) cout << e << " , "; cout << endl;

    cout << "Result: " << (actual == pred) << endl;
}
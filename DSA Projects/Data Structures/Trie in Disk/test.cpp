#include "disk_allocation.h"

void f1()
{
    string name("lol");
    DiskAllocator da(name);

    cout<<"Initial -->"<<endl<<da.getDevStats()<<endl<<endl;

    TrieNode n;
    for(long long i = 1; i <= 10; i++)
    {
        cout << "Allocated = " << da.allocateNode() <<endl;
        cout << da.getDevStats() << endl;
    }

    for(long long i = 0; i <= 10; i++)
    {
        da.loadNode(n, i);
        cout << "Loaded #" << i << " -->" << endl;
        cout << n << endl << endl;

        n.isEnd = i % 2 == 0;
        n.next[i] = i + 100;

        da.dumpNode(n, i);
    }

    da.deallocateNode(3);
    cout<<da.getDevStats()<<endl<<endl;

    da.deallocateNode(6);
    cout<<da.getDevStats()<<endl<<endl;

    cout << "Allocated: " << da.allocateNode() <<endl;
    cout<<da.getDevStats()<<endl<<endl;
}

void f2()
{
    string name("lol");
    DiskAllocator da(name);

    cout<<"Initial -->"<<endl<<da.getDevStats()<<endl<<endl;

    TrieNode n;
    bool result;
    for(long long i = 0; i <= 10; i++)
    {
        result = da.loadNode(n, i);
        cout << "Loaded #" << i << " -->" << endl;
        if(result)
            cout << n << endl << endl;
        else
            cout << "Deallocated !!!" << endl << endl;
    }
}

int main()
{
    // f1();
    f2();

    return 0;
}
#include <iostream>
#include "trie.h"

using namespace std;

int main()
{
    int l;
    trie t;

    cout<<t.add("a")<<endl;
    cout<<t.add("ab")<<endl;
    cout<<t.add("ac")<<endl;
    cout<<t.add("abc")<<endl;
    cout<<t.add("acd")<<endl;
    cout<<t.add("abcde")<<endl<<endl;

    l=t.print_all_words();
    cout<<"Count = "<<l<<endl<<endl;

    /*cout<<t.remove("ab")<<endl<<endl;
    cout<<t.remove("a")<<endl<<endl;

    l=t.print_all_words();
    cout<<"Count = "<<l<<endl<<endl;

    t.clear();
    cout<<"Cleared ..."<<endl<<endl;

    l=t.print_all_words();
    cout<<"Count = "<<l<<endl;*/

    return 0;
}

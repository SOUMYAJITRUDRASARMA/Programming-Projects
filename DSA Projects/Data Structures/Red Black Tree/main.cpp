#include "red_black_tree.h"
#define NEWL cout<<endl

using namespace std;

int main()
{
    red_black_tree rbt;

    rbt.display_tree_2D();

    NEWL;
    NEWL;

    cout<<rbt.insert(1);
    cout<<rbt.insert(2);
    cout<<rbt.insert(3);
    cout<<rbt.insert(4);
    cout<<rbt.insert(5);

    NEWL;

    rbt.display_tree_2D();

    NEWL;
    NEWL;

    cout<<rbt.search(1);
    cout<<rbt.search(2);
    cout<<rbt.search(3);
    cout<<rbt.search(4);
    cout<<rbt.search(5);
    cout<<rbt.search(6);
    cout<<rbt.search(7);
    cout<<rbt.search(8);
    cout<<rbt.search(9);
    cout<<rbt.search(10);

    NEWL;
    NEWL;

    rbt.clear();

    rbt.display_tree_2D();

    NEWL;
    NEWL;

}

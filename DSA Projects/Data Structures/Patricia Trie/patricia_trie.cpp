# include "patricia_trie.h"
# define NEWL cout<<endl
using namespace std;

int main()
{
    PatriciaTrie pt;

    int choice;
    string st;
    while(true)
    {
        cout<<"Press 1 for search"<<endl;
        cout<<"Press 2 for insert"<<endl;
        cout<<"Press 3 for delete"<<endl;
        cout<<"Press 4 for DFS traversal"<<endl;
        cout<<"Press 5 to clear"<<endl;
        cout<<"Press 6 to exit"<<endl;
        cout<<"Enter your choice: ";

        cin>>choice;

        switch(choice)
        {
        case 1:
            NEWL;
            cout<<"Enter search string: ";
            cin>>st;
            cout<<"Result: "<<(pt.search(st) != nullptr)<<endl;
            NEWL;
            break;

        case 2:
            NEWL;
            cout<<"Enter insert string: ";
            cin>>st;
            cout<<"Result: "<<pt.insert(st)<<endl;
            NEWL;
            break;

        case 3:
            NEWL;
            cout<<"Enter delete string: ";
            cin>>st;
            cout<<"Result: "<<pt.remove(st)<<endl;
            NEWL;
            break;

        case 4:
            NEWL;
            cout<<"DFS Traversal -->"<<endl<<endl;
            pt.printDfsTraversal();
            NEWL;
            NEWL;
            break;

        case 5:
            NEWL;
            pt.clear();
            cout<<"Cleared ..."<<endl;
            NEWL;
            break;

        case 6:
            NEWL;
            cout<<"Program ended"<<endl;
            return 0;
            NEWL;
            break;

        default:
            NEWL;
            cout<<"Invalid Choice, please try again ..."<<endl;
            NEWL;
            break;


        }
    }

    return 0;
}

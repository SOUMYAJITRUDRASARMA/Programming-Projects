#include "trie.h"

int main()
{
    string dbName("my_dict");
    Trie t(dbName);
    int choice;
    bool doCont = true;
    string key;
    vector<string> allWords;

    while(doCont)
    {
        cout << "Press 1 to search" << endl;
        cout << "Press 2 to insert" << endl;
        cout << "Press 3 to delete" << endl;
        cout << "Press 4 to print all words" << endl;
        cout << "Press 5 for disk allocator stats" << endl;
        cout << "Press 6 to exit" << endl;
        cout << "Enter your choice: ";

        cin >> choice;

        switch(choice)
        {
        case 1:
            cout << endl;
            cout << "Enter key to search: ";
            cin >> key;
            cout << ((t.search(key))? "Found ...": "Not Found ...") << endl;
            cout << endl;
            break;
        
        case 2:
            cout << endl;
            cout << "Enter key to insert: ";
            cin >> key;
            cout << ((t.insert(key))? "Inserted successfully ...": "Already Present ...") << endl;
            cout << endl;
            break;
        
        case 3:
            cout << endl;
            cout << "Enter key to delete: ";
            cin >> key;
            cout << ((t.remove(key))? "Deleted successfully ...": "Not Found ...") << endl;
            cout << endl;
            break;

        case 4:
            cout << endl;
            cout << "ALL WORDS -->" << endl;
            allWords = t.getAllWords();
            for(string &word: allWords)
                cout << word << endl;
            cout << endl << "Total # words = " << allWords.size() << endl;
            cout << endl;
            break;
        
        case 5:
            cout << endl;
            cout << "DISK ALLOCATOR STATS -->" << endl;
            cout << t.getDiskAllocatorStats() << endl;
            cout << endl;
            break;
        
        case 6:
            doCont = false;
            break;
        
        default:
            cout << endl;
            cout << "Invalid choice, please try again ..." << endl;
            cout << endl;
        }
    }

    cout << endl << "Program ended !!!" << endl << endl;
}
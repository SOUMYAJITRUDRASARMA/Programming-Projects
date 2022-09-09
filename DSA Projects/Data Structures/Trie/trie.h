#define NUMBER_OF_LETTERS 26
//#define MAX_WORD_LENGTH 100
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

class trienode
{
    //making everything public as it is a basic node structure ...

public:

    trienode *next[NUMBER_OF_LETTERS];
    bool is_end_of_word;

    trienode();

};

class trie
{

    trienode *head;

    int del_util_int(trienode *node,string word,int pos);
    int print_all_words_util_int(trienode *node,string word);
    void clear_util_int(trienode *node);

public:

    trie();
    ~trie();
    bool add(string word);
    bool search(string word);
    bool remove(string word);
    int print_all_words();
    void clear();
    bool save_to_file(char *filename);
    bool load_from_file(char *filename);

};

trienode::trienode()
{
    for(int i=0;i<NUMBER_OF_LETTERS;next[i++]=nullptr);
    is_end_of_word=false;
}

int trie::del_util_int(trienode *node,string word,int pos)
{
    // returns 0 -> not found, 1->found and delete child node, 2->found and don't delete child node

    bool flag=true; // can i free up this node

    if(pos==word.length())
    {
        if(!node->is_end_of_word)
            return 0;

        node->is_end_of_word=false;

        flag=true;
        for(int i=0;i<NUMBER_OF_LETTERS;i++)
            if(node->next!=nullptr)
                flag=false;

        if(flag)
            return 1;
        else
            return 2;
    }

    if(node->next[word[pos]-'a']==nullptr)
        return 0;

    int res=del_util_int(node->next[word[pos]-'a'],word,pos+1);

    if(res==0)
        return 0;
    else if(res==1)
    {
        delete node->next[word[pos]-'a'];
        node->next[word[pos]-'a']=nullptr;
        flag=true;
        for(int i=0;i<NUMBER_OF_LETTERS;i++)
            if(node->next!=nullptr)
                flag=false;
        if(flag)
            return 1;
        else
            return 2;
    }
    else
        return 2;

}

trie::trie()
{
    head=new trienode();
}

trie::~trie()
{
    clear();
    delete head;
}

bool trie::add(string word)
{
    trienode *temp=head;
    for(int i=0;i<word.length();i++)
    {
        if(temp->next[word[i]-'a']==nullptr)
            temp->next[word[i]-'a']=new trienode();
        temp=temp->next[word[i]-'a'];
    }

    if(temp->is_end_of_word)
        return false;

    return temp->is_end_of_word=true;
}

bool trie::search(string word)
{
    trienode *temp=head;
    for(int i=0;i<word.length();i++)
    {
        if(temp->next[word[i]-'a']==nullptr)
            return false;
        temp=temp->next[word[i]-'a'];
    }

    if(temp->is_end_of_word)
        return true;
    else
        return false;
}

bool trie::remove(string word)
{
    if(word.length()==0)
        return false;

    int result=del_util_int(head,word,0);
    if(result==0)
        return false;
    else
        return true;
}

int trie::print_all_words()
{
    return print_all_words_util_int(head,"");
}

int trie::print_all_words_util_int(trienode *node,string word)
{
    static int cnt=0;
    if(word=="")
        cnt=0;
    if(node->is_end_of_word)
    {
        cout<<word<<endl;
        cnt++;
    }
    for(int i=0;i<NUMBER_OF_LETTERS;i++)
    {
        if(node->next[i]!=nullptr)
        {
            word.push_back('a'+i);
            print_all_words_util_int(node->next[i],word);
            word.pop_back();
        }
    }
    return cnt;
}

void trie::clear_util_int(trienode *node)
{
    // like post-order traversal deleting
    for(int i=0;i<NUMBER_OF_LETTERS;i++)
    {
        if(node->next[i]!=nullptr)
        {
            clear_util_int(node->next[i]);
            delete node->next[i];
            node->next[i]=nullptr;
        }
    }
}

void trie::clear()
{
    clear_util_int(head);
}

bool trie::save_to_file(char *filename)
{

}

bool trie::load_from_file(char *filename)
{

}

/*void writeNode(Node *node)
    write node data to file
    write node.numOfChildren to file
    for each child:
        writeNode(child)

Node *readNode()
    Node *node = allocateNewNode()
    read node data from file
    read node.numOfChildren from file
    for (i=0; i<node.numOfChildren; i++)
        Node *child = readNode()
        node.addChild(child)*/

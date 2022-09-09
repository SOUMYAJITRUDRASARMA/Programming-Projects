#include "trie_node.h"

// #define MAX_NAME_SIZE 100
#define HEAD 0

class DiskAllocator
{
    string name, statsFileName, dataFileName;
    fstream fileStats, fileData;
    long long n;  // number of allocated nodes other than root (always allocated)
    vector<long long> freeIndex;  // location of freed up indexes to use -> we are not using unordered_set to check for no misuse -> we entrust that on the users
    TrieNode deallocNodeFormat;

    bool fileExists(string name)
    {
        FILE *fp;
        if(fp = fopen(name.c_str(), "r")){ fclose(fp); return true; }
        else return false;
    }

    void firstOpeningActions()
    {
        if(fileExists(statsFileName) && fileExists(dataFileName))
        {
            fileStats.open(statsFileName, ios::in | ios::out);
            // fileData.open(dataFileName, ios::in | ios::out | ios::binary);

            fileStats >> n;
            size_t tmpSize;
            fileStats >> tmpSize;
            freeIndex.resize(tmpSize);
            for(long long &e: freeIndex) fileStats >> e;

            fileStats.close();
        }
        else
        {
            n = 0;

            fileData.open(dataFileName, ios::trunc | ios::out | ios::binary);
            // Allocating head node
            TrieNode tmp;
            fileData.write((char *)&tmp, sizeof(TrieNode));
            fileData.close();
            // fileData.close();
            // fileData.open(dataFileName, ios::in | ios::out | ios::binary);
        }

        // assert(fileData.good());
    }

public:
    string getDevStats()
    {
        assert(fileData.good());

        string ans;
        ans += "n: " + to_string(n) + "\nFree Index: ";
        for(int e: freeIndex) ans += to_string(e) + ", ";
        ans += "\n\n";
        return ans;
    }

    DiskAllocator(string name = "global")
    {
        this->name = name;
        this->statsFileName = this->name + "_stats.dat";
        this->dataFileName = this->name + "_data.dat";

        deallocNodeFormat.next[0] = LONG_LONG_MAX;

        firstOpeningActions();
    }

    ~DiskAllocator()
    {
        fileData.close();

        // Saving stats
        fileStats.open(statsFileName, ios::in | ios::out | ios::trunc);
        fileStats << n << " ";
        fileStats << freeIndex.size() << " ";
        for(long long e: freeIndex) fileStats << e << " ";
        fileStats.close();
    }

    bool loadNode(TrieNode &node, long long nodeNumber)
    {
        // assert(fileData.good());
        // fileData.clear();

        if(nodeNumber < HEAD || nodeNumber > n) return false;

        fileData.open(dataFileName, ios::in | ios::out | ios::binary);
        fileData.seekg(nodeNumber * sizeof(TrieNode), ios::beg);
        fileData.read((char *)&node, sizeof(TrieNode));
        fileData.close();

        if(node.next[0] == LONG_LONG_MAX) return false;  // Deallocated

        return true;
    }

    bool dumpNode(TrieNode &node, long long nodeNumber)
    {
        // assert(fileData.good());
        // fileData.clear();

        if(nodeNumber < HEAD || nodeNumber > n) return false;

        TrieNode tmp;
        fileData.open(dataFileName, ios::in | ios::out | ios::binary);
        fileData.seekg(nodeNumber * sizeof(TrieNode), ios::beg);
        fileData.read((char *)&tmp, sizeof(TrieNode));
        fileData.close();

        if(tmp.next[0] == LONG_LONG_MAX) return false;  // Cannot dump to deallocated space

        // fileData.clear();

        fileData.open(dataFileName, ios::in | ios::out | ios::binary);
        fileData.seekp(nodeNumber * sizeof(TrieNode), ios::beg);
        fileData.write((char *)&node, sizeof(TrieNode));
        fileData.close();

        return true;
    }

    long long allocateNode()
    {
        // assert(fileData.good());
        // fileData.clear();

        TrieNode node;

        if(!freeIndex.empty())
        {
            long long pos = freeIndex.back();
            freeIndex.pop_back();

            dumpNode(node, pos);
            return pos;
        }

        n++;
        // fileData.close();
        // fileData.open(dataFileName, ios::app | ios::out | ios::binary | ios::trunc);
        // fileData.write((char *)&node, sizeof(TrieNode));
        // fileData.close();
        // fileData.open(dataFileName, ios::in | ios::out | ios::binary);
        dumpNode(node, n);

        return n;
    }

    bool deallocateNode(long long nodeNumber)
    {
        // assert(fileData.good());

        if(nodeNumber <= HEAD || nodeNumber > n) return false;  // Cannot deallocated head too

        // fileData.clear();

        TrieNode node;
        fileData.open(dataFileName, ios::in | ios::out | ios::binary);
        fileData.seekg(nodeNumber * sizeof(TrieNode), ios::beg);
        fileData.read((char *)&node, sizeof(TrieNode));
        fileData.close();

        if(node.next[0] == LONG_LONG_MAX) return false;  // Node has already been deallocated

        // fileData.clear();

        fileData.open(dataFileName, ios::in | ios::out | ios::binary);
        fileData.seekp(nodeNumber * sizeof(TrieNode), ios::beg);
        fileData.write((char *)&deallocNodeFormat, sizeof(TrieNode));
        fileData.close();

        freeIndex.push_back(nodeNumber);
        return true;
    }
};
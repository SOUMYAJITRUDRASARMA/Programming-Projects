#include <bits/stdc++.h>

using namespace std;

class Graph
{
    vector<vector<int>> adjList;
    int n;
public:
    Graph(int n);
    Graph(Graph &g);
    int getNumVertices();
    bool hasEdge(int from,int to);
    bool hasBidirectionalEdge(int from,int to);
    bool addEdge(int from,int to);
    bool deleteEdge(int from,int to);
    bool addBidirectionalEdge(int from,int to);
    bool deleteBidirectionalEdge(int from,int to);
    vector<int> getNeighbours(int n);

    friend ostream& operator << (ostream &ost,Graph &g);
};

Graph::Graph(int n)
{
    this->n=n;
    adjList=vector<vector<int>>(this->n);
}

Graph::Graph(Graph &g)
{
    this->n=g.getNumVertices();
    adjList=vector<vector<int>>(this->n);
    for(int i=0;i<n;i++)
    {
        for(int j:g.getNeighbours(i))
            addEdge(i,j);
    }
}

int Graph::getNumVertices()
{
    return n;
}

bool Graph::hasEdge(int from,int to)
{
    /*for(int i:adjList[from])
        if(i==to)*/
    if(find(adjList[from].begin(),adjList[from].end(),to)!=adjList[from].end())
            return true;
    return false;
}

bool Graph::hasBidirectionalEdge(int from,int to)
{
    return hasEdge(from,to)&&hasEdge(to,from);
}

bool Graph::addEdge(int from,int to)
{
    if(hasEdge(from,to))
        return false;

    adjList[from].push_back(to);
    return true;
}

bool Graph::deleteEdge(int from,int to)
{
    auto it=find(adjList[from].begin(),adjList[from].end(),to);
    if(it==adjList[from].end())
        return false;
    adjList[from].erase(it);
    return true;
}

bool Graph::addBidirectionalEdge(int from,int to)
{
    bool res1=addEdge(from,to),res2=addEdge(to,from);
    return res1||res2;
}

bool Graph::deleteBidirectionalEdge(int from,int to)
{
    bool res1=deleteEdge(from,to),res2=deleteEdge(to,from);
    return res1||res2;
}

vector<int> Graph::getNeighbours(int n)
{
    return adjList[n];
}

ostream& operator << (ostream &ost,Graph &g)
{
    int n=g.getNumVertices();
    for(int i=0;i<n;i++)
    {
        ost<<"Vertex "<<i<<" :    [  ";
        for(int j:g.getNeighbours(i))
            ost<<j<<"  ";
        ost<<"]  # Neighbours = "<<g.getNeighbours(i).size()<<"\n";
    }
    ost<<"\nTotal # vertices = "<<n<<endl;

    return ost;
}

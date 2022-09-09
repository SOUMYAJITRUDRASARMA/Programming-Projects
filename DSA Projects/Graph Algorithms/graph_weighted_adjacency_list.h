#include <bits/stdc++.h>
#define INF_WT FLT_MAX
#define NEG_INF_WT -FLT_MAX-1

using namespace std;

class GraphW
{
    vector<vector<pair<int,float>>> adjList;
    int n;
    //const static float INF=FLT_MAX;
public:
    GraphW(int n);
    GraphW(GraphW &g);
    GraphW reverseGraph();
    int getNumVertices();
    bool hasEdge(int from,int to);
    bool hasBidirectionalEdge(int from,int to);
    bool addEdge(int from,int to,float weight);
    bool deleteEdge(int from,int to);
    bool addBidirectionalEdge(int from,int to,float weight);
    bool deleteBidirectionalEdge(int from,int to);
    vector<pair<int,float>> getNeighbours(int n);
    float getEdgeWeight(int from,int to);

    friend ostream& operator << (ostream &ost,GraphW &g);
};

class FindVertexHelper
{
    int vertex;
public:
    FindVertexHelper(int vertex)
    {
        this->vertex=vertex;
    }
    bool operator () (pair<int,float> p)
    {
        if(p.first==vertex)
            return true;
        else
            return false;
    }
};

GraphW::GraphW(int n)
{
    this->n=n;
    adjList=vector<vector<pair<int,float>>>(this->n);
}

GraphW::GraphW(GraphW &g)
{
    this->n=g.getNumVertices();
    adjList=vector<vector<pair<int,float>>>(this->n);
    for(int i=0;i<n;i++)
    {
        for(pair<int,float> j:g.getNeighbours(i))
            addEdge(i,j.first,j.second);
    }
}

GraphW GraphW::reverseGraph()
{
    GraphW g(n);
    for(int i=0;i<n;i++)
    {
        for(pair<int,float> j:getNeighbours(i))
            g.addEdge(j.first,i,j.second);
    }

    return g;
}

int GraphW::getNumVertices()
{
    return n;
}

bool GraphW::hasEdge(int from,int to)
{
    /*for(int i:adjList[from])
        if(i==to)*/
    if(find_if(adjList[from].begin(),adjList[from].end(),FindVertexHelper(to))!=adjList[from].end())
            return true;
    return false;
}

bool GraphW::hasBidirectionalEdge(int from,int to)
{
    return hasEdge(from,to)&&hasEdge(to,from);
}

bool GraphW::addEdge(int from,int to,float weight)
{
    if(hasEdge(from,to))
        return false;

    adjList[from].push_back(make_pair(to,weight));
    return true;
}

bool GraphW::deleteEdge(int from,int to)
{
    auto it=find_if(adjList[from].begin(),adjList[from].end(),FindVertexHelper(to));
    if(it==adjList[from].end())
        return false;
    adjList[from].erase(it);
    return true;
}

bool GraphW::addBidirectionalEdge(int from,int to,float weight)
{
    bool res1=addEdge(from,to,weight),res2=addEdge(to,from,weight);
    return res1||res2;
}

bool GraphW::deleteBidirectionalEdge(int from,int to)
{
    bool res1=deleteEdge(from,to),res2=deleteEdge(to,from);
    return res1||res2;
}

vector<pair<int,float>> GraphW::getNeighbours(int n)
{
    return adjList[n];
}

float GraphW::getEdgeWeight(int from,int to)
{
    auto it=find_if(adjList[from].begin(),adjList[from].end(),FindVertexHelper(to));
    if(it==adjList[from].end())
        return INF_WT;
    return it->second;
}

ostream& operator << (ostream &ost,GraphW &g)
{
    int n=g.getNumVertices();
    for(int i=0;i<n;i++)
    {
        ost<<"Vertex "<<i<<" :    [  ";
        for(pair<int,float> j:g.getNeighbours(i))
            ost<<j.first<<":"<<j.second<<"  ";
        ost<<"]  # Neighbours = "<<g.getNeighbours(i).size()<<"\n";
    }
    ost<<"\nTotal # vertices = "<<n<<endl;

    return ost;
}

using namespace std;
using namespace std::chrono;

/*
* 1. Bidirectional Dijkstra
* 2. A* Directed Search
*/

class CompareNodeDistPair
{
public:
    bool operator () (pair<int,float> p1,pair<int,float> p2)
    {
        return p1.second>p2.second;
    }
};

// BIDIRECTIONAL DIJKSTRA

pair<float,vector<int>> ShortestPathBidirectionalDijkstra(GraphW &g, int start, int end, vector<int> &prev, vector<int> &prevR, vector<float> &dist, vector<float> &distR, vector<bool> &vis, vector<bool> &visR)
{
    float distance = INF_WT;
    int uBest = -1; // None
    int n = g.getNumVertices();

    for(int i=0;i<n;i++)
    {
        if(vis[i] || visR[i])
        {
            float addDist = (dist[i]==INF_WT)?INF_WT: (distR[i]==INF_WT)?INF_WT: (dist[i]+distR[i]);
            if(addDist < distance)
            {
                uBest = i;
                distance = addDist;
            }
        }
    }

    vector<int> path;
    if(uBest == -1)
        return make_pair(distance,path);

    int last = uBest;
    while(last != start)
    {
        path.push_back(last);
        last = prev[last];
    }
    path.push_back(start);
    reverse(path.begin(),path.end());

    last = uBest;
    while(last != end)
    {
        path.push_back(last = prevR[last]);
    }

    return make_pair(distance,path);
}

pair<float,vector<int>> BidirectionalDijkstra(GraphW &g, int start, int end)
{
     auto startTime = high_resolution_clock::now();
    GraphW gR(0);
    gR = g.reverseGraph(); // reverse graph
     auto stopTime = high_resolution_clock::now();
     auto duration = duration_cast<microseconds>(stopTime - startTime);
     cout<<"Time to compute reverse graph: "<<duration.count()<<" ms"<<endl;

    int n = g.getNumVertices();

    vector<int> prev(n,-1), prevR(n,-1);
    vector<float> dist(n,INF_WT), distR(n,INF_WT);
    dist[start] = 0;
    distR[end] = 0;
    vector<bool> vis(n,false), visR(n,false);

    priority_queue<pair<int,float>,vector<pair<int,float>>,CompareNodeDistPair> pq, pqR;
    pq.push(make_pair(start,0.0f));
    pqR.push(make_pair(end,0.0f));
    pair<int,float> pairIndexMinValue;

    while(!(pq.empty() && pqR.empty()))
    //  while(true)
    {
        if(!pq.empty())
        {
            pairIndexMinValue=pq.top();
            int index=pairIndexMinValue.first;
            float minValue=pairIndexMinValue.second;
            pq.pop();

            if(!vis[index])
            {
                vis[index]=true;

                for(pair<int,float> e:g.getNeighbours(index))
                {
                    if(vis[e.first])
                        continue;

                    float newDist=dist[index]+e.second;
                    if(newDist<dist[e.first])
                    {
                        prev[e.first]=index;
                        dist[e.first]=newDist;
                        pq.push(make_pair(e.first,newDist));
                    }
                }

                if(visR[index])
                    return ShortestPathBidirectionalDijkstra(g, start, end, prev, prevR, dist, distR, vis, visR);
            }
        }

        if(!pqR.empty())
        {
            pairIndexMinValue=pqR.top();
            int index=pairIndexMinValue.first;
            float minValue=pairIndexMinValue.second;
            pqR.pop();

            if(!visR[index])
            {
                visR[index]=true;

                for(pair<int,float> e:gR.getNeighbours(index))
                {
                    if(visR[e.first])
                        continue;

                    float newDist=distR[index]+e.second;
                    if(newDist<distR[e.first])
                    {
                        prevR[e.first]=index;
                        distR[e.first]=newDist;
                        pqR.push(make_pair(e.first,newDist));
                    }
                }

                if(vis[index])
                    return ShortestPathBidirectionalDijkstra(g, start, end, prev, prevR, dist, distR, vis, visR);
            }
        }
    }

    // not reachable ...
    return make_pair(INF_WT,vector<int>());
}

// A* DIRECTED SEARCH

float defaultPotential(int vertex,void *args=nullptr)
{
    return 0; // makes it defaultDijkstra
}

pair<float,vector<int>> aStarDirectedSearch(GraphW &g, int start, int end, float (*potential)(int,void *) = defaultPotential, void *args = nullptr)
{
    if(potential == nullptr)
        potential = defaultPotential;

    int n = g.getNumVertices();
    vector<int> prev(n,-1);
    vector<float> dist(n,INF_WT);
    dist[start] = 0;
    vector<bool> vis(n,false);

    priority_queue<pair<int,float>,vector<pair<int,float>>,CompareNodeDistPair> pq;
    pq.push(make_pair(start,0.0f));
    pair<int,float> pairIndexMinValue;

    while(!pq.empty())
    {
        pairIndexMinValue=pq.top();
        int index=pairIndexMinValue.first; // cout<<index<<", "; // uncomment to test dequed indexes dec or inc :)
        float minValue=pairIndexMinValue.second;
        pq.pop();

        if(!vis[index])
        {
            vis[index]=true;
            if(index == end)
                break;

            for(pair<int,float> e:g.getNeighbours(index))
            {
                if(vis[e.first])
                    continue;

                float newDist=dist[index]+e.second-potential(index,args)+potential(e.first,args); // CHANGE WITH POTENTIAL
                if(newDist<dist[e.first])
                {
                    prev[e.first]=index;
                    dist[e.first]=newDist;
                    pq.push(make_pair(e.first,newDist));
                }
            }
        }
    }

    // not reachable ...
    if(!vis[end])
        return make_pair(INF_WT,vector<int>());

    // post-processing
    // need to reconstruct min-dist from path , as we used potential too in Dijkstra ...
    vector<int> path;
    path.push_back(end);
    int last = end;
    float distance = 0;
    while(last != start)
    {
        distance+=g.getEdgeWeight(prev[last],last);
        path.push_back(last = prev[last]);
    }

    reverse(path.begin(),path.end());

    // return make_pair(dist[end],path);
    return make_pair(distance,path);
}

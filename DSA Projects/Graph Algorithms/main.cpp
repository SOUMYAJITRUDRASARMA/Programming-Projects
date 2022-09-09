#include "graph_weighted_adjacency_list.h"
#include "algorithms.h"

using namespace std;
using namespace std::chrono;

void f1()
{
    // Bidirectional Dijkstra Test

    GraphW g(9);

    g.addEdge(0,1,1);
    g.addEdge(1,2,1);
    g.addEdge(2,5,3);
    g.addEdge(5,6,3);
    g.addEdge(6,7,1);
    g.addEdge(7,8,1);
    g.addEdge(2,6,4);

    cout<<g<<endl<<endl;

    pair<float,vector<int>> p = BidirectionalDijkstra(g,0,8);
    cout<<"Min Dist: "<<p.first<<endl;
    cout<<"Path: "; for(int e:p.second) cout<<e<<"  "; cout<<endl;

    return;
}

float f2_GridPotentialFunction(int v, void *args)
{
    int *iPtr = (int *)args;
    int N_GRID = *iPtr;
    int row,col; row = v/N_GRID; col = v%N_GRID;
    row = N_GRID - row, col = N_GRID - col;

    // return sqrt(row*row + col*col);
    return (row*row + col*col); // better function ... | potential difference should be scaled larger than actual path distances ???
}

void f2()
{
    // A* Directed Search on a Grid System Test
    //  _ _     0 1 2
    // | | |
    //  _ _     3 4 5
    // | | |
    //  _ _     6 7 8
    //
    // for N_GRID = 3

    int N_GRID = 1000;

    GraphW g(N_GRID * N_GRID);

    // add down and next edges if they are within bounds
    for(int i=0;i<N_GRID * N_GRID;i++)
    {
        int row,col; row = i/N_GRID; col = i%N_GRID;
        if(row+1 < N_GRID)
            g.addBidirectionalEdge(i,i+N_GRID,1);
        if(col+1 < N_GRID)
            g.addBidirectionalEdge(i,i+1,1);
    }

    // cout<<g<<endl<<endl;

    auto start = high_resolution_clock::now();
    // pair<float,vector<int>> p = aStarDirectedSearch(g,0,N_GRID*N_GRID - 1);
    pair<float,vector<int>> p = aStarDirectedSearch(g,(N_GRID*N_GRID)/3,(N_GRID*N_GRID*2)/3);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout<<"DEFAULT DIJKSTRA -->"<<endl;
    cout<<"Min Dist: "<<p.first<<endl;
    // cout<<"Path: "; for(int e:p.second) cout<<e<<"  "; cout<<endl;
    cout<<"Time taken: "<<duration.count()<<" ms"<<endl<<endl;

    auto start2 = high_resolution_clock::now();
    // pair<float,vector<int>> p2 = aStarDirectedSearch(g,0,N_GRID*N_GRID - 1,f2_GridPotentialFunction,(void *)(&N_GRID));
    pair<float,vector<int>> p2 = aStarDirectedSearch(g,(N_GRID*N_GRID)/3,(N_GRID*N_GRID*2)/3,f2_GridPotentialFunction,(void *)(&N_GRID));
    auto stop2 = high_resolution_clock::now();
    auto duration2 = duration_cast<microseconds>(stop2 - start2);
    cout<<"A* DIRECTED SEARCH -->"<<endl;
    cout<<"Min Dist: "<<p2.first<<endl;
    // cout<<"Path: "; for(int e:p2.second) cout<<e<<"  "; cout<<endl;
    cout<<"Time taken: "<<duration2.count()<<" ms"<<endl<<endl;

    auto start3 = high_resolution_clock::now();
    // pair<float,vector<int>> p3 = BidirectionalDijkstra(g,0,N_GRID*N_GRID - 1);
    pair<float,vector<int>> p3 = BidirectionalDijkstra(g,(N_GRID*N_GRID)/3,(N_GRID*N_GRID*2)/3);
    auto stop3 = high_resolution_clock::now();
    auto duration3 = duration_cast<microseconds>(stop3 - start3);
    cout<<"BIDIRECTIONAL DIJKSTRA -->"<<endl;
    cout<<"Min Dist: "<<p3.first<<endl;
    // cout<<"Path: "; for(int e:p3.second) cout<<e<<"  "; cout<<endl;
    cout<<"Time taken: "<<duration3.count()<<" ms"<<endl<<endl; // MY BIDIRECTIONAL DIJKSTRA IS BUGGED , NEED TO OPTIMISE T-T // Computing gR costly , need to precompute ???

    return;
}

int main()
{
    f2();

    return 0;
}

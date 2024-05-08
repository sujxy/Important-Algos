#include<bits/stdc++.h>
#include <queue>
#include <utility>
using namespace std ;


vector<vector<int> > primsAlgo(int  mat[5][5] , int V ) {
    //priority queue //min heap
    priority_queue<vector<int> , vector<vector<int > > , greater<vector<int > > > pq;
    vector<int> visited(V ,0 ) ;
    vector<vector<int > > res;

    int minCost = 0 ;
    //element  : (weight , vertex , parent) =>

    pq.push({0, 0,-1}) ;

    while (!pq.empty()) {
        vector<int> top = pq.top() ;
        pq.pop() ;
        int u = top[1] ;
        int uw = top[0];
        int parent = top[2] ;

        if (visited[u]) continue;

        visited[u] = 1 ;
        minCost+=uw ;
        res.push_back({parent , u }) ;

        //for all neighbours
        for (int v = 0 ; v < V ; v++) {
            if (mat[u][v]  && !visited[v]) {
                int node = v ;
                int weight = mat[u][v] ;
                pq.push({weight,node ,u}) ;
            }
        }
    }
    cout << "cost : " << minCost <<endl ;
    return res;
}


int main() {
    int mat[5][5] = {
        {0,1,3,0,0} ,
        {1,0,0,5,0} ,
        {3,0,0,2,4} ,
        {0,5,2,0,7} ,
        {0,0,4,7,0}}  ;
    //prims
    vector<vector<int> > res ;
    res = primsAlgo(mat, 5) ;

    for (int i = 1 ; i < res.size() ; i++) {
        cout << res[i][0] << "=>" << res[i][1] <<endl ;

    }


    return 0 ;
}

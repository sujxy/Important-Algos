#include<bits/stdc++.h>
using namespace std ;

void dijkstraAlgo(vector<int> & dist ,int mat[5][5] ,int V  ) {

    priority_queue<pair<int,int> , vector<pair<int,int> > , greater<pair<int,int> > > pq ;
    //start push => {dist , start_vertex}
    pq.push({0,0}) ;
    dist[0] = 0 ;
    while (!pq.empty()) {
        int u = pq.top().second ;
        int u_dist = pq.top().first ;
        pq.pop() ;

        //check all neghbours and update dist if possible
        for (int i = 0 ; i < V ; i++) {
            //if neighbour
            if (mat[u][i] ) {
                int v = i ;
                int v_weight = mat[u][i] ;
                //if dist from u to v is less than dist[v] update dist[v]
                if (u_dist + v_weight < dist[v]) {
                    dist[v] = u_dist + v_weight ;
                    pq.push({dist[v] , v}) ;
                }
            }
        }
    }
}

int main() {
    int mat[5][5] = {
        {0,1,3,0,0} ,
        {1,0,0,5,0} ,
        {3,0,0,2,4} ,
        {0,5,2,0,7} ,
        {0,0,4,7,0}}  ;

    //dijkstras
    vector<int> dist(5 , INT_MAX) ;
    dijkstraAlgo(dist , mat , 5 ) ;
    for(int i = 0 ; i < dist.size() ; i++) {
        cout << "vertex: " << i << "-> distance: "<<dist[i] <<endl ;
    }
    return 0 ;
}

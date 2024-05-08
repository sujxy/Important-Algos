#include<iostream>
#include <utility>
using namespace std ;

class DisjointSet {
    vector<int> rank , parent ;
    int N ;
    public :
    DisjointSet(int n )  : N(n){
        rank.resize(N+1 , 0 ) ; //initial rank 0 of all
        parent.resize(N+1) ; //to store each node's parent
        for (int i = 0 ; i <= N ; i++) {
            parent[i] = i ; //assign each node as parent to itself
        }
    }

    //find parent of given node
    int findParent(int node) {
        if (node == parent[node]) {
            return node ;
        }
        return parent[node] = findParent(parent[node]) ;
    }

    //creaate union of two dijoint nodes by using rank disjiont->component
    void unionByRank(int u , int v) {
        //find ultimate parent
        int up_u = findParent(u) ;
        int up_v = findParent(v) ;
        //if has same parent , then already disjoint & no union
        if (up_u == up_v) return ;
        //join parents on basis of rank
        if (rank[up_u] < rank[up_v]) {
            parent[up_u] = up_v ;
        }
        else if (rank[up_u] > rank[up_v]) {
            parent[up_v] = up_u ;
        }
        else  {
            parent[up_v] = up_u ;
            rank[up_u]++ ;
        }
    }
} ;

void kruskalsAlgo(int& minCost , int adjMat[5][5] , int N) {
    // pair : { weight , { u , v} }
    vector<pair<int , pair<int , int > > > edges ;
    for (int u = 0 ; u < N ; u++) {
        for (int v = 0 ; v < N ; v++) {
            if (adjMat[u][v]) edges.push_back({adjMat[u][v] , {u , v }}) ;
        }
    }
    //sort edges for minimum at front
    sort(edges.begin() , edges.end()) ;
   //a data structure to track if new node is in same component
    DisjointSet ds(N) ;

    for (auto itr : edges ) {
        int w = itr.first ;
        int u = itr.second.first ;
        int v = itr.second.second ;

        if (ds.findParent(u) != ds.findParent(v)) {
            //u & v(new) belong to disjoint set so we can include in mst
            minCost += w ;
            ds.unionByRank(u,v) ; //combine u & v to make union set
        }
        //else both are in same component & cannot we added to mst
    }

}

int main() {
    int adjMat[5][5] = {
        {0,1,3,0,0} ,
        {1,0,0,5,0} ,
        {3,0,0,2,4} ,
        {0,5,2,0,7} ,
        {0,0,4,7,0}
    } ;
    int N = 5 ;
    int res = 0 ;
    kruskalsAlgo(res , adjMat , N) ;
    cout << "minimum cost : " << res << endl ;
}

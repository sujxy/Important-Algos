#include<iostream>
#include<utility>
using namespace std ;

int findMinimum(vector<int> cost , vector<int> visited) {
    int minimum = INT_MAX , minNode ;
    for (int u = 0 ; u < cost.size() ; u++) {
        if (!visited[u] && cost[u] < minimum) {
            minimum = cost[u]  ;
            minNode = u ;
        }
    }
    //return min cost node
    return minNode ;
}

void findPrimsMst(vector<int> & parent ,vector<int> & visited , vector<int> & cost ,int adjMat[5][5] , int V  ) {
    //initiation
    cost[0] = 0 ;

    for(int i = 0 ; i < V ; i++) {
        //find minimum node
        int u = findMinimum(cost , visited) ;
        //include in mst
        visited[u] = 1 ;
        //check neighbours and update cost if lower cost neighbour is found
        for (int v = 0 ; v < V ; v++) {
            if (adjMat[u][v] && !visited[v] && adjMat[u][v] < cost[v] ) {
                //a neighbour ,not visited(not in mst) , lower cost than previous
                cost[v] = adjMat[u][v] ;
                parent[v] = u ;
            }
        }
    }
}

int main() {
    int V = 5 ;
    int mat[5][5] = {
        {0,1,3,0,0} ,
        {1,0,0,5,0} ,
        {3,0,0,2,4} ,
        {0,5,2,0,7} ,
        {0,0,4,7,0}}  ;

    vector<int> parent(V , -1) ;
    vector<int> visited(V , 0 ) ;
    vector<int> cost(V,INT_MAX) ;

    findPrimsMst(parent , visited ,cost , mat , V) ;

    cout <<" minimum cost : " ;
    int sum = 0;
    for (int i = 0 ; i < cost.size() ; i++) {
        sum+=cost[i] ;
    }
    cout << sum << endl ;

    return 0 ;
}

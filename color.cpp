#include<iostream>
#include<vector>
using namespace std ;

bool isSafe(int currentColor , int vertex , vector<int> colors , int adjMat[5][5] , int N) {
    //for all neighbours check if it has same color
    for (int n = 0 ; n < N ; n++) {
        if (n != vertex && adjMat[n][vertex] == 1 && colors[n] == currentColor) return false ;
    }
    return true ;
}

bool fillColor(int vertex ,int totalColors, vector<int> & colors , int adjMat[5][5] , int N){
    if (vertex == N) {
        return true ;
    }

    //for all colors
    for (int col = 1 ; col <= totalColors ; col++ ) {
        if (isSafe(col , vertex , colors , adjMat , N)) {
            colors[vertex] = col ;
            //try for next vertex
            if (fillColor(vertex+1 , totalColors , colors , adjMat ,N) == true)  return true ;
            colors[vertex] = 0 ;
        }
    }
    //no color possible
    return false ;
}

int main() {
    int N = 5 ;
    int adjMat[5][5] = {
        {0,1,0,0,1},
        {1,0,1,0,0},
        {0,1,0,1,0},
        {0,0,1,0,1},
        {1,0,0,1,0}
    } ;
    bool flag  ;
    vector<int> colors(N,0) ;
    flag = fillColor(0, 3 ,colors,adjMat,N) ;

    if (flag) {
        cout << "vertex\tcolor"  <<endl;
        for (int i = 0 ; i < colors.size() ; i++) {
            cout << i << "\t" << colors[i] <<endl ;
        }
    }
    else {
        cout << "coloring not possible with provided colors. " <<endl ;
    }

}

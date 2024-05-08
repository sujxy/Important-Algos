#include<bits/stdc++.h>
using namespace std ;


class Graph {
    private:
        int vertex , edges ;
        int** adjMat ;
  public :

    Graph(int v , int e) : vertex(v) , edges(e) {
        adjMat = new int*[vertex] ;
        for (int i = 0 ; i < vertex ; i++) {
            adjMat[i] = new int[vertex] ;
            for (int j = 0 ; j < vertex ; j++) {
                adjMat[i][j] = 0 ;
            }
        }
    }

    void addEdge(int u,int v , int w = 1 ) {
        this->adjMat[u][v] = w ;
        this->adjMat[v][u] = w ;
    }

    void removeEdge(int u , int v) {
        this->adjMat[u][v] = 0  ;
        this->adjMat[v][u] = 0 ;
    }

    void display() {
        for (int i = 0 ; i < vertex ; i++) {
            cout << i << "->" ;
            for (int j = 0 ; j < vertex ; j++) {
                if (this->adjMat[i][j] == 1) {
                    cout << j << "," ;
                }
            }
            cout << '\n' ;
        }
    }

    void dfsHelper(int u , int visited[]) {
        cout << u << "->" ;
        visited[u] = 1 ;
        //for all neighbours that ar un-visited
        for (int v = 0 ; v < vertex ; v++) {
            if (this->adjMat[u][v] == 1 && !visited[v] ){
                dfsHelper(v, visited) ;
            }
        }
    }

    void getDFS() {
        int* visited = new int[vertex] ;
        dfsHelper(0 , visited ) ;
        cout << "x" <<endl ;
    }

    void bfsHelper( int visited[] , queue<int>& q) {
        if (q.empty()) return ;
        int front = q.front() ;
        q.pop() ;

        for (int v = 0 ; v < vertex ; v++) {
            if (this->adjMat[front][v] ==1 && !visited[v]) {
                cout << v << "->" ;
                visited[v] = 1 ;
                q.push(v) ;
            }
        }
        //now call recursion with new queeu
        bfsHelper(visited ,q) ;

    }

    void getBFS() {
        int *visited = new int[vertex] ;
        queue<int> q ;
        q.push(0) ;
        cout << 0 << "->" ;
        visited[0] = 1 ;
        bfsHelper( visited , q) ;
        cout << "x" <<endl ;

    }

    void dfsNonRecursive() {
        stack<int> stk ;
        int* visited = new int[this->vertex] ;
        stk.push(0) ;
        while (!stk.empty()) {
            int front = stk.top() ;
            stk.pop() ;
            cout <<front<<"->" ;
            visited[front] = 1 ;
            for (int v = this->vertex-1 ; v >=0  ; v--) {
                if (this->adjMat[front][v] == 1 && !visited[v] ) {
                    stk.push(v) ;
                }
            }
        }
        cout << 'x' << endl ;
    }

    void bfsNonRecursive() {
        int * visited = new int[this->vertex] ;
        queue<int> q ;
        //starrt node
        cout<< 0 << "->" ;
        visited[0] = true ;
        q.push(0) ;
        while (!q.empty()) {
            int front = q.front() ;
            q.pop();
            for (int v = 0 ; v < this->vertex ; v++) {
                if (this->adjMat[front][v] == 1 && !visited[v]) {
                    cout << v << "->" ;
                    visited[v] = 1 ;
                    q.push(v) ;
                }
            }
        }
        cout << 'x' << endl ;
    }


};

int main() {
    Graph g1(7,6) ;
    g1.addEdge(0, 1) ;
    g1.addEdge(0, 2) ;
    g1.addEdge(0, 3) ;
    g1.addEdge(2, 4) ;
    g1.addEdge(2, 5) ;
    g1.addEdge(4, 6) ;
    //display
    g1.display();

    cout << "dfs = " ;
    g1.getDFS();
    cout << "dfs (recursive) => " ;
    g1.dfsNonRecursive();

    cout << "bfs = "  ;
    g1.getBFS();
    cout << "bfs (recursive) => " ;
    g1.bfsNonRecursive();

    return 0 ;
}

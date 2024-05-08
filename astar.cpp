#include<iostream>
#include<utility>
#include<queue>
#include<set>
using namespace std  ;

//size of puzzle
const int n = 3 ;

//puzzle state for eact move
struct PuzzleState {
    int puzzle[n][n]  ;
    int g , h ;
    int zeroRow,zeroCol ;

    bool operator<( const PuzzleState& p2) const {
        //calc: f = g + h
        //this is for priority q's default lessthan function
        //this will help to create min heap of smallest f value
        return (g + h) > (p2.g + p2.h) ;
    }
};

int calculateManhattenDistance( PuzzleState  currentState) {
    //manhatten dist => row,col displacement of curr state from goal state
    int dist = 0 ;
    //correct row,col for a cell-val is r = val/n , col = val%n
    for (int i = 0 ; i < n ; i++) {
        for (int j =0 ; j< n ; j++) {
            if (currentState.puzzle[i][j] != 0 ) {
                int val = currentState.puzzle[i][j] ;
                int rowDisp = abs( ((val-1)/n) - i ) ;
                int colDisp = abs( ((val-1)%n) - j ) ;
                dist += rowDisp + colDisp ;
            }
        }
    }

    return dist ;
}

bool isEqual(PuzzleState current , PuzzleState final ) {
    for (int i = 0 ; i < n ; i++) {
        for (int j = 0 ; j< n ; j++) {
            if (current.puzzle[i][j] != final.puzzle[i][j] ) return false ;
        }
    }
    return true ;
}

//generate possbile successor states
vector<PuzzleState> generateSuccessorStates(const PuzzleState& current) {
    vector<PuzzleState> successorStates ;
    int directions[4][2] = {{0,-1} , {0 , 1} , {-1 , 0} , {1 , 0}} ;  //left ,right , up , down

    //for all possible directions
    for (int i = 0 ; i < 4 ; i++) {
        //make possible moves
        int nextZeroRow = current.zeroRow+directions[i][0] ;
        int nextZeroCol = current.zeroCol+directions[i][1] ;
        //check validity of moves
        if (nextZeroRow >= 0 && nextZeroRow<n && nextZeroCol >= 0 && nextZeroCol<n ) {
             PuzzleState newState = current ;
             //swap vals in successor puzzle :
             swap(newState.puzzle[current.zeroRow][current.zeroCol] , newState.puzzle[nextZeroRow][nextZeroCol]);
             newState.zeroRow = nextZeroRow ;
             newState.zeroCol = nextZeroCol ;
             newState.g = current.g +  1 ;
             newState.h = calculateManhattenDistance(newState) ;
             successorStates.push_back(newState) ;
        }

    }
    return successorStates ;
}

//display a state of puzzle
void displayPuzzle(const PuzzleState& puzzle) {
    cout << endl ;
    for (int i = 0 ; i < n ; i++) {
        for (int j = 0 ; j < n ; j++){
            cout << puzzle.puzzle[i][j] << " " ;
        }
        cout << endl ;
     }
     cout << endl ;
     cout << "distance from start [moves] : " << puzzle.g << endl ;
     cout << "distance from goal [heuristic] : " << puzzle.h << endl ;
     cout << "---------------------------------" << endl ;
}

//main algorithm code
void astarSearch(const PuzzleState &initial ,const  PuzzleState &final ) {
    priority_queue<PuzzleState > queue ;
    set<int> visited ;
    //starting state :
    queue.push(initial) ;

    while (!queue.empty()) {
        PuzzleState currentState = queue.top() ;
        queue.pop() ;

        cout << "current state  :" << endl ;
        displayPuzzle(currentState) ;

        if (isEqual(currentState , final)) {
            cout << "reached goal state ! " << endl ;
            break ;
        }

        //not the goal state, then generate successor/possible states & push to Q
        vector<PuzzleState> successorStates= generateSuccessorStates(currentState) ;
        //push successor states to queue
        for (const PuzzleState& successor : successorStates) {
            int hash = 0 ;
            for (int i = 0 ; i < n ; i++) {
                for (int j = 0 ; j < n ; j++){
                    hash += hash*10 +  successor.puzzle[i][j] ;
                }
             }
             if (visited.find(hash) == visited.end() ){
                 //sollution unvisited
                  queue.push(successor) ;
                  visited.insert(hash) ;
             }

        }
    }
}


//generate new puzzle
PuzzleState getNewPuzzle() {
    PuzzleState newPuzzle ;
    cout << "enter values in (row,col) " << endl ;
    for (int i = 0 ; i < n ; i++) {
        for (int j = 0 ; j < n ; j++) {
            cout << "enter cell (" << i << "," << j << ") : " ;
            cin >> newPuzzle.puzzle[i][j]  ;
            //if the cell is 0-cell ,store pos
            if (newPuzzle.puzzle[i][j] == 0 ) {
                newPuzzle.zeroRow = i ;
                newPuzzle.zeroCol = j ;
            }
        }
    }
    newPuzzle.g = 0 ;
    newPuzzle.h = calculateManhattenDistance(newPuzzle) ;
    return newPuzzle ;
}

int main() {

    PuzzleState initialState = getNewPuzzle() ;
    PuzzleState finalState = getNewPuzzle() ;
    astarSearch(initialState, finalState) ;
    return 0 ;
}

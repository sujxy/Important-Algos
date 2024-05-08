#include<bits/stdc++.h>
using namespace std ;


bool isValid(int row , int col ,vector<vector<int> >  board,int n ){
    int duprow = row ;
    int dupcol = col ;
    //for upper diagonal
    while (row >= 0 && col >= 0 ) {
        if (board[row][col] == 1) return false ;
        row-- ;
        col-- ;
    }
    //for lower diagonal
    row = duprow ;
    col = dupcol ;
    while (row < n && col >= 0 ) {
        if (board[row][col] == 1) return false ;
        row++ ;
        col-- ;
    }
    //for left row
    row = duprow ;
    col = dupcol ;
    while ( col >= 0 ) {
        if (board[row][col] == 1) return false ;
        col-- ;
    }

    //elese safe
    return true ;
}

void placeQueen(int col ,vector<vector<vector<int> > > & ans,vector<vector<int> > & board,int n ) {
    if (col == n ) {
        ans.push_back(board) ;
        return ;
    }

    for (int row = 0 ; row < n ; row++) {
        if (isValid(row, col ,board , n)) {
            board[row][col] = 1 ;
            placeQueen(col+1 , ans , board , n ) ;
            board[row][col] = 0 ;
        }
    }
}

void placeQueenBetter(int col ,vector<int> & leftRow ,vector<int> & leftLower , vector<int> & leftUpper ,   vector<vector<vector<int> > > &ans , vector<vector<int> > &board , int n )
{
    if (col == n ) {
        ans.push_back(board) ;
        return ;
    }

    for (int row = 0 ; row < n ; row++) {
        if (!leftRow[row] && !leftLower[row+col] && !leftUpper[(n-1) + (row-col)]) {
            leftRow[row] = 1;
            leftLower[row+col] = 1 ;
            leftUpper[(n-1) + (row-col) ] = 1 ;
            board[row][col] = 1 ;
            placeQueenBetter(col+1, leftRow, leftLower,leftUpper, ans, board, n) ;
            leftRow[row] = 0;
            leftLower[row+col] = 0;
            leftUpper[(n-1) + (row-col) ] = 0;
            board[row][col] = 0 ;
        }
    }
}
int main() {
    int n = 4 ;
    vector<vector<int> > board(n ,vector<int>(n,0) ) ;
    vector<vector<vector<int> > >  ans ;
    //app 1
    //placeQueen( 0 , ans , board , n ) ;
    //approach 2
    vector<int> leftRow(n,0) ;
    vector<int> leftLower(2*n-1,0) ;
    vector<int> leftUpper(2*n-1,0) ;
    //app 2
    placeQueenBetter(0,leftRow, leftLower,leftUpper, ans, board, n ) ;
    for (int i = 0 ; i < ans.size() ; i++)  {
        cout << "solution "<< i+1 << ":"<<endl ;
        for (int j = 0 ; j < n ; j++) {
            for (int k = 0 ; k < n ; k++) {
                cout << ans[i][j][k] << " " ;
            }
            cout << endl ;
        }
    }
}

#include<iostream>
using namespace std ;

void selectionSort(int arr[] , int n) {
    for (int i = 0 ; i < n ; i++) {
        int min = arr[i] ;
        int minIndex = i ;
        for (int j = i+1 ; j < n ; j++) {
            if (arr[j] < min) {
                min = arr[j] ;
                minIndex = j ;
            }
        }
        swap(arr[i] , arr[minIndex]) ;
    }
}

int main() {
    int arr[] = {9,8,7,6,1,2,3} ;
    int n = sizeof(arr) / 4 ;
    selectionSort(arr , n) ;
    cout << "sorted array : " ;
    for (int i = 0 ; i < n ; i++) {
        cout << arr[i] << " " ;
    }
    return 0 ;
}

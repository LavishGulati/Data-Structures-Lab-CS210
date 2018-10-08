#include <bits/stdc++.h>
using namespace std;

template <class dataType> void printArray(dataType *input, int n){
    for(int i = 0; i < n; i++) cout << input[i] << " ";
    cout << endl;
}

template <class dataType> void swap(dataType *input, int i, int j){
    dataType temp = input[i];
    input[i] = input[j];
    input[j] = temp;
}

template <class dataType> void insertionSort(dataType *input, int n){
    for(int i = 1; i < n; i++){
        int j;
        for(j = i-1; j >= 0; j--){
            if(input[j] <= input[i]) break;
        }

        if(j != i-1){
            int temp = input[i];
            for(int k = i-1; k > j; k--){
                input[k+1] = input[k];
            }
            input[j+1] = temp;
        }

        // printArray(input, n);
    }
}

int main(){
    int input[8] = {12, 6, 4, 9,14,43,42,3};
    printArray(input, 8);

    insertionSort(input, 8);
    printArray(input, 8);
}

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

template <class dataType> void bubbleSort(dataType *input, int n){
    for(int i = n-1; i > 0; i--){
        for(int j = 0; j < i; j++){
            if(input[j] > input[j+1]){
                swap(input, j, j+1);
            }
        }
    }
}

int main(){
    int input[8] = {12, 6, 4, 9,14,43,42,3};
    printArray(input, 8);

    bubbleSort(input, 8);
    printArray(input, 8);
}

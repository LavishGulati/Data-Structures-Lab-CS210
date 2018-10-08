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

template <class dataType> void selectionSort(dataType *input, int n){
    for(int i = 0; i < n-1; i++){
        int minId = i;
        for(int j = i+1; j < n; j++){
            if(input[j] < input[minId]) minId = j;
        }
        if(i != minId) swap(input, i, minId);
        // printArray(input, n);
    }
}

int main(){
    int input[8] = {12, 6, 4, 9,14,43,42,3};
    printArray(input, 8);

    selectionSort(input, 8);
    printArray(input, 8);
}

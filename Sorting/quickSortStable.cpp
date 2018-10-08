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

template <class dataType> void quickSort(dataType *input, int si, int ei){
    if(si >= ei) return;

    int *helper = new int[ei-si+1];
    int id = 0;
    for(int i = si+1; i <= ei; i++){
        if(input[i] < input[si]){
            helper[id] = input[i];
            id++;
        }
    }

    int pivotId = id;
    helper[id] = input[si];
    id++;

    for(int i = si+1; i <= ei; i++){
        if(input[i] >= input[si]){
            helper[id] = input[i];
            id++;
        }
    }

    for(int i = 0; i <= ei-si; i++){
        input[si+i] = helper[i];
    }

    quickSort(input, si, si+pivotId-1);
    quickSort(input, si+pivotId+1, ei);
}

template <class dataType> void quickSort(dataType *input, int n){
    quickSort(input, 0, n-1);
}

int main(){
    int input[8] = {12, 6, 4, 9,14,43,42,3};
    printArray(input, 8);

    quickSort(input, 8);
    printArray(input, 8);
}

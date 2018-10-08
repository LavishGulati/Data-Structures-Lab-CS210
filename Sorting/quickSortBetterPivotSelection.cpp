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

    srand(time(0));
    int pivotId = rand()%(ei-si+1) + si;

    int smallCount = 0;
    for(int i = si; i <= ei; i++){
        if(input[i] < input[pivotId]) smallCount++;
    }

    swap(input, pivotId, si+smallCount);
    pivotId = si+smallCount;

    int i = si;
    int j = ei;
    while(i < pivotId){
        if(input[i] >= input[pivotId]){
            while(1){
                if(input[j] < input[pivotId]) break;
                j--;
            }
            swap(input, i, j);
        }
        i++;
    }

    quickSort(input, si, si+smallCount-1);
    quickSort(input, si+smallCount+1, ei);
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

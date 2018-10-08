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

template <class dataType> void partition(dataType *input, int si, int ei, int &pivotId1, int &pivotId2){
    pivotId1 = si;
    pivotId2 = ei;

    if(input[pivotId1] > input[pivotId2]) swap(input, pivotId1, pivotId2);

    int i = si+1;
    int j = ei-1;
    int k = si+1;
    while(k <= j){
        if(input[k] < input[pivotId1]){
            swap(input, i, k);
            i++;
        }
        else if(input[k] >= input[pivotId2]){
            while(input[j] >= input[pivotId2] && k < j) j--;

            swap(input, j, k);
            j--;

            if(input[k] < input[pivotId1]){
                swap(input, i, k);
                i++;
            }
        }

        k++;
    }

    i--;
    j++;

    swap(input, si, i);
    swap(input, ei, j);

    pivotId1 = i;
    pivotId2 = j;
}

template <class dataType> void quickSort(dataType *input, int si, int ei){
    if(si >= ei) return;

    int pivotId1, pivotId2;

    partition(input, si, ei, pivotId1, pivotId2);

    quickSort(input, si, pivotId1-1);
    quickSort(input, pivotId1+1, pivotId2-1);
    quickSort(input, pivotId2+1, ei);
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

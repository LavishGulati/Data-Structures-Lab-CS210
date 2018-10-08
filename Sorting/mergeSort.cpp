#include <bits/stdc++.h>
using namespace std;

template <class dataType> void printArray(dataType *input, int n){
    for(int i = 0; i < n; i++) cout << input[i] << " ";
    cout << endl;
}

template <class dataType> void merge(dataType *input, int si, int mid, int ei){
    int *helper = new int[ei-si+1];

    int i = si;
    int j = mid+1;
    int k = 0;
    while(i <= mid && j <= ei){
        if(input[i] <= input[j]){
            helper[k] = input[i];
            i++; k++;
        }
        else{
            helper[k] = input[j];
            j++; k++;
        }
    }

    while(i <= mid){
        helper[k] = input[i];
        i++; k++;
    }

    while(j <= ei){
        helper[k] = input[j];
        j++; k++;
    }

    for(k = 0; k <= ei-si; k++){
        input[si+k] = helper[k];
    }

    delete[] helper;
}

template <class dataType> void mergeSort(dataType *input, int si, int ei){
    if(si >= ei) return;

    int mid = (si+ei)/2;
    mergeSort(input, si, mid);
    mergeSort(input, mid+1, ei);

    merge(input, si, mid, ei);
}

template <class dataType> void mergeSort(dataType *input, int n){
    mergeSort(input, 0, n-1);
}

int main(){
    int input[8] = {12, 6, 4, 9,14,43,42,3};
    printArray(input, 8);

    mergeSort(input, 8);
    printArray(input, 8);
}

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

template <class dataType> void mergeSort(dataType *input, int si, int ei, int partSize){
    if(si >= ei) return;

    if(ei-si+1 <= partSize){
        insertionSort(input+si, ei-si+1);
        return;
    }

    int mid = (si+ei)/2;
    mergeSort(input, si, mid, partSize);
    mergeSort(input, mid+1, ei, partSize);

    merge(input, si, mid, ei);
}

template <class dataType> void mergeSort(dataType *input, int n, int partSize){
    mergeSort(input, 0, n-1, partSize);
}

int main(){
    int input[8] = {12, 6, 4, 9,14,43,42,3};
    int partSize = 3;

    printArray(input, 8);

    mergeSort(input, 8, partSize);
    printArray(input, 8);
}

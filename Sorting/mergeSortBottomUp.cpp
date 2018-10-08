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

template <class dataType> void mergeSort(dataType *input, int n){
    for(int m = 1; m < n; m *= 2){
        for(int si = 0; si < n-1; si += 2*m){
            int mid = si+m-1;
            int ei = min(si + 2*m - 1, n-1);

            merge(input, si, mid, ei);
        }
    }
}

int main(){
    int input[8] = {12, 6, 4, 9,14,43,42,3};
    // int input[1] = {1};
    // int input[2] = {2,1};
    // int input[3] = {2,1,3};
    // int input[4] = {1,4,3,2};
    // int input[5] = {5,4,3,2,1};
    // int input[6] = {6,4,2,5,3,1};
    // int input[7] = {7,5,4,3,2,1,6};
    int n = 8;
    printArray(input, n);

    mergeSort(input, n);
    printArray(input, n);
}

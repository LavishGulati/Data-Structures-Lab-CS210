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

template <class dataType> void quickSort(dataType *input, int si, int ei, int partSize){
    if(si >= ei) return;

    if(ei-si+1 <= partSize){
        insertionSort(input+si, ei-si+1);
        return;
    }

    int smallCount = 0;
    for(int i = si+1; i <= ei; i++){
        if(input[i] < input[si]) smallCount++;
    }

    swap(input, si, si+smallCount);

    int i = si;
    int j = ei;
    while(i < si+smallCount){
        if(input[i] >= input[si+smallCount]){
            while(1){
                if(input[j] < input[si+smallCount]) break;
                j--;
            }
            swap(input, i, j);
        }
        i++;
    }

    quickSort(input, si, si+smallCount-1, partSize);
    quickSort(input, si+smallCount+1, ei, partSize);
}

template <class dataType> void quickSort(dataType *input, int n, int partSize){
    quickSort(input, 0, n-1, partSize);
}

int main(){
    int input[8] = {12, 6, 4, 9,14,43,42,3};
    int partSize = 3;

    printArray(input, 8);

    quickSort(input, 8, partSize);
    printArray(input, 8);
}

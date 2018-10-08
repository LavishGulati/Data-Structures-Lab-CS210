#include <bits/stdc++.h>
using namespace std;

void printList(int *input, int n){
    for(int i = 0; i < n; i++){
        // cout << input[i] << " ";
        cout << input[i] << endl;
    }
    // cout << endl;
}

void kWayMerging(int *input, int si, int ei, int m, int k){
    int *id = new int[k];
    for(int i = 0; i < k; i++){
        id[i] = si + i*m;
    }

    int *helper = new int[ei-si+1];

    for(int j = 0; j <= ei-si; j++){

        int minId = -1;
        for(int i = 0; i < k; i++){
            if(id[i] < min(si+(i+1)*m, ei+1)){
                if(minId == -1 || input[id[i]] < input[id[minId]]) minId = i;
            }
        }

        helper[j] = input[id[minId]];
        id[minId]++;
    }

    // cout << "Printing sorted array from " << si << " to " << ei << ": ";
    // printList(helper, ei-si+1);

    for(int i = 0; i <= ei-si; i++){
        input[si+i] = helper[i];
    }
}

void mergeSort(int *input, int n, int k, int iteration){
    for(int m = 1; m < n && iteration != 0; m *= k){

        for(int si = 0; si < n; si += m*k){
            int ei = min(n-1, si+m*k-1);
            kWayMerging(input, si, ei, m, k);
        }

        iteration--;
    }
}

int main(){
    int k, iteration, n;
    cin >> k >> iteration >> n;

    int *input = new int[n];
    for(int i = 0; i < n; i++) cin >> input[i];

    mergeSort(input, n, k, iteration);

    printList(input, n);
}

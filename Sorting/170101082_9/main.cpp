#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>

void printList(int *input, int n){
    for(int i = 0; i < n; i++){
        cout << input[i] << endl;
    }
}

void kWayMerging(int *input, int si, int ei, int m, int k){
    priority_queue< pii, vector<pii>, greater<pii> > pq;

    int *id = new int[k];
    for(int i = 0; i < k; i++){
        id[i] = si + i*m;
        if(id[i] < min(si+(i+1)*m, ei+1)){
            pq.push(make_pair(input[id[i]], i));
        }
    }

    int *helper = new int[ei-si+1];

    for(int j = 0; j <= ei-si; j++){

        pii minNode = pq.top();
        pq.pop();

        int i = minNode.second;

        helper[j] = minNode.first;
        id[i]++;

        if(id[i] < min(si+(i+1)*m, ei+1)){
            pq.push(make_pair(input[id[i]], i));
        }
    }

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

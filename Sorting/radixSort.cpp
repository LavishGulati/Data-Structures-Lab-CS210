#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define pb push_back

void printList(int *input, int n){
    for(int i = 0; i < n; i++) cout << input[i] << " ";
    cout << endl;
}

void radixSort(int *input, int n, int d){
    for(int i = 0; i < d; i++){
        vector<int> *helper = new vector<int>[10];

        for(int j = 0; j < n; j++){
            int id = (input[j]/(int(pow(10, i))))%10;
            helper[id].pb(input[j]);
        }

        int id = 0;
        for(int j = 0; j < 10; j++){
            for(int k = 0; k < helper[j].size(); k++){
                input[id] = helper[j][k];
                id++;
            }
        }
    }
}

int main(){
    int n;
    cin >> n;

    int *input = new int[n];
    for(int i = 0; i < n; i++) cin >> input[i];

    radixSort(input, n, 3);

    printList(input, n);
}

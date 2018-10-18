#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define pb push_back

void printList(int *input, int n){
    for(int i = 0; i < n; i++) cout << input[i] << " ";
    cout << endl;
}

void countingSort(int *input, int n, int range){
    int *helper = new int[range];
    for(int i = 0; i < range; i++) helper[i] = 0;

    for(int i = 0; i < n; i++) helper[input[i]]++;
    for(int i = 1; i < range; i++) helper[i] += helper[i-1];

    // printList(helper, range);

    int *output = new int[n];
    for(int i = 0; i < n; i++){
        helper[input[i]]--;
        output[helper[input[i]]] = input[i];
    }

    for(int i = 0; i < n; i++) input[i] = output[i];

    delete[] output;
    delete[] helper;
}

int main(){
    int n;
    cin >> n;

    int *input = new int[n];
    for(int i = 0; i < n; i++) cin >> input[i];

    countingSort(input, n, 10);

    printList(input, n);
}

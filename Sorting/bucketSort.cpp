#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unordered_map<int, int> umapii;
typedef unordered_map<int, bool> umapib;
typedef map<string, int> mapsi;
typedef map<pair<int, int>, int> mappiii;

#define it iterator
#define mp make_pair
#define pb push_back
#define all(x) (x).begin(), (x).end()

void printList(double *input, int n){
    for(int i = 0; i < n; i++) cout << input[i] << " ";
    cout << endl;
}

void bucketSort(double *input, int n){
    vector<double> *helper = new vector<double>[10];
    for(int i = 0; i < n; i++){
        int id = int(input[i]*10);
        helper[id].pb(input[i]);
    }

    for(int i = 0; i < 10; i++) sort(all(helper[i]));

    int id = 0;
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < helper[i].size(); j++){
            input[id] = helper[i][j];
            id++;
        }
    }
}

int main(){
    int n;
    cin >> n;

    double *input = new double[n];
    for(int i = 0; i < n; i++) cin >> input[i];

    bucketSort(input, n);

    printList(input, n);
}

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unordered_map<int, int> umapii;
typedef unordered_map<int, bool> umapib;
typedef unordered_map<string, int> umapsi;
typedef unordered_map<string, string> umapss;
typedef map<string, int> mapsi;
typedef map<pair<int, int>, int> mappiii;
typedef map<int, int> mapii;
typedef pair<int, int> pii;

#define it iterator
#define mp make_pair
#define pb push_back
#define all(x) (x).begin(), (x).end()

bool compare(pii a, pii b){
    if(a.second < b.second) return true;
    else if(a.second > b.second) return false;
    else{
        if(a.first < b.first) return true;
        else return false;
    }
}

int main(){
    int n;
    cin >> n;

    pii *input = new pii[n];
    int t, d;
    for(int i = 0; i < n; i++){
        cin >> t >> d;
        input[i] = mp(i+1, t+d);
    }

    sort(input, input+n, compare);

    for(int i = 0; i < n; i++) cout << input[i].first << " ";
    cout << endl;
}

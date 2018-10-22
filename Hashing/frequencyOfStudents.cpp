#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define pb push_back
typedef unordered_map<int, int> umapii;
typedef unordered_map<int, bool> umapib;
typedef map<string, int> mapsi;
#define it iterator

int main(){
    int n;
    cin >> n;

    mapsi m;
    string s;
    for(int i = 0; i < n; i++){
        cin >> s;
        m[s]++;
    }

    mapsi::it i = m.begin();
    while(i != m.end()){
        cout << i->first << " " << i->second << endl;
        i++;
    }
}

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

int main(){
    int n;
    cin >> n;

    mappiii m;
    int x, y;
    for(int i = 0; i < n; i++){
        cin >> x >> y;
        m[mp(x, y)]++;
    }

    mappiii::it i = m.begin();
    while(i != m.end()){
        cout << (i->first).first << " " << (i->first).second << " " << i->second << endl;
        i++;
    }
}

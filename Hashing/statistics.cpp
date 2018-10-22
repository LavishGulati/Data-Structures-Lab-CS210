#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unordered_map<int, int> umapii;
typedef unordered_map<int, bool> umapib;
typedef unordered_map<string, int> umapsi;
typedef unordered_map<string, string> umapss;
typedef map<string, int> mapsi;
typedef map<pair<int, int>, int> mappiii;

#define it iterator
#define mp make_pair
#define pb push_back
#define all(x) (x).begin(), (x).end()

int main(){
    umapss m1;
    mapsi m2;

    int n;
    cin >> n;
    string name, sport;
    for(int i = 0; i < n; i++){
        cin >> name >> sport;
        if(m1.find(name) == m1.end()){
            m1[name] = sport;
            m2[sport]++;
        }
    }

    mapsi::it i = m2.begin();
    string mostpopular;
    int maxLike = 0;
    while(i != m2.end()){
        if(i->second > maxLike){
            mostpopular = i->first;
            maxLike = i->second;
        }
        i++;
    }

    cout << mostpopular << endl;
    cout << m2["football"] << endl;
}

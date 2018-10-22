#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define pb push_back
typedef unordered_map<int, int> umapii;
typedef unordered_map<int, bool> umapib;

int main(){
    int t;
    cin >> t;
    while(t--){
        int n, k;
        cin >> n;

        int *input = new int[n];
        for(int i = 0; i < n; i++) cin >> input[i];
        cin >> k;

        umapii m;
        for(int i = 0; i < n; i++){
            if(m.find(input[i]) == m.end()) m[input[i]] = 1;
            else m[input[i]]++;
        }

        int total = 0;
        for(int i = 0; i < n; i++){
            if(2*input[i] == k){
                total += (m[input[i]]*(m[input[i]]-1))/2;
                m.erase(input[i]);
            }
            else{
                if(m.find(k-input[i]) != m.end()){
                    total += m[input[i]]*m[k-input[i]];
                    m.erase(k-input[i]);
                }
                m.erase(input[i]);
            }
        }

        cout << total << endl;
    }
}

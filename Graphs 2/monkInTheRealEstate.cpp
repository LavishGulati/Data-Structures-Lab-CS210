#include <iostream>
using namespace std;
#define MAX 10000

int main(){
    int t;
    cin >> t;

    bool *isBought = new bool[MAX];

    while(t--){
        int e;
        cin >> e;

        for(int i = 0; i < MAX; i++) isBought[i] = false;

        int x, y;
        for(int i = 0; i < e; i++){
            cin >> x >> y;
            isBought[x-1] = true;
            isBought[y-1] = true;
        }

        int total = 0;
        for(int i = 0; i < MAX; i++){
            if(isBought[i]) total++;
        }

        cout << total << endl;
    }
}

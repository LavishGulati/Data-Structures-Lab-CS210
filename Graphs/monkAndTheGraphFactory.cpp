#include <iostream>
#include <fstream>
using namespace std;

int main(){
    int n;
    cin >> n;

    int totalDegree = 0;

    int *degree = new int[n];
    for(int i = 0; i < n; i++){
        cin >> degree[i];

        if(degree[i] == 0){
            cout << "No" << endl;
            return 0;
        }

        totalDegree += degree[i];
    }

    if(totalDegree/2 == n-1) cout << "Yes" << endl;
    else cout << "No" << endl;
}

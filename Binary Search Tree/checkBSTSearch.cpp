#include <iostream>
#include <fstream>
#include <climits>
using namespace std;

bool checkBSTSearch(int *input, int n){
    int min = INT_MIN;
    int max = INT_MAX;

    for(int i = 1; i < n; i++){
        if(input[i] < min || input[i] >= max) return false;

        if(input[i] > input[i-1]){
            min = input[i-1];
        } else max = input[i-1];
    }

    return true;
}

int main(){
    ifstream inputFile;
    inputFile.open("input.txt");

    int n;
    inputFile >> n;

    int *input = new int[n];
    for(int i = 0; i < n; i++) inputFile >> input[i];

    cout << checkBSTSearch(input, n) << endl;

    delete input;
    inputFile.close();
}

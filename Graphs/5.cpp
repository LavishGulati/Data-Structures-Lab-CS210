#include <iostream>
#include <fstream>
using namespace std;

int main(){

    ifstream inputFile;
    inputFile.open("input.txt");

    int n;
    inputFile >> n;

    int **graph = new int *[n];
    for(int i = 0; i < n; i++){
        graph[i] = new int[n];
        for(int j = 0; j < n; j++) graph[i][j] = 0;
    }

    while(1){
        int x, y;
        inputFile >> x;
        if(inputFile.eof()) break;
        inputFile >> y;
        if(inputFile.eof()) break;

        graph[x][y] = 1;
    }


}

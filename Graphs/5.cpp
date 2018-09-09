#include <iostream>
#include <fstream>
using namespace std;

void dfs(int parentNode, int currentNode, int **graph, bool **isPath, int n, string *color){
    for(int i = 0; i < n; i++){
        // cout << graph[currentNode][i] << ": " << color[i] << endl;;
        if(graph[currentNode][i] == 1 && color[i] == "white"){
            // cout << parentNode << ": " << i << endl;
            isPath[parentNode][i] = true;
            color[i] = "black";
            dfs(parentNode, i, graph, isPath, n, color);
        }
    }
}

bool check(bool **isPath, int node, int **group, int groupId, int groupSize){
    for(int i = 0; i < groupSize; i++){
        if(!isPath[ group[groupId][i] ][node]) return false;
        if(!isPath[node][ group[groupId][i] ]) return false;
    }
}

int main(){

    ifstream inputFile;
    inputFile.open("input.txt");

    int n;
    inputFile >> n;
    // cout << n << endl;

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

        // cout << x << " " << y << endl;
        graph[x][y] = 1;
    }

    bool **isPath = new bool *[n];
    for(int i = 0; i < n; i++){
        isPath[i] = new bool[n];
        for(int j = 0; j < n; j++) isPath[i][j] = false;
    }

    string *color = new string[n];

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++) color[j] = "white";
        dfs(i, i, graph, isPath, n, color);
    }

    // for(int i = 0; i < n; i++){
    //     for(int j = 0; j < n; j++) cout << isPath[i][j] << " ";
    //     cout << endl;
    // }

    int **group = new int *[n];
    for(int i = 0; i < n; i++){
        group[i] = new int[n];
        for(int j = 0; j < n; j++) group[i][j] = -1;
    }

    bool *isAdded = new bool[n];
    for(int i = 0; i < n; i++) isAdded[i] = false;

    int groupId = 0;
    int groupSize;

    for(int i = 0; i < n; i++){
        groupSize = 0;

        if(isAdded[i]) continue;

        group[groupId][groupSize] = i;
        groupSize++;

        for(int j = 0; j < n; j++){
            if(j == i) continue;

            if(check(isPath, j, group, groupId, groupSize)){
                isAdded[j] = true;
                // groupSize++;
                group[groupId][groupSize] = j;
                groupSize++;
            }
        }

        groupId++;
    }


    for(int i = 0; i < n; i++){
        if(group[i][0] == -1) break;
        for(int j = 0; j < n; j++){
            if(group[i][j] == -1) break;

            cout << group[i][j] << " ";
        }
        cout << endl;
    }
}

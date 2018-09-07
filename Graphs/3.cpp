#include <iostream>
#include <fstream>
using namespace std;

void dfs(int currentNode, int **graph, bool **isPath, int n){
    for(int i = 0; i < n; i++){
        if(graph[currentNode][i] == 1){
            isPath[currentNode][i] = 1;
        }
    }
}

int main(){
    int n, e;
    cin >> n >> e;

    int **graph = new int *[n];
    for(int i = 0; i < n; i++){
        graph[i] = new int[n];
        for(int j = 0; j < n; j++) graph[i][j] = 0;
    }

    for(int i = 0; i < e; i++){
        int u, v;
        cin >> u >> v;

        graph[u][v] = 1;
    }

    bool **isPath = new bool *[n];
    for(int i = 0; i < n; i++){
        isPath[i] = new bool[n];
        for(int j = 0; j < n; j++) isPath[i][j] = false;
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(!isPath[i][j]){
                dfs(i, graph, isPath, n);
            }
        }
    }
}

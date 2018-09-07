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

    string *color = new string[n];

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++) color[j] = "white";
        dfs(i, i, graph, isPath, n, color);
    }

    // for(int i = 0; i < n; i++){
    //     cout << i << ": ";
    //     for(int j = 0; j < n; j++){
    //         if(graph[i][j] == 1) cout << j << " ";
    //     }
    //     cout << endl;
    // }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++) cout << isPath[i][j] << " ";
        cout << endl;
    }
}

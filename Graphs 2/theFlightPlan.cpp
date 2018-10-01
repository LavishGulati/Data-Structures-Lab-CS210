#include <bits/stdc++.h>
using namespace std;

void findPath(vector<int> *path, int x, int y, int *parent){
    if(y == x){
        path->push_back(x+1);
        return;
    }

    findPath(path, x, parent[y], parent);
    path->push_back(y+1);
}

int main(){
    int n, m, t, c;
    cin >> n >> m >> t >> c;

    bool **graph = new bool *[n];
    for(int i = 0; i < n; i++){
        graph[i] = new bool[n];
        for(int j = 0; j < n; j++) graph[i][j] = false;
    }

    int u, v;
    for(int i = 0; i < m; i++){
        cin >> u >> v;
        graph[u-1][v-1] = true;
        graph[v-1][u-1] = true;
    }

    int x, y;
    cin >> x >> y;

    int *parent = new int[n];
    bool *isVisited = new bool[n];
    for(int i = 0; i < n; i++) isVisited[i] = false;

    queue<int> q;
    q.push(x-1);
    parent[x-1] = -1;
    isVisited[x-1] = true;

    while(!q.empty()){
        int vertex = q.front();
        q.pop();

        for(int i = 0; i < n; i++){
            if(graph[vertex][i]){
                if(!isVisited[i]){
                    isVisited[i] = true;
                    parent[i] = vertex;
                    q.push(i);
                }
            }
        }
    }

    vector<int> *path = new vector<int>;
    findPath(path, x-1, y-1, parent);

    cout << path->size() << endl;
    for(int i = 0; i < path->size(); i++) cout << path->at(i) << " ";
    cout << endl;
}

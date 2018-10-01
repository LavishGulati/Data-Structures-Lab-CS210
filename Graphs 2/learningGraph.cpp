#include <bits/stdc++.h>
using namespace std;
#define all(x) (x).begin(), (x).end()

class node{
public:
    int data, value;

    node(int d, int v){
        data = d;
        value = v;
    }

    bool operator< (node b){
        if(this->value > b.value) return true;
        else if(this->value == b.value){
            return this->data > b.data ? true : false;
        }
        else return false;
    }
};

class graphNode{
public:
    int degree;
    vector<node> list;

    graphNode(){
        degree = 0;
    }

    void insertNode(int x, int v){
        degree++;
        node newNode(x, v);
        list.push_back(newNode);
    }
};


int main(){
    int n, m, k;
    cin >> n >> m >> k;

    int *value = new int[n];
    for(int i = 0; i < n; i++) cin >> value[i];

    graphNode *graph = new graphNode[n];

    int x, y;
    for(int i = 0; i < m; i++){
        cin >> x >> y;
        graph[x-1].insertNode(y-1, value[y-1]);
        graph[y-1].insertNode(x-1, value[x-1]);
    }

    for(int i = 0; i < n; i++) sort(all(graph[i].list));

    for(int i = 0; i < n; i++){
        if(graph[i].degree < k) cout << -1 << endl;
        else cout << (graph[i].list)[k-1].data + 1 << endl;
    }
}

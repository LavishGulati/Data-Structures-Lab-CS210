#include <bits/stdc++.h>
using namespace std;

class node{
public:
    int data;
    node *next;

    node(int d){
        data = d;
        next = NULL;
    }
};

class graphNode{
public:
    int degree;
    node *head, *rear;

    graphNode(){
        degree = 0;
        head = NULL;
        rear = NULL;
    }

    void addEdge(int x){
        node *newNode = new node(x);

        if(rear == NULL){
            head = newNode;
            rear = newNode;
            return;
        }

        rear->next = newNode;
    }
};

int main(){
    int n, q;
    cin >> n >> q;

    char *tree = new char[n];
    for(int i = 0; i < n; i++) cin >> tree[i];

    graphNode *graph = new graphNode[n];
    int u, v;
    for(int i = 0; i < n-1; i++){
        cin >> u >> v;
        graph[u-1].addEdge(v-1);
        graph[v-1].addEdge(u-1);
    }
}

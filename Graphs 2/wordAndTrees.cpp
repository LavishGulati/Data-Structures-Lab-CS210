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
        rear = rear->next;
    }

    void printList(){
        node *temp = head;
        while(temp != NULL){
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

void dfs(graphNode *graph, int source, int root, bool check, int *letter, char *tree, bool *isVisited){
    node *temp = graph[source].head;
    if(source == root) check = true;
    // cout << source << " " << check << " " << root << endl;
    isVisited[source] = true;

    int id;
    if(check){
        id = tree[source]-'a';
        if(letter[id] > 0) letter[id]--;
    }

    int vertex;
    while(temp != NULL){
        vertex = temp->data;

        if(!isVisited[vertex]){
            dfs(graph, vertex, root, check, letter, tree, isVisited);
        }

        temp = temp->next;
    }

    if(source == root) check = false;
}

int main(){
    int n, q, i;
    cin >> n >> q;

    char *tree = new char[n];
    for(i = 0; i < n; i++) cin >> tree[i];

    graphNode *graph = new graphNode[n];
    int u, v;
    for(i = 0; i < n-1; i++){
        // cin >> u >> v;
        scanf("%d%d", &u, &v);
        graph[u-1].addEdge(v-1);
        graph[v-1].addEdge(u-1);
    }

    // for(int i = 0; i < n; i++){
    //     cout << i << ": ";
    //     graph[i].printList();
    // }

    int root;
    string s;
    bool check;
    int *letter = new int[26];
    bool *isVisited = new bool[n];

    while(q--){
        for(i = 0; i < 26; i++) letter[i] = 0;
        for(i = 0; i < n; i++) isVisited[i] = false;
        check = false;

        cin >> root >> s;
        for(i = 0; i < s.length(); i++) letter[ s[i]-'a' ]++;


        dfs(graph, 0, root-1, check, letter, tree, isVisited);

        int count = 0;
        for(i = 0; i < 26; i++) count += letter[i];
        cout << count << endl;
    }
}

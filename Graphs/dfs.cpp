#include <iostream>
#include <fstream>
using namespace std;

int currTime = 0;

struct node{
    int data;
    struct node *next;
};

struct graphNode{
    struct node *head;
    int size;
};

node *createNode(int element){
    node *newNode = new node;
    newNode->data = element;
    newNode->next = NULL;
    return newNode;
}

void insert(graphNode *list, int element){
    node *temp = list->head;
    node *prev = NULL;
    node *newNode = createNode(element);

    newNode->next = list->head;
    list->head = newNode;

    (list->size)++;
}

void dfsVisit(int currVertex, graphNode **graph, int n, string *color, int *parent, int *d, int *f, char **edge){
    color[currVertex] = "grey";
    currTime++;
    d[currVertex] = currTime;
    // cout << currVertex << " ";

    node *temp = graph[currVertex]->head;
    while(temp != NULL){
        int i = temp->data;
        if(color[i] == "white"){
            edge[currVertex][i] = 'T';
            parent[i] = currVertex;
            dfsVisit(i, graph, n, color, parent, d, f, edge);
        }
        else if(color[i] == "grey"){
            edge[currVertex][i] = 'B';
        }
        else if(color[i] == "black" && d[i] < d[currVertex]){
            edge[currVertex][i] = 'C';
        }
        else edge[currVertex][i] = 'F';

        temp = temp->next;
    }

    color[currVertex] = "black";
    currTime++;
    f[currVertex] = currTime;
}

void dfs(graphNode **graph, int n, string *color, int *parent, int *d, int *f, char **edge){
    for(int i = 0; i < n; i++){
        if(color[i] == "white"){
            dfsVisit(i, graph, n, color, parent, d, f, edge);
        }
    }
}

int main(){
    int n, e;
    cin >> n >> e;

    graphNode **graph = new graphNode *[n];
    for(int i = 0; i < n; i++){
        graph[i] = new graphNode;
        graph[i]->head = NULL;
        graph[i]->size = 0;
    }

    for(int i = 0; i < e; i++){
        int u, v;
        cin >> u >> v;
        insert(graph[u], v);
        // insert(graph[v], u);
    }

    char **edge = new char *[n];
    for(int i = 0; i < n; i++){
        edge[i] = new char[n];
        for(int j = 0; j < n; j++) edge[i][j] = '.';
    }

    string *color = new string[n];
    int *parent = new int[n];
    int *d = new int[n];
    int *f = new int[n];

    for(int i = 0; i < n; i++){
        color[i] = "white";
    }

    dfs(graph, n, color, parent, d, f, edge);
    // cout << endl;

    // for(int i = 0; i < n; i++){
    //     for(int j = 0; j < n; j++){
    //         printf("%2c", edge[i][j]);
    //     }
    //     cout << endl;
    // }
}

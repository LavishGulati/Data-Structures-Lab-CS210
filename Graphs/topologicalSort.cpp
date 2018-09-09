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

struct stack{
    node *head;
    int size;
};

node *createNode(int element){
    node *newNode = new node;
    newNode->data = element;
    newNode->next = NULL;
    return newNode;
}

stack *createStack(){
    stack *s = new stack;
    s->head = NULL;
    s->size = 0;
    return s;
}

void push(stack *s, int element){
    node *newNode = createNode(element);
    newNode->next = s->head;
    s->head = newNode;
    (s->size)++;
}

void pop(stack *s){
    if(s->head == NULL) return;

    node *removeElem = s->head;
    s->head = removeElem->next;
    delete removeElem;
    (s->size)--;
}

int top(stack *s){
    return s->head->data;
}

void insert(graphNode *list, int element){
    node *temp = list->head;
    node *prev = NULL;
    node *newNode = createNode(element);

    newNode->next = list->head;
    list->head = newNode;

    (list->size)++;
}

void dfsVisit(int currVertex, graphNode **graph, int n, string *color, int *parent, int *d, int *f, char **edge, stack *s){
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
            dfsVisit(i, graph, n, color, parent, d, f, edge, s);
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
    push(s, currVertex);
    f[currVertex] = currTime;
}

void dfs(graphNode **graph, int n, string *color, int *parent, int *d, int *f, char **edge, stack *s){
    for(int i = 0; i < n; i++){
        if(color[i] == "white"){
            dfsVisit(i, graph, n, color, parent, d, f, edge, s);
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

    stack *s = createStack();

    dfs(graph, n, color, parent, d, f, edge, s);
    // cout << endl;

    // for(int i = 0; i < n; i++){
    //     for(int j = 0; j < n; j++){
    //         printf("%2c", edge[i][j]);
    //     }
    //     cout << endl;
    // }

    // for(int i = 0; i < n; i++){
    //     cout << d[i] << " ";
    // }
    // cout << endl;
    //
    // for(int i = 0; i < n; i++){
    //     cout << f[i] << " ";
    // }
    // cout << endl;

    // while(s->size != 0){
    //     cout << top(s) << " ";
    //     pop(s);
    // }
    // cout << endl;
}

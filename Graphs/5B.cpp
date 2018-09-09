#include <iostream>
#include <fstream>
using namespace std;

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

void dfsVisit(int currVertex, graphNode **graph, int n, string *color, stack *s){
    color[currVertex] = "grey";

    node *temp = graph[currVertex]->head;
    while(temp != NULL){
        int i = temp->data;
        if(color[i] == "white"){
            dfsVisit(i, graph, n, color, s);
        }

        temp = temp->next;
    }

    push(s, currVertex);
    color[currVertex] = "black";
}

void dfs(graphNode **graph, int n, string *color, stack *s){
    for(int i = 0; i < n; i++){
        if(color[i] == "white"){
            dfsVisit(i, graph, n, color, s);
        }
    }
}

void strongConnComp(int currVertex, graphNode **graph, int n, string *color){
    color[currVertex] = "grey";
    cout << currVertex << " ";

    node *temp = graph[currVertex]->head;
    while(temp != NULL){
        int i = temp->data;
        if(color[i] == "white") strongConnComp(i, graph, n, color);

        temp = temp->next;
    }

    color[currVertex] = "black";
}

int main(){
    ifstream inputFile;
    inputFile.open("input.txt");

    int n;
    inputFile >> n;

    graphNode **graph = new graphNode *[n];
    for(int i = 0; i < n; i++){
        graph[i] = new graphNode[n];
        graph[i]->head = NULL;
        graph[i]->size = 0;
    }

    graphNode **reverseGraph = new graphNode *[n];
    for(int i = 0; i < n; i++){
        reverseGraph[i] = new graphNode[n];
        reverseGraph[i]->head = NULL;
        reverseGraph[i]->size = 0;
    }

    while(1){
        int x, y;
        inputFile >> x;
        if(inputFile.eof()) break;
        inputFile >> y;
        if(inputFile.eof()) break;

        insert(graph[x], y);
        insert(reverseGraph[y], x);
    }

    string *color = new string[n];
    for(int i = 0; i < n; i++){
        color[i] = "white";
    }

    stack *s = createStack();

    dfs(graph, n, color, s);

    for(int i = 0; i < n; i++) color[i] = "white";

    while(s->size != 0){
        int currVertex = top(s);
        pop(s);

        if(color[currVertex] == "white"){
            strongConnComp(currVertex, reverseGraph, n, color);
            cout << endl;
        }
    }
}

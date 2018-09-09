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

struct queue{
    struct node *front;
    struct node *rear;
    int size;
};


node *createNode(int element){
    node *newNode = new node;
    newNode->data = element;
    newNode->next = NULL;
    return newNode;
}

queue *createQueue(){
    queue *newQueue = new queue;
    newQueue->front = NULL;
    newQueue->rear = NULL;
    newQueue->size = 0;
    return newQueue;
}

bool empty(queue *q){
    return q->size == 0;
}

void enqueue(queue *q, int element){
    node *newNode = createNode(element);

    if(q->size == 0){
        q->front = newNode;
        q->rear = newNode;
    }
    else{
        q->rear->next = newNode;
        q->rear = newNode;
    }

    (q->size)++;
}

int dequeue(queue *q){
    node *temp = q->front;

    q->front = temp->next;
    if(q->front == NULL) q->rear = NULL;
    (q->size)--;

    int answer = temp->data;
    delete temp;
    return answer;
}

void insert(graphNode *list, int element){
    node *temp = list->head;
    node *prev = NULL;
    node *newNode = createNode(element);

    newNode->next = list->head;
    list->head = newNode;

    (list->size)++;
}

void bfs(graphNode **graph, int n, string *color, int *parent, int *d){
    queue *q = createQueue();
    color[0] = "grey";
    parent[0] = -1;
    d[0] = 0;
    enqueue(q, 0);

    while(!empty(q)){
        int currVertex = dequeue(q);
        // cout << currVertex << " ";
        node *temp = graph[currVertex]->head;
        while(temp != NULL){
            int i = temp->data;
            if(color[i] == "white"){
                color[i] = "grey";
                d[i] = d[currVertex]+1;
                parent[i] = currVertex;
                enqueue(q, i);
            }
            temp = temp->next;
        }

        color[currVertex] = "black";
    }
    // cout << endl;
}

void printPath(int source, int currVertex, int *parent){
    if(currVertex == source){
        cout << source << " ";
        return;
    }

    printPath(source, parent[currVertex], parent);
    cout << currVertex << " ";
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
        insert(graph[v], u);
    }

    string *color = new string[n];
    int *parent = new int[n];
    int *d = new int[n];

    for(int i = 0; i < n; i++){
        color[i] = "white";
        d[i] = 0;
        parent[i] = -1;
    }

    bfs(graph, n, color, parent, d);

    // for(int i = 0; i < n; i++){
    //     printPath(0, i, parent);
    //     cout << endl;
    // }
}

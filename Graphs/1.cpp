#include <iostream>
#include <fstream>
using namespace std;

struct node{
    int data;
    struct node *next;
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

void bfs(int **graph, int n, int *parent, string *color){
    queue *q = createQueue();
    enqueue(q, 0);

    while(!empty(q)){
        int currentNode = dequeue(q);
        cout << char('a'+26-n+currentNode) << " ";
        for(int i = 0; i < n; i++){
            if(graph[currentNode][i] == 1 && color[i] == "white"){
                color[i] = "grey";
                parent[i] = currentNode;
                enqueue(q, i);
            }
        }
        color[currentNode] = "black";
    }

    cout << endl;
}

void printShortestPath(int *parent, int currentNode, int source, int n){
    if(currentNode == source){
        cout << char('a'+26-n+source) << " ";
        return;
    }

    printShortestPath(parent, parent[currentNode], source, n);
    cout << char('a'+26-n+currentNode) << " ";
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
        char u, v;
        cin >> u >> v;
        // cout << int(u-26+n-'a') << " " << int(v-26+n-'a') << endl;
        graph[int(u-26+n-'a')][int(v-26+n-'a')] = 1;
        graph[int(v-26+n-'a')][int(u-26+n-'a')] = 1;
    }

    // int count = 0;
    // for(int i = 0; i < n; i++){
    //     for(int j = 0; j < n; j++){
    //         if(graph[i][j] == 1){
    //             count++;
    //             // cout << char('a'+26-n+i) << " " << char('a'+26-n+j) << endl;
    //         }
    //     }
    // }
    // cout << count << endl;

    int *parent = new int[n];
    string *color = new string[n];
    for(int i = 0; i < n; i++) color[i] = "white";

    cout << "BFS of the graph: ";
    bfs(graph, n, parent, color);

    for(int i = 0; i < n; i++){
        cout << "Shortest distance path of " << char('a'+26-n+i) << " from source is: ";
        printShortestPath(parent, i, 0, n);
        cout << endl;
    }
}

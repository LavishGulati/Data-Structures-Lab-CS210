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

    if(list->size == 0) list->head = newNode;
    else{
        newNode->next = list->head;
        list->head = newNode;
    }

    (list->size)++;
}

void bfs(graphNode **graph, int n, int *d, bool *isVisited){
    queue *q = createQueue();

    enqueue(q, 0);
    d[0] = 0;
    isVisited[0] = true;

    while(q->size != 0){
        int currVertex = dequeue(q);

        node *temp = graph[currVertex]->head;
        while(temp != NULL){
            int i = temp->data;
            if(!isVisited[i]){
                enqueue(q, i);
                d[i] = d[currVertex]+1;
                isVisited[i] = true;

                if(i == n-1) return;
            }

            temp = temp->next;
        }
    }
}

int main(){
    int t;
    cin >> t;
    while(t--){
        int n, m;
        cin >> n >> m;

        graphNode **graph = new graphNode *[n];
        for(int i = 0; i < n; i++){
            graph[i] = new graphNode;
            graph[i]->head = NULL;
            graph[i]->size = 0;
        }

        for(int i = 0; i < m; i++){
            int x, y;
            cin >> x >> y;
            insert(graph[x-1], y-1);
            insert(graph[y-1], x-1);
        }

        int *d = new int[n];
        bool *isVisited = new bool[n];
        for(int i = 0; i < n; i++) isVisited[i] = false;

        bfs(graph, n, d, isVisited);

        cout << d[n-1] << endl;
    }
}

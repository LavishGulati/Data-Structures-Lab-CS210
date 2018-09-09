#include <iostream>
#include <fstream>
using namespace std;

struct node{
    int data;
    struct node *next;
};

struct graphNode{
    struct node *head;
    bool isGirlfriend;
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
    else if(element < temp->data){
        newNode->next = list->head;
        list->head = newNode;
    }
    else{
        while(temp != NULL){
            if(element < temp->data) break;

            prev = temp;
            temp = temp->next;
        }

        prev->next = newNode;
        newNode->next = temp;
    }

    (list->size)++;
}

int bfs(graphNode **graph, int n, bool *isVisited){
    queue *q = createQueue();
    enqueue(q, 0);
    isVisited[0] = true;

    while(q->size != 0){
        int currVertex = dequeue(q);
        node *temp = graph[currVertex]->head;

        while(temp != NULL){
            int i = temp->data;
            if(!isVisited[i]){
                if(graph[i]->isGirlfriend) return i+1;

                enqueue(q, i);
                isVisited[i] = true;
            }
            temp = temp->next;
        }
    }
}

int main(){
    int n;
    cin >> n;

    graphNode **graph = new graphNode *[n];
    for(int i = 0; i < n; i++){
        graph[i] = new graphNode;
        graph[i]->head = NULL;
        graph[i]->isGirlfriend = false;
        graph[i]->size = 0;
    }

    for(int i = 0; i < n-1; i++){
        int u, v;
        cin >> u >> v;
        insert(graph[u-1], v-1);
        insert(graph[v-1], u-1);
    }

    int q;
    cin >> q;
    for(int i = 0; i < q; i++){
        int x;
        cin >> x;
        graph[x-1]->isGirlfriend = true;
    }

    bool *isVisited = new bool[n];
    for(int i = 0; i < n; i++) isVisited[i] = false;

    cout << bfs(graph, n, isVisited) << endl;
}

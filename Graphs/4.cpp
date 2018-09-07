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

int main(){
    int n, r;
    cin >> n >> r;

    graphNode **graph = new graphNode *[n];
    for(int i = 0; i < n; i++){
        graph[i] = new graphNode;
        graph[i]->head = NULL;
        graph[i]->size = 0;
    }

    for(int i = 0; i < r; i++){
        int u, v;
        cin >> u >> v;
        insert(graph[u-1], v-1);
        insert(graph[v-1], u-1);
    }

    // for(int i = 0; i < n; i++){
    //     node *temp = graph[i]->head;
    //     cout << i << ": ";
    //     while(temp != NULL){
    //         cout << temp->data << " ";
    //         temp = temp->next;
    //     }
    //     cout << endl;
    // }

    int **rival = new int *[2];
    rival[0] = new int[n];
    rival[1] = new int[n];
    for(int i = 0; i < n; i++){
        rival[0][i] = 0;
        rival[1][i] = 0;
    }

    bool *isVisited = new bool[n];
    for(int i = 0; i < n; i++) isVisited[i] = false;

    queue *q = createQueue();
    enqueue(q, 0);
    isVisited[0] = true;
    rival[0][0] = 1;

    while(q->size != 0){
        int i = dequeue(q);
        // cout << i << endl;
        int id;

        if(rival[0][i] == 1) id = 1;
        else id = 0;

        node *temp = graph[i]->head;

        while(temp != NULL){
            int j = temp->data;
            if(isVisited[j]){
                if(rival[1^id][j] == 1){
                    cout << "Not Possible" << endl;
                    return 0;
                }
                temp = temp->next;
                continue;
            }

            if(rival[1^id][j] == 1){
                cout << "Not Possible" << endl;
                return 0;
            }

            rival[id][j] = 1;
            enqueue(q, j);
            isVisited[j] = true;
            temp = temp->next;
        }
    }

    cout << "Good Guys: ";
    for(int i = 0; i < n; i++){
        if(rival[0][i] == 1) cout << i+1 << " ";
    }
    cout << endl;

    cout << "Bad Guys: ";
    for(int i = 0; i < n; i++){
        if(rival[1][i] == 1) cout << i+1 << " ";
    }
    cout << endl;
}

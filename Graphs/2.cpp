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

void dfs(graphNode **graph, int n, string *color){
    stack *s = createStack();
    int flag;

    for(int i = 0; i < n; i++){
        if(color[i] == "white"){
            push(s, i);
            color[i] = "grey";

            while(s->size != 0){
                flag = 0;
                int currentNode = top(s);
                // cout << char('a'+26-n+currentNode) << " ";
                node *temp = graph[currentNode]->head;
                
                while(temp != NULL){
                    // cout << currentNode << " " << temp->data << endl;
                    if(color[temp->data] == "white"){
                        cout << "(" << char('a'+26-n+currentNode) << "," << char('a'+26-n+(temp->data)) << ")" << endl;
                        push(s, temp->data);
                        color[temp->data] = "grey";
                        flag = 1;
                        break;
                    }
                    temp = temp->next;
                }

                if(flag == 0){
                    color[top(s)] = "black";
                    pop(s);
                }
            }
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
        char u, v;
        cin >> u >> v;
        insert(graph[int(u-26+n-'a')], int(v-26+n-'a'));
    }

    // for(int i = 0; i < n; i++){
    //     node *temp = graph[i]->head;
    //     cout << char('a'+26-n+i) << ": ";
    //     while(temp != NULL){
    //         cout << char('a'+26-n+(temp->data)) << " ";
    //         temp = temp->next;
    //     }
    //     cout << endl;
    // }

    string *color = new string[n];
    for(int i = 0; i < n; i++) color[i] = "white";

    dfs(graph, n, color);
}

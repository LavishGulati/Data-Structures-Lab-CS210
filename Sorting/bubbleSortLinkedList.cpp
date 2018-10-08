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

void inputLinkedList(){
    int n;
    cin >> n;

    if(n == 0) return;

    int x;
    cin >> x;
    node *head = new node(x);
    node *temp = head;

    for(int i = 0; i < n-1; i++){
        cin >> x;
        temp->next = new node(x);
        temp = temp->next;
    }
}

void printList(node *head){
    node *temp = head;
    while(temp != NULL){
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

void bubbleSort(node *head){
    node *temp = head;
}

int main(){
    node *head = inputLinkedList();

    bubbleSort(head);
    printList(head);
}

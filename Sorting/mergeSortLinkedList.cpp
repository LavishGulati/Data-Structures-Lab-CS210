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

node *inputLinkedList(){
    int n;
    cin >> n;

    if(n == 0) return NULL;

    int x;
    cin >> x;
    node *head = new node(x);
    node *temp = head;

    for(int i = 0; i < n-1; i++){
        cin >> x;
        temp->next = new node(x);
        temp = temp->next;
    }

    return head;
}

void printList(node *head){
    node *temp = head;
    while(temp != NULL){
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

void swap(node *temp1, node *temp2){
    int x = temp1->data;
    temp1->data = temp2->data;
    temp2->data = x;
}

node *mergeSort(node *head, int size){
    if(size <= 1) return;

    int count = 1;
    node *temp = head;
    while(count != size/2){
        count++;
        temp = temp->next;
    }

    node *head2 = temp->next;
    temp->next = NULL;

    node *newHead = mergeSort(head, count);
    node *newHead2 = mergeSort(head, size-count);

    
}

void mergeSort(node *head){
    int count = 0;
    node *temp = head;
    while(temp != NULL){
        temp = temp->next;
        count++;
    }

    return mergeSort(head, n);
}

int main(){
    node *head = inputLinkedList();

    mergeSort(head);
    printList(head);
}

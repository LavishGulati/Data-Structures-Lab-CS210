#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unordered_map<int, int> umapii;
typedef unordered_map<int, bool> umapib;
typedef unordered_map<string, int> umapsi;
typedef unordered_map<string, string> umapss;
typedef map<string, int> mapsi;
typedef map<pair<int, int>, int> mappiii;

#define it iterator
#define mp make_pair
#define pb push_back
#define all(x) (x).begin(), (x).end()

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

void selectionSort(node *head){
    node *temp = head;
    while(1){
        if(temp->next == NULL) break;

        node *smallest = temp;
        node *temp2 = temp->next;
        while(temp2 != NULL){
            if(smallest->data > temp2->data) smallest = temp2;
            temp2 = temp2->next;
        }

        swap(temp, smallest);

        temp = temp->next;
    }
}

int main(){
    node *head = inputLinkedList();

    selectionSort(head);
    printList(head);
}

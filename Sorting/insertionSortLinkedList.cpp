#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unordered_map<int, int> umapii;
typedef unordered_map<int, bool> umapib;
typedef unordered_map<string, int> umapsi;
typedef unordered_map<string, string> umapss;
typedef map<string, int> mapsi;
typedef map<pair<int, int>, int> mappiii;
typedef map<int, int> mapii;
typedef pair<int, int> pii;

#define it iterator
#define mp make_pair
#define pb push_back
#define all(x) (x).begin(), (x).end()

class node{
public:
    int data;
    node *next;
    node *prev;

    node(int d){
        data = d;
        next = NULL;
        prev = NULL;
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
        temp->next->prev = temp;
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

void insertionSort(node *head){
    node *temp = head->next;
    while(temp != NULL){
        
    }
}

int main(){
    node *head = inputLinkedList();

    insertionSort(head);
    printList(head);
}

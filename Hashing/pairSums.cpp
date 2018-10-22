#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define pb push_back
typedef unordered_map<int, int> umapii;
typedef unordered_map<int, bool> umapib;

class node{
    int key;
    int value;
    node *next;

    friend class bucket;

    node(int k, int v){
        key = k;
        value = v;
        next = NULL;
    }
};

class bucket{
    int bucketSize;
    node *head;
    node *rear;

    friend class hashmap;

    void insert(int k, int v){
        if(head == NULL){
            node *newNode = new node(k, v);
            head = newNode;
            rear = newNode;
            bucketSize++;
            return;
        }

        node *newNode = new node(k, v);
        rear->next = newNode;
        rear = newNode;
        bucketSize++;
    }

    int search(int k){
        node *temp = head;
        while(temp != NULL){
            if(temp->key == k) return temp->value;
            temp = temp->next;
        }

        return -1;
    }

    void deleteRecord(int k){
        if(bucketSize == 0){
            return;
        }
        else if(bucketSize == 1){
            if(head->key == k){
                node *temp = head;
                head = NULL;
                rear = NULL;
                delete temp;
                bucketSize--;
                return;
            }
            else return;
        }

        node *prev = NULL;
        node *temp = head;
        if(head->key == k){
            head = head->next;
            delete temp;
            bucketSize--;
            return;
        }

        while(temp != NULL){
            if(temp->key == k){
                if(temp->next == NULL){
                    rear = prev;
                    delete temp;
                    bucketSize--;
                }
                else{
                    prev->next = temp->next;
                    delete temp;
                    bucketSize--;
                }
                return;
            }
            prev = temp;
            temp = temp->next;
        }

    }
};

class hashmap{
    int mapSize;
    bucket *map;

public:
    void insert(int k, int v){
        map[k%mapSize].insert(k, v);
    }

    hashmap(int size){
        mapSize = size;
        map = new bucket[size];
        for(int i = 0; i < size; i++){
            map[i].bucketSize = 0;
            map[i].head = NULL;
            map[i].rear = NULL;
        }
    }

    int search(int k){
        return map[k%mapSize].search(k);
    }

    void deleteRecord(int k){
        map[k%mapSize].deleteRecord(k);
    }
};

int main(){
    int n, k;
    cin >> n >> k;

    int *input = new int[n];
    for(int i = 0; i < n; i++) cin >> input[i];

    // hashmap m(1000000);
    //
    // for(int i = 0; i < n; i++){
    //     if(m.search(k - input[i]) != -1){
    //         cout << "YES" << endl;
    //         return 0;
    //     }
    //     else{
    //         m.insert(input[i], i);
    //     }
    // }
    //
    // cout << "NO" << endl;

    umapib m;
    for(int i = 0; i < n; i++){
        if(m.find(k - input[i]) != m.end()){
            cout << "YES" << endl;
            return 0;
        }

        m[input[i]] = true;
    }

    cout << "NO" << endl;
}

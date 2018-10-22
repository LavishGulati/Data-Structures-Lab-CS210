#include <bits/stdc++.h>
using namespace std;

class node{
    int key;
    node *next;

    friend class bucket;
    friend class hashmap;

    node(int k){
        key = k;
        next = NULL;
    }

    int getKey(){
        return key;
    }
};

class bucket{
    node *head;
    node *rear;

    friend class hashmap;

    void insert(int k){
        if(head == NULL){
            node *newNode = new node(k);
            head = newNode;
            rear = newNode;
            return;
        }

        node *newNode = new node(k);
        rear->next = newNode;
        rear = newNode;
    }

    void printList(){
        node *temp = head;
        if(temp == NULL) return;

        while(temp->next != NULL){
            cout << temp->key << ", ";
            temp = temp->next;
        }
        cout << temp->key;
    }

    bool search(int k){
        node *temp = head;
        while(temp != NULL){
            if(temp->key == k) return true;
            temp = temp->next;
        }
        return false;
    }
};

class hashmap{
    int numBucket, numKey;
    double threshold;
    bucket *map;

    int hash(int key){
        return key%numBucket;
    }

    void display(){
        cout << "Number of keys: " << numKey << endl;
        cout << "Number of buckets: " << numBucket << endl;
        for(int i = 0; i < numBucket; i++){
            cout << "Bucket " << i << ": ";
            map[i].printList();
            cout << endl;
        }
        cout << endl;
    }

    void extendHashmap(){
        int oldNumBucket = numBucket;
        numBucket *= 3;
        bucket *newMap = new bucket[numBucket];

        for(int i = 0; i < oldNumBucket; i++){
            node *temp = map[i].head;
            while(temp != NULL){
                int k = temp->getKey();
                int id = hash(k);
                newMap[id].insert(k);
                temp = temp->next;
            }
        }

        bucket *oldMap = map;
        map = newMap;
        delete[] oldMap;
    }

public:
    hashmap(int numBucket, double threshold){
        this->numBucket = numBucket;
        this->numKey = 0;
        this->threshold = threshold;
        map = new bucket[numBucket];
        for(int i = 0; i < numBucket; i++){
            map[i].head = NULL;
            map[i].rear = NULL;
        }
    }

    void insert(int k){
        int id = hash(k);

        if(map[id].search(k)){
            cout << "Key " << k << " already present in the hash table. Status of the hash table." << endl;
            display();
            return;
        }

        double loadFactor = (double(numKey+1))/(double(numBucket));
        if(loadFactor > threshold){
            extendHashmap();
        }

        id = hash(k);
        map[id].insert(k);
        numKey++;
    }
};

int main(){
    double threshold;
    int numBucket;
    cin >> threshold >> numBucket;
    hashmap m(numBucket, threshold);

    int key;
    while(1){
        if(cin >> key) m.insert(key);
        else break;
    }
}

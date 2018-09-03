#include <iostream>
#include <climits>
#include <fstream>
using namespace std;

struct heap{
    int *array;
    int size;
    int maxSize;
};

heap *createHeap(int n){
    heap *newMinHeap = new heap;
    newMinHeap->array = new int[n+1];
    newMinHeap->size = 0;
    newMinHeap->maxSize = n;
    return newMinHeap;
}

void swap(int *array, int i, int j){
    int x = array[i];
    array[i] = array[j];
    array[j] = x;
}

void moveUp(heap *minHeap, int id){
    int i = id;
    while(i > 1 && minHeap->array[i] < minHeap->array[i/2]){
        swap(minHeap->array, i, i/2);
        i = i/2;
    }
}

void insert(heap *minHeap, int element){
    (minHeap->size)++;
    minHeap->array[minHeap->size] = element;

    moveUp(minHeap, minHeap->size);
}

int getMinId(heap *minHeap, int i, int j, int k){
    int minId = i;

    if(j <= minHeap->size && minHeap->array[j] < minHeap->array[minId]) minId = j;
    if(k <= minHeap->size && minHeap->array[k] < minHeap->array[minId]) minId = k;

    return minId;
}

void moveDown(heap *minHeap, int id){
    int i = id;

    while(i <= minHeap->size){
        int minId = getMinId(minHeap, i, 2*i, 2*i+1);

        if(minId == i) break;
        else{
            swap(minHeap->array, i, minId);
            i = minId;
        }
    }
}

int deleteMin(heap *minHeap){
    int answer = minHeap->array[1];

    // (minHeap->size)--;

    minHeap->array[1] = minHeap->array[minHeap->size];

    (minHeap->size)--;

    moveDown(minHeap, 1);

    // (minHeap->size)--;

    return answer;
}

void deleteKey(heap *minHeap, int id){
    if(id > minHeap->size){
        cout << "Id is larger than heap size" << endl;
        return;
    }

    // (minHeap->size)--;

    minHeap->array[id] = minHeap->array[minHeap->size];
    (minHeap->size)--;
    moveDown(minHeap, id);

    // (minHeap->size)--;
}

void increaseKey(heap *minHeap, int id, int value){
    minHeap->array[id] = value;

    // cout << value << endl;

    moveDown(minHeap, id);
}

int main(){
    int n;
    cin >> n;

    heap *minHeap = createHeap(n);

    for(int i = 0; i < n; i++){
        int element;
        cin >> element;
        insert(minHeap, element);
    }

    // for(int i = 1; i < n; i++){
    //     cout << minHeap->array[i] << " ";
    // }
    // cout << endl;

    // while(minHeap->size){
    //     cout << deleteMin(minHeap) << " ";
    // }
    // cout << endl;

    cout << deleteMin(minHeap) << endl;

    deleteKey(minHeap, 1);
    deleteKey(minHeap, 2);
    deleteKey(minHeap, 3);
    deleteKey(minHeap, 4);

    cout << deleteMin(minHeap) << endl;

    increaseKey(minHeap, 1, 12);

    cout << deleteMin(minHeap) << endl;
    while(minHeap->size){
        cout << deleteMin(minHeap) << endl;
        // cout << minHeap->size << " " << deleteMin(minHeap) << endl;
    }
}

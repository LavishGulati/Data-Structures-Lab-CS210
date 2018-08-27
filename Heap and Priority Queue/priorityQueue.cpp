#include <iostream>
#include <fstream>
#include <climits>
using namespace std;

struct heap{
    int *array;
    int size;
    int maxSize;
};

heap *createHeap(int n){
    heap *newHeap = new heap;
    newHeap->array = new int[n+1];
    newHeap->size = 0;
    newHeap->maxSize = n;
    return newHeap;
}

void swap(int *array, int i, int j){
    int x = array[i];
    array[i] = array[j];
    array[j] = x;
}

void insert(heap *newHeap, int element){
    if(newHeap->size == newHeap->maxSize) return;

    (newHeap->size)++;
    newHeap->array[newHeap->size] = element;

    int i = newHeap->size;
    while(i > 1){
        if(newHeap->array[i] > newHeap->array[i/2]){
            swap(newHeap->array, i, i/2);
            i = i/2;
        }
        else break;
    }
}

int getMaxId(heap *newHeap, int i, int j, int k){
    int maxId = i;

    if(j <= newHeap->size && newHeap->array[j] > newHeap->array[maxId]) maxId = j;
    if(k <= newHeap->size && newHeap->array[k] > newHeap->array[maxId]) maxId = k;

    return maxId;
}

void deleteHeap(heap *newHeap, int id){
    newHeap->array[id] = INT_MIN;

    int i = id;
    while(i <= newHeap->size){
        int maxId = getMaxId(newHeap, i, 2*i, 2*i+1);

        if(maxId == i) break;
        else{
            swap(newHeap->array, i, maxId);
            i = maxId;
        }
    }

    (newHeap->size)--;
}

int extract(heap *newHeap){
    int answer = newHeap->array[1];
    deleteHeap(newHeap, 1);
    return answer;
}

void increaseKey(heap *newHeap, int id, int key){
    if(key < newHeap->array[id]) return;

    newHeap->array[id] = key;
    int i = id;
    while(i > 1){
        if(newHeap->array[i] > newHeap->array[i/2]){
            swap(newHeap->array, i, i/2);
            i = i/2;
        }
        else break;
    }
}

int main(){

}

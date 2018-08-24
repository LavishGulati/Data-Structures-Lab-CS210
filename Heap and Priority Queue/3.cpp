#include <iostream>
#include <fstream>
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
    (newHeap->size)++;
    newHeap->array[newHeap->size] = element;

    int i = newHeap->size;
    while(i > 1 && newHeap->array[i] > newHeap->array[i/2]){
        swap(newHeap->array, i, i/2);
        i = i/2;
    }
}

int main(){
    int n;
    cin >> n;

    int *input = new int[n+1];
    for(int i = 1; i <= n; i++) cin >> input[i];

    int k;
    cin >> k;

    heap *newHeap = createHeap(k);

    for(int i = 1; i <= k; i++){
        insert(newHeap, input[i]);
    }

    for(int i = k+1; i <= n; i++){
        if(input[i] < newHeap->array[1]) insert(newHeap, input[i]);
    }

    cout << newHeap->array[1] << endl;

    delete input;
    delete newHeap;
}

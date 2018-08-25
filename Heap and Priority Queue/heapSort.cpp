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

int getMaxId(heap *newHeap, int i, int j, int k){
    int maxId = i;

    if(j <= newHeap->size && newHeap->array[j] > newHeap->array[maxId]) maxId = j;
    if(k <= newHeap->size && newHeap->array[k] > newHeap->array[maxId]) maxId = k;

    return maxId;
}

void swap(int *array, int i, int j){
    int x = array[i];
    array[i] = array[j];
    array[j] = x;
}

void heapify(heap *newHeap, int i){
    int maxId = getMaxId(newHeap, i, 2*i, 2*i+1);

    if(i != maxId){
        // cout << "Swap " << newHeap->array[i] << " " << newHeap->array[maxId] << endl;
        swap(newHeap->array, i, maxId);
        heapify(newHeap, maxId);
    }
}

void buildHeap(heap *inputHeap, int n){
    for(int i = n/2; i > 0; i--){
        heapify(inputHeap, i);
    }
}

int *heapSort(heap *inputHeap, int n){
    while(inputHeap->size > 1){
        // cout << "Swap " << inputHeap->array[1] << " " << inputHeap->array[heapSize] << endl;
        swap(inputHeap->array, 1, inputHeap->size);
        (inputHeap->size)--;
        heapify(inputHeap, 1);
    }

    inputHeap->size = n;
    return inputHeap->array;
}

int main(){
    ifstream inputFile;
    inputFile.open("input.txt");

    int n;
    inputFile >> n;

    heap *inputHeap = createHeap(n);
    for(int i = 1; i <= n; i++) inputFile >> inputHeap->array[i];
    inputHeap->size = n;

    buildHeap(inputHeap, n);
    // for(int i = 1; i <= n; i++) cout << inputHeap->array[i] << " ";
    // cout << endl;

    int *output = heapSort(inputHeap, n);
    for(int i = 1; i <= n; i++) cout << output[i] << " ";
    cout << endl;

    delete[] output;
    delete inputHeap;
}

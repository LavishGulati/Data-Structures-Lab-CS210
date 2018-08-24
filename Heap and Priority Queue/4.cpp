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

int *merge(int *a, int n, int *b, int m){
    int *output = new int[m+n+1];

    int id = 1;
    int idA = 1;
    int idB = 1;

    while(idA <= n && idB <= m){
        if(a[idA] > b[idB]){
            output[id] = a[idA];
            idA++;
        }
        else{
            output[id] = b[idB];
            idB++;
        }

        id++;
    }

    while(idA <= n){
        output[id] = a[idA];
        idA++;
        id++;
    }

    while(idB <= n){
        output[id] = b[idB];
        idB++;
        id++;
    }

    return output;
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
        swap(newHeap->array, i, maxId);
        heapify(newHeap, maxId);
    }
}

heap *mergeHeaps(int *a, int n, int *b, int m){
    heap *newHeap = createHeap(m+n);
    int *output = merge(a, n, b, m);
    newHeap->array = output;
    newHeap->size = m+n;

    for(int i = (m+n)/2; i > 0; i--) heapify(newHeap, i);

    return newHeap;
}

int main(){
    int n;
    cin >> n;
    int *a = new int[n+1];
    for(int i = 1; i <= n; i++) cin >> a[i];

    int m;
    cin >> m;
    int *b = new int[m+1];
    for(int i = 1; i <= m; i++) cin >> b[i];

    heap *outputHeap = mergeHeaps(a, n, b, m);

    for(int i = 1; i <= m+n; i++) cout << outputHeap->array[i] << " ";
    cout << endl;

    delete outputHeap;
    delete a;
    delete b;
}

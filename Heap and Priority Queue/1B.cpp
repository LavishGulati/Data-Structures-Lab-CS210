#include <iostream>
#include <fstream>
#include <time.h>
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

int getMinId(heap *newHeap, int i, int j, int k){
    int minId = i;

    if(j <= newHeap->size && newHeap->array[j] < newHeap->array[minId]) minId = j;
    if(k <= newHeap->size && newHeap->array[k] < newHeap->array[minId]) minId = k;

    return minId;
}

void swap(int *array, int i, int j){
    int x = array[i];
    array[i] = array[j];
    array[j] = x;
}

void heapify(heap *newHeap, int i){
    int minId = getMinId(newHeap, i, 2*i, 2*i+1);

    if(i != minId){
        swap(newHeap->array, i, minId);
        heapify(newHeap, minId);
    }
}

heap *buildHeap(int *k){
    ifstream inputFile;
    inputFile.open("input.txt");

    int n;
    inputFile >> n;

    heap *newHeap = createHeap(n);

    for(int i = 1; i <= n; i++){
        int element;
        inputFile >> element;

        (newHeap->size)++;
        newHeap->array[i] = element;
    }

    for(int i = n/2; i > 0; i--) heapify(newHeap, i);

    inputFile >> *k;

    return newHeap;
}

int deleteFromHeap(heap *newHeap){
    int answer = newHeap->array[1];

    newHeap->array[1] = newHeap->array[newHeap->size];
    (newHeap->size)--;

    int i = 1;
    while(i <= newHeap->size){
        int minId = getMinId(newHeap, i, 2*i, 2*i+1);

        // cout << minId << " ";

        if(minId == i) break;
        else if(minId == 2*i){
            swap(newHeap->array, i, 2*i);
            i = 2*i;
        }
        else{
            swap(newHeap->array, i, 2*i+1);
            i = 2*i+1;
        }
    }
    // cout << endl;

    return answer;
}

void kLowestSalary(heap *salary, int k){
    for(int i = 0; i < k; i++){
        cout << deleteFromHeap(salary) << " ";
    }
    cout << endl;
}

int main(){
    int k;

    clock_t start = clock();
    heap *salary = buildHeap(&k);
    clock_t stop = clock();

    cout << 1000*((double)stop-(double)start)/(CLOCKS_PER_SEC) << endl;
    // for(int i = 1; i <= salary->size; i++) cout << salary->heapArray[i] << " ";
    // cout << endl;

    kLowestSalary(salary, k);

    delete salary;
}

#include <iostream>
#include <fstream>
#include <time.h>
using namespace std;

struct heap{
    int *heapArray;
    int size;
    int maxSize;
};

heap *createHeap(int n){
    heap *newHeap = new heap;
    newHeap->heapArray = new int[n+1];
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
    newHeap->heapArray[newHeap->size] = element;

    int i = newHeap->size;
    while(i/2 > 0 && newHeap->heapArray[i] < newHeap->heapArray[i/2]){
        swap(newHeap->heapArray, i, i/2);
        i = i/2;
    }
}

heap *buildHeap(int *addressK){
    ifstream inputFile;
    inputFile.open("input.txt");

    int n;
    inputFile >> n;

    heap *newHeap = createHeap(n);

    for(int i = 0; i < n; i++){
        int element;
        inputFile >> element;
        insert(newHeap, element);
    }

    inputFile >> *addressK;

    return newHeap;
}

int getMinId(heap *newHeap, int i, int j, int k){
    int minId = i;

    if(j <= newHeap->size && newHeap->heapArray[j] < newHeap->heapArray[minId]) minId = j;
    if(k <= newHeap->size && newHeap->heapArray[k] < newHeap->heapArray[minId]) minId = k;

    return minId;
}

int deleteFromHeap(heap *newHeap){
    int answer = newHeap->heapArray[1];

    newHeap->heapArray[1] = newHeap->heapArray[newHeap->size];
    (newHeap->size)--;

    int i = 1;
    while(i <= newHeap->size){
        int minId = getMinId(newHeap, i, 2*i, 2*i+1);

        // cout << minId << " ";

        if(minId == i) break;
        else if(minId == 2*i){
            swap(newHeap->heapArray, i, 2*i);
            i = 2*i;
        }
        else{
            swap(newHeap->heapArray, i, 2*i+1);
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

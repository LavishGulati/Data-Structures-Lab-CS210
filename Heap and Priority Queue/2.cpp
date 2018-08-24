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
    while(i/2 > 0 && newHeap->array[i] < newHeap->array[i/2]){
        swap(newHeap->array, i, i/2);
        i = i/2;
    }
}

int getMin(heap *newHeap){
    return newHeap->array[1];
}

int getMinId(heap *newHeap, int i, int j, int k){
    int minId = i;

    if(j <= newHeap->size && newHeap->array[j] < newHeap->array[minId]) minId = j;
    if(k <= newHeap->size && newHeap->array[k] < newHeap->array[minId]) minId = k;

    return minId;
}

void removeMin(heap *newHeap){
    int answer = newHeap->array[1];

    newHeap->array[1] = newHeap->array[newHeap->size];
    (newHeap->size)--;

    int i = 1;
    while(i <= newHeap->size){
        int minId = getMinId(newHeap, i, 2*i, 2*i+1);

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
}

int main(){
    int n;
    cin >> n;

    int answer = 0;
    string *outputCommand = new string[2*n];
    int *outputElement = new int[2*n];

    heap *newHeap = createHeap(n);

    for(int i = 0; i < n; i++){
        string command;
        cin >> command;


        if(command == "insert"){
            int element;
            cin >> element;
            insert(newHeap, element);

            outputCommand[answer] = "insert";
            outputElement[answer] = element;
            answer++;
        }
        else if(command == "getMin"){
            int element;
            cin >> element;

            if(newHeap->size == 0 || getMin(newHeap) > element){
                insert(newHeap, element);

                outputCommand[answer] = "insert";
                outputElement[answer] = element;
                answer++;

                outputCommand[answer] = "getMin";
                outputElement[answer] = element;
                answer++;
            }
            else{
                while(newHeap->size != 0 && getMin(newHeap) < element){
                    removeMin(newHeap);

                    outputCommand[answer] = "removeMin";
                    answer++;
                }

                insert(newHeap, element);

                outputCommand[answer] = "insert";
                outputElement[answer] = element;
                answer++;

                outputCommand[answer] = "getMin";
                outputElement[answer] = element;
                answer++;
            }
        }
        else if(command == "removeMin"){
            removeMin(newHeap);
            outputCommand[answer] = "removeMin";
            answer++;
        }
    }


    cout << answer << endl;
    for(int i = 0; i < answer; i++){
        if(outputCommand[i] != "removeMin"){
            cout << outputCommand[i] << " " << outputElement[i] << endl;
        }
        else cout << outputCommand[i] << endl;
    }
}

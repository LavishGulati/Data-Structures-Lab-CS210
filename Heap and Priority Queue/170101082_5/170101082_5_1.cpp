#include <iostream>
using namespace std;

// Node of the max heap which contains a character and its priority
struct node{
    char data;
    int priority;
};

// Heap which contains a heap array, its size and its maximum capacity
struct heap{
    node *array;
    int size;
    int maxSize;
};

// Creates a heap by allocating memory for heap array and assigning other values
heap *createHeap(int n){
    heap *newHeap = new heap;
    newHeap->array = new node[n+1];
    newHeap->size = 0;
    newHeap->maxSize = n;
    return newHeap;
}

// Finds the specified element in the max heap iteratively
int find(heap *maxHeap, char element){
    for(int i = 1; i <= maxHeap->size; i++){
        if((maxHeap->array[i]).data == element) return i;
    }

    return 0;
}

// Swaps the values of two indexes i and j in the given array
void swap(node *array, int i, int j){
    int x = array[i].priority;
    array[i].priority = array[j].priority;
    array[j].priority = x;

    char y = array[i].data;
    array[i].data = array[j].data;
    array[j].data = y;
}

// Move up the element in the max heap recursively to place the element at its correct position
void moveUp(heap *maxHeap, int id){
    if(id > 1){
        if((maxHeap->array[id/2]).priority < (maxHeap->array[id]).priority){
            swap(maxHeap->array, id, id/2);
            moveUp(maxHeap, id/2);
        }
    }
}

// Insert an element into the max heap. If it is not found in the max heap, specify its
// frequency as 1. Else, increase its frequency by 1.
void insert(heap *maxHeap, char element){
    int id = find(maxHeap, element);

    if(id == 0){
        (maxHeap->size)++;
        node newNode;
        newNode.data = element;
        newNode.priority = 1;
        maxHeap->array[maxHeap->size] = newNode;
    }
    else{
        ((maxHeap->array[id]).priority)++;
        moveUp(maxHeap, id);
    }
}

// Get the id of the maximum value among indexes i, j and k in the given max heap
int getMaxId(heap *maxHeap, int i, int j, int k){
    int maxId = i;
    if(j <= maxHeap->size && (maxHeap->array[j]).priority > (maxHeap->array[maxId]).priority){
        maxId = j;
    }
    if(k <= maxHeap->size && (maxHeap->array[k]).priority > (maxHeap->array[maxId]).priority){
        maxId = k;
    }

    return maxId;
}

// Move down the element in the max heap iteratively to place the element at its correct position
void moveDown(heap *maxHeap, int id){
    int i = id;

    while(i <= maxHeap->size){
        int maxId = getMaxId(maxHeap, i, 2*i, 2*i+1);

        if(i == maxId) break;
        else{
            swap(maxHeap->array, i, maxId);
            i = maxId;
        }
    }
}

// Insert a character in the ouput string one by one by checking its priority of frequency
// and whether it is being repeated or not
string insertInOutput(string output, heap *maxHeap){

    // If output string is empty or previous character of the output string is not same as
    // the current element to be inserted
    if(output.size() == 0 || (maxHeap->array[1]).data != output[output.size()-1]){
        if((maxHeap->array[1]).priority == 0) return "";
        output = output + (maxHeap->array[1]).data;
        (maxHeap->array[1].priority)--;
        moveDown(maxHeap, 1);
        return output;
    }

    // If current element is same as the previous character in the output string
    int maxId = (maxHeap->array[2]).priority > (maxHeap->array[3].priority) ? 2 : 3;
    if((maxHeap->array[maxId]).priority == 0) return "";
    output = output + (maxHeap->array[maxId]).data;
    ((maxHeap->array[maxId]).priority)--;
    moveDown(maxHeap, maxId);
    return output;
}


int main(){
    // Inputting string
    string input;
    cin >> input;

    // Creating max heap
    heap *maxHeap = createHeap(input.size()+1);
    string output = "";

    // Inserting characters in max heap one by one
    for(int i = 0; i < input.size(); i++){
        insert(maxHeap, input[i]);
    }

    // for(int i = 1; i <= maxHeap->size; i++){
    //     cout << maxHeap->array[i].data << " " << maxHeap->array[i].priority << endl;
    // }

    // Calculating output string
    for(int i = 0; i < input.size(); i++){
        output = insertInOutput(output, maxHeap);
        if(output == ""){
            cout << "Not Possible" << endl;
            return 0;
        }
    }

    cout << output << endl;
}

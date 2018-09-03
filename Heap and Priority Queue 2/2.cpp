#include <iostream>
#include <fstream>
using namespace std;

struct node{
    char data;
    int frequency;
    node *left;
    node *right;
};

struct heap{
    node **array;
    int size;
};

heap *createHeap(int n){
    heap *newHeap = new heap;
    newHeap->array = new node*[n+1];
    newHeap->size = 0;
    return newHeap;
};

node *createNode(){
    node *newNode = new node;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void swap(node **array, int i, int j){
    node *swap = array[i];
    array[i] = array[j];
    array[j] = swap;
}

void moveUp(heap *minHeap, int id){
    int i = id;
    while(i > 1 && minHeap->array[i]->frequency < minHeap->array[i/2]->frequency){
        swap(minHeap->array, i, i/2);
        i = i/2;
    }
}

void insert(heap *minHeap, char c, int x){
    (minHeap->size)++;
    minHeap->array[minHeap->size] = createNode();
    minHeap->array[minHeap->size]->data = c;
    minHeap->array[minHeap->size]->frequency = x;

    moveUp(minHeap, minHeap->size);
}

int getMinId(heap *minHeap, int i, int j, int k){
    int minId = i;

    if(j <= minHeap->size && minHeap->array[j]->frequency < minHeap->array[minId]->frequency) minId = j;
    if(k <= minHeap->size && minHeap->array[k]->frequency < minHeap->array[minId]->frequency) minId = k;

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

node *deleteMin(heap *minHeap){
    node *answer = minHeap->array[1];
    minHeap->array[1] = minHeap->array[minHeap->size];

    (minHeap->size)--;
    moveDown(minHeap, 1);

    return answer;
}

void insert(heap *minHeap, node *element){
    (minHeap->size)++;
    minHeap->array[minHeap->size] = element;

    moveUp(minHeap, minHeap->size);
}

void assignStrings(node *head, string *output, string s){
    if(head->data != '.'){
        output[ (head->data)-'a' ] = s;
        return;
    }

    assignStrings(head->left, output, s+"0");
    assignStrings(head->right, output, s+"1");
}

void buildOutput(heap *minHeap, string *output){
    while(minHeap->size > 1){

        node *ans1 = deleteMin(minHeap);
        node *ans2 = deleteMin(minHeap);

        // cout << ans1->data << " " << ans2->data << endl;

        node *answer = createNode();
        answer->data = '.';
        answer->frequency = ans1->frequency + ans2->frequency;
        answer->left = ans1;
        answer->right = ans2;

        insert(minHeap, answer);
    }

    assignStrings(minHeap->array[1], output, "");
}

int main(){
    string input;
    cin >> input;

    char *letter = new char[26];
    for(int i = 0; i < 26; i++) letter[i] = 0;
    for(int i = 0; i < input.length(); i++) letter[ input[i]-'a' ]++;

    heap *minHeap = createHeap(26);

    for(int i = 0; i < 26; i++){
        if(letter[i] > 0){
            insert(minHeap, 'a'+i, letter[i]);
        }
    }

    delete[] letter;

    // for(int i = 1; i <= minHeap->size; i++){
    //     cout << minHeap->array[i]->data << " " << minHeap->array[i]->frequency << endl;
    // }

    string *output = new string[26];
    for(int i = 0; i < 26; i++) output[i] = "";

    buildOutput(minHeap, output);

    for(int i = 0; i < 26; i++){
        if(output[i] != ""){
            cout << char('a'+i) << " " << output[i] << endl;
        }
    }

    delete[] output;
    delete[] minHeap;
}

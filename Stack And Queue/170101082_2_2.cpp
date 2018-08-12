#include <iostream>
#include <fstream>
using namespace std;

// Node to store the count of span and the maximum element for the consecutive previous days
// for given day
typedef struct node{
    int count;
    int max;
    struct node *next;
} node;


// Stack using linked list
typedef struct stack{
    node *head;
    int size;
} stack;


// Create a node by allocating memory and assign respected max and count values to it
node *createElement(int newCount, int newMax){
    node *newElement = new node;
    newElement->count = newCount;
    newElement->max = newMax;
    newElement->next = NULL;
    return newElement;
}

// Create a stack be allocating memory
stack *createStack(){
    stack *s = new stack;
    s->head = NULL;
    s->size = 0;
    return s;
}

// Push the elements to the given stack
void push(stack *s, int count, int max){
    node *newElement = createElement(count, max);
    newElement->next = s->head;
    s->head = newElement;
    (s->size)++;
}


// Pop from the given stack
void pop(stack *s){

    // If there is no element in the stack, return NULL
    if(s->head == NULL) return;

    node *removeElem = s->head;
    s->head = removeElem->next;
    delete removeElem;
    (s->size)--;
}


// Return the topmost element of the given stack
node *top(stack *s){
    return s->head;
}

int *stockSpan(int *input, int n){

    // Output array to store the span of each stock on given day
    int *output = new int[n];
    // Creating stack
    stack *s = createStack();

    for(int i = 0; i < n; i++){
        int currElem = input[i];
        int span = 1;

        // if(s->size == 0){
        //     push(s, span, currElem);
        //     output[i] = 1;
        //     continue;
        // }

        while(1){
            // The topmost element in the stack
            node *topElem = top(s);

            // If size of stack is 0 or topmost max element of the stack is greater than current
            // element, then save the current span and push it into the stack
            if(s->size == 0 || topElem->max > currElem){
                push(s, span, currElem);
                output[i] = span;
                break;
            }
            // If topmost max element of the stack is less than or equal to current element,
            // then add its span to current span and pop it
            else{
                span += topElem->count;
                // if(s->size == 0) cout << "Incorrect pop" << endl;
                pop(s);
            }
        }
    }

    // Deallocating the memory used
    delete s;

    // Return output
    return output;
}

int main(){
    // Debugging code: Checking the functioning of stack
    // stack *s = createStack();
    // push(s, 1, 1);
    // push(s, 2, 2);
    // node *n = top(s);
    // pop(s);
    // n = top(s);


    // Inputting the file using ifstream for input
    ifstream inputFile;
    inputFile.open("input.txt");

    // Size of the input array
    int n;
    inputFile >> n;

    // Input array to store the stock on each day
    int *input = new int[n];
    for(int i = 0; i < n; i++) inputFile >> input[i];

    // for(int i = 0; i < n; i++) cout << input[i] << " ";
    // cout << endl;

    // Output array to store the span of each stock on given day
    int *output = stockSpan(input, n);

    // Printing the output
    cout << "Day\tPrice\tSpan" << endl;
    for(int i = 0; i < n; i++){
        printf("%2d\t%3d\t%2d\n", i, input[i], output[i]);
    }


    // Deallocating the memory used
    inputFile.close();
    delete[] input;
    delete[] output;
}

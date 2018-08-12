#include <iostream>
#include <stdio.h>
using namespace std;

// Declaration of a node in the linked list
typedef struct node{
    char data;
    struct node *next;
} node;

// Create a node by allocating memory and initialize its variables
node *createNode(char element){
    node *newElement = new node;
    newElement->data = element;
    newElement->next = NULL;
    return newElement;
}


// Search for a given element and return the index of the element in the linked list.
// If not found, return -1
int search(node *head, char element){
    node  *temp = head;
    int count = 0;
    while(temp != NULL){
        count++;
        if(temp->data == element) return count;
        temp = temp->next;
    }
    return -1;
}


// Insert an element at the end of the linked list
void insertAtEnd(node *head, char element, int *comparison){
    int count = 0;
    node *temp = head;
    count++;

    // Travel to the end of the list
    while(temp->next != NULL){
        count++;
        temp = temp->next;
    }

    // Add the number of counts to the total comparisons made
    *comparison += count;

    node *newElement = createNode(element);
    temp->next = newElement;
}

// Insert an element at the start of the linked list
node *insertAtStart(node *head, char element){
    node *prev = NULL;
    node *temp = head;

    while(temp != NULL){
        if(temp->data == element) break;
        prev = temp;
        temp = temp->next;
    }

    // If the element is already present at the start of the linked list
    if(temp == head){
        return head;
    }

    prev->next = temp->next;
    temp->next = head;
    head = temp;
    return head;
}


// Move-To-Front approach of arranging the linked list
node *moveToFront(FILE *fileP, int *comparison){
    char element;
    fscanf(fileP, "%c", &element);

    node *head = createNode(element);

    while(1){
        fscanf(fileP, "%c", &element);

        if(element == ' ') continue;
        if(element == EOF || element == '\n') break;

        // Searching the element in the linked list
        int count = search(head, element);
        if(count == -1){
            insertAtEnd(head, element, comparison);
        }
        else{
            *comparison += count;
            head = insertAtStart(head, element);
        }
    }

    return head;
}

// Print the linked list in a single line
void printList(node *head){
    node *temp = head;
    while(temp != NULL){
        cout << temp->data << " ";
        temp = temp->next;
    }
}

// Swap the given element and its predecessor required for Transpose method
node *swap(node *head, char element){
    // prev points to the previous element pointed by temp
    // prev2 points to the 2nd last element pointed by temp
    node *prev2 = NULL;
    node *prev = NULL;
    node *temp = head;

    while(temp != NULL){
        if(temp->data == element) break;
        prev2 = prev;
        prev = temp;
        temp = temp->next;
    }

    // If the element is already at the start of the linked list
    if(temp == head) return head;
    // If the element's index is 2
    else if(prev == head){
        head = temp;
        prev->next = temp->next;
        temp->next = prev;
    }
    else{
        prev2->next = temp;
        prev->next = temp->next;
        temp->next = prev;
    }

    return head;
}

// Transpose approach to arrange the linked list
node *transpose(FILE *fileP, int *comparison){
    char element;
    fscanf(fileP, "%c", &element);

    node *head = createNode(element);

    while(1){
        fscanf(fileP, "%c", &element);

        if(element == ' ') continue;
        if(element == EOF || element == '\n') break;

        int count = search(head, element);
        if(count == -1){
            insertAtEnd(head, element, comparison);
        }
        else{
            *comparison += count;
            head = swap(head, element);
        }
    }

    return head;
}


int main(){
    FILE *fileP = fopen("input.txt", "r"); // Declaring the file pointer

    int comparison = 0; // Initializing comparison variable to 0

    // Move-To-Front approach
    node *head = moveToFront(fileP, &comparison);
    cout << "MoveToFront ";
    printList(head);
    cout << comparison << endl;
    fclose(fileP);

    // Transpose approach
    fileP = fopen("input.txt", "r");
    comparison = 0;
    head = transpose(fileP, &comparison);
    cout << "Transpose ";
    printList(head);
    cout << comparison << endl;
    fclose(fileP);
}

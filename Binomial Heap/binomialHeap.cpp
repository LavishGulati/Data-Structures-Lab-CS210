#include <iostream>
#include <fstream>
using namespace std;

struct node{
    int data;
    int degree;
    struct node *parent;
    struct node *child;
    struct node *sibling;
};

node *createNode(int element){
    node *newNode = new node;
    newNode->data = element;
    newNode->degree = 0;
    newNode->parent = NULL;
    newNode->child = NULL;
    newNode->sibling = NULL;

    return newNode;
}

void printRootList(node *root){
    if(root == NULL) return;

    node *temp = root;
    while(temp != NULL){
        cout << temp->data << " ";
        printRootList(temp->child);
        temp = temp->sibling;
    }
}

int findMin(node *root){
    node *temp = root;

    int minElement = temp->data;
    while(temp != NULL){
        if(temp->data < minElement) minElement = temp->data;

        temp = temp->sibling;
    }

    return temp->data;
}

node *merge(node *root1, node *root2){
    node *temp1 = root1;
    node *temp2 = root2;

    node *newRoot, *temp;

    if(temp1->degree <= temp2->degree){
        newRoot = temp1;
        temp1 = temp1->sibling;
    }
    else{
        newRoot = temp2;
        temp2 = temp2->sibling;
    }

    temp = newRoot;

    while(temp1 != NULL && temp2 != NULL){
        if(temp1->degree <= temp2->degree){
            temp->sibling = temp1;
            temp1 = temp1->sibling;
        }
        else{
            temp->sibling = temp2;
            temp2 = temp2->sibling;
        }

        temp = temp->sibling;
    }

    while(temp1 != NULL){
        temp->sibling = temp1;
        temp1 = temp1->sibling;
        temp = temp->sibling;
    }

    while(temp2 != NULL){
        temp->sibling = temp2;
        temp2 = temp2->sibling;
        temp = temp->sibling;
    }

    return newRoot;
}

void link(node **root, node *root1, node *root2){

    if(*root == root2) *root = root1;

    root2->parent = root1;

    if(root1->sibling == root2) root1->sibling = root2->sibling;
    else root1->sibling = 

    root2->sibling = root1->child;
    root1->child = root2;
    (root1->degree)++;

}

node *unionHeap(node *root1, node *root2){
    node *newRoot = merge(root1, root2);

    // printRootList(newRoot);

    node *temp1 = newRoot;
    node *temp2 = temp1->sibling;
    node *temp3 = temp2->sibling;

    // cout << temp1->data << " " << temp2->data << " ";
    // if(temp3 != NULL) cout << temp3->data << " ";
    // cout << endl;

    while(temp3 != NULL){
        if(temp1->degree != temp2->degree){
            temp1 = temp2;
            temp2 = temp3;
            temp3 = temp3->sibling;
        }
        else if(temp1->degree == temp2->degree && temp2->degree == temp3->degree){
            temp1 = temp2;
            temp2 = temp3;
            temp3 = temp3->sibling;
        }
        else{
            if(temp1->data < temp2->data) link(&newRoot, temp1, temp2);
            else link(&newRoot, temp2, temp1);

            temp2 = temp1->sibling;
            temp3 = temp2->sibling;
        }
    }

    if(temp1->degree == temp2->degree){
        if(temp1->data < temp2->data) link(&newRoot, temp1, temp2);
        else link(&newRoot, temp2, temp1);
    }

    return newRoot;
}

node *insert(node *root, int element){
    node *newNode = createNode(element);
    node *newRoot = unionHeap(root, newNode);

    return newRoot;
}

int main(){
    int n;
    cin >> n;

    int firstElement;
    cin >> firstElement;
    node *root = createNode(firstElement);

    for(int i = 0; i < n-1; i++){
        int element;
        cin >> element;
        root = insert(root, element);
    }

    printRootList(root);
    cout << endl;
}

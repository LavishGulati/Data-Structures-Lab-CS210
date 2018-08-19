#include <iostream>
#include <fstream>
using namespace std;

typedef struct node{
    int data;
    struct node *left;
    struct node *right;
    struct node *parent;
} node;

node *createNode(int element){
    node *newNode = new node;
    newNode->data = element;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = NULL;
    return newNode;
}

void insertInBST(node *root, int element){
    node *temp = root;
    node *prev = NULL;

    while(temp != NULL){
        if(element < temp->data){
            prev = temp;
            temp = temp->left;
        }
        else{
            prev = temp;
            temp = temp->right;
        }
    }

    node *newNode = createNode(element);
    newNode->parent = prev;

    if(element < prev->data) prev->left = newNode;
    else prev->right = newNode;
}

node *createBST(){
    ifstream inputFile;
    inputFile.open("input.txt");

    int element;
    inputFile >> element;

    node *root = createNode(element);

    while(1){
        inputFile >> element;
        if(inputFile.eof()) break;

        insertInBST(root, element);
    }

    return root;
}

node *maximum(node *root){
    node *temp = root;
    while(temp->right != NULL) temp = temp->right;
    return temp;
}

node *find(node *root, int element){
    if(root == NULL) return NULL;

    if(root->data == element) return root;

    if(element < root->data) return find(root->left, element);
    else return find(root->right, element);
}

int findPredecessor(node *root, int element){
    node *temp = find(root, element);
    // cout << temp->data << endl;

    if(temp->left != NULL){
        // cout << "temp->left is not NULL" << endl;
        return maximum(temp->left)->data;
    }

    node *parentNode = temp->parent;
    while(parentNode != NULL && parentNode->right != temp){
        temp = parentNode;
        parentNode = temp->parent;
    }
    return parentNode->data;
}

int main(){
    node *root = createBST();

    cout << findPredecessor(root, 39) << endl;
}

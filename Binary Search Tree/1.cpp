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

node *minimumInBST(node *root){
    node *temp = root;

    while(temp->left != NULL) temp = temp->left;

    return temp;
}

node *findSuccessor(node *root){
    node *temp = root;

    if(temp->right != NULL){
        return minimumInBST(temp->right);
    }
    else{
        node *parentNode = temp->parent;
        while(parentNode != NULL && temp == parentNode->right){
            temp = parentNode;
            parentNode = parentNode->parent;
        }
        return parentNode;
    }
}

void deleteNode(node *root){
    node *parentNode = root->parent;

    if(root->data < parentNode->data) parentNode->left = NULL;
    else parentNode->right = NULL;

    delete root;
}

node *deleteFromBST(node *root, int element){
    node *temp = root;

    while(temp != NULL && temp->data != element){
        if(element < temp->data) temp = temp->left;
        else temp = temp->right;
    }

    if(temp == NULL) return root;

    if(temp->left == NULL && temp->right == NULL){
        deleteNode(temp);
    }
    else if(temp->left != NULL && temp->right != NULL){
        node *successor = findSuccessor(temp);

        temp->data = successor->data;

        deleteNode(successor);
    }
    else{
        node *parentNode = temp->parent;
        node *child = (temp->right) != NULL ? temp->right : temp->left;

        if(element < parentNode->data) parentNode->left = child;
        else parentNode->right = child;

        child->parent = parentNode;
        delete temp;
    }

    return root;
}

void inorder(node *root){
    if(root == NULL) return;

    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

int main(){
    node *root = createBST();
    inorder(root);
    cout << endl;

    root = deleteFromBST(root, 25);
    inorder(root);
    cout << endl;
}

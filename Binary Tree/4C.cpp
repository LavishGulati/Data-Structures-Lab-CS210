#include <iostream>
#include <fstream>
using namespace std;

typedef struct node{
    int data;
    struct node *left;
    struct node *right;
    bool rightThread;
} node;

node *createNode(int element){
    node *newNode = new node;
    newNode->data = element;
    newNode->right = NULL;
    newNode->left = NULL;
    newNode->rightThread = false;
    return newNode;
}

node *find(node *root, int element){
    if(root == NULL) return NULL;

    if(root->data == element) return root;

    node *leftAns = find(root->left, element);
    if(leftAns != NULL) return leftAns;

    if(root->rightThread == false) return find(root->right, element);

    return NULL;
}

node *createThreadedBT(){
    ifstream inputFile;
    inputFile.open("input.txt");

    int element;
    int parent;
    char side;

    inputFile >> element >> parent >> side;
    node *root = createNode(element);

    while(1){
        inputFile >> element >> parent >> side;
        if(element == -1 && parent == -1) break;

        node *newNode = createNode(element);

        node *parentNode = find(root, parent);

        if(side == 'L'){
            parentNode->left = newNode;
            newNode->right = parentNode;
            newNode->rightThread = true;
        }
        else if(side == 'R'){
            newNode->right = parentNode->right;
            parentNode->right = newNode;
            parentNode->rightThread = false;
            newNode->rightThread = true;
        }
    }

    inputFile.close();
    return root;
}

void inorder(node *root){
    node *temp = root;
    node *temp2 = NULL;

    while(1){
        while(temp != NULL){
            temp2 = temp;
            temp = temp->left;
        }

        while(temp2->rightThread == true){
            cout << temp2->data << " ";
            temp = temp2;
            temp2 = temp2->right;
        }

        cout << temp2->data << endl;
        temp = temp2->right;

        if(temp2 == NULL) break;
    }
}

int main(){
    node *root = createThreadedBT();

    cout << "Inorder" << endl;
    inorder(root);
    cout << endl;
}

#include <iostream>
#include <fstream>
using namespace std;

typedef struct node{
    int data;
    struct node *left;
    struct node *right;
} node;

node *createNode(int element){
    node *newNode = new node;
    newNode->data = element;
    newNode->left = NULL;
    newNode->right = NULL;
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

    if(element < prev->data) prev->left = newNode;
    else prev->right = newNode;
}

node *createBST(int flag){
    ifstream inputFile;
    if(flag == 1) inputFile.open("input1.txt");
    else inputFile.open("input2.txt");

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

bool compareBST(node *root1, node *root2){
    if(root1 == NULL && root2 == NULL) return true;
    if(root1 == NULL || root2 == NULL) return false;

    if(root1->data != root2->data) return false;

    if(!compareBST(root1->left, root2->left)) return false;
    if(!compareBST(root1->right, root2->right)) return false;

    return true;
}

int main(){

    node *root1 = createBST(1);
    node *root2 =createBST(2);

    cout << compareBST(root1, root2) << endl;
}

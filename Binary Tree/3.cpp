#include <iostream>
#include <fstream>
#include <cstdlib>
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

node *insertInBST(node *root, int element){
    if(root == NULL){
        root = createNode(element);
        return root;
    }

    if(element < root->data){
        node *newNode = insertInBST(root->left, element);
        root->left = newNode;
    }
    else{
        node *newNode = insertInBST(root->right, element);
        root->right = newNode;
    }

    return root;
}

void deleteTree(node *root){
    if(root == NULL) return;

    deleteTree(root->left);
    deleteTree(root->right);

    delete root;
}

int height(node *root){
    if(root == NULL) return 0;

    int leftAns = 1+height(root->left);
    int rightAns = 1+height(root->right);

    return max(leftAns, rightAns);
}

int main(){
    node *root = NULL;
    srand((unsigned)time(0));
    for(int i = 0; i < 100; i++){
        int element = rand();
        root = insertInBST(root, element);
    }

    cout << "Height of the binary tree:" << endl;
    cout << height(root) << endl;

    deleteTree(root);
}

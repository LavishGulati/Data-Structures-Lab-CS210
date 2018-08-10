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

void inorder(node *root){
    if(root == NULL) return;

    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

void preorder(node *root){
    if(root == NULL) return;

    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

void postorder(node *root){
    if(root == NULL) return;

    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

int main(){
    node *root = NULL;
    srand((unsigned)time(0));
    for(int i = 0; i < 25; i++){
        int element = rand()%1000;
        root = insertInBST(root, element);
    }

    cout << "Inorder: ";
    inorder(root);
    cout << endl << endl;
    cout << "Preorder: ";
    preorder(root);
    cout << endl << endl;
    cout << "Postorder: ";
    postorder(root);
    cout << endl << endl;

    deleteTree(root);
}

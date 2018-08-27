#include <iostream>
#include <fstream>
using namespace std;

// Node of a tree which contains the data, pointer to the left node and pointer to the right node
// of the tree
struct node{
    int data;
    node *left;
    node *right;
};

// Creates a node by allocating memory and assigning given value to the data of the node
node *createNode(int element){
    node *newNode = new node;
    newNode->data = element;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Inserts an element into the binary search tree recursively
node *insertInBST(node *root, int element){

    // If root is NULL then make the new node with given element and return it
    if(root == NULL){
        node *newNode = createNode(element);
        return newNode;
    }

    // If the element is less than the data of the root, insert the element into the left subtree of
    // the root
    if(element < root->data){
        node *leftChild = insertInBST(root->left, element);
        root->left = leftChild;
    }
    // If the element is greater than or equal to the data of the root, insert the element into
    // the right subtree of the root
    else{
        node *rightChild = insertInBST(root->right, element);
        root->right = rightChild;
    }

    // Return the root once the element has been inserted
    return root;
}

// Given two values k1 and k2, print all the keys in range [k1, k2] in the given binary search tree
// in increasing order (recursively)
void printInRange(node *root, int k1, int k2){

    // If root is NULL, then return as there is nothing to print
    if(root == NULL) return;

    // If data of the root is less than k1, then all keys in the left subtree of the root are smaller
    // than k1, hence search keys in the right subtree only
    if(root->data < k1){
        printInRange(root->right, k1, k2);
    }
    // If data of the root is greater than k2, then all keys in the right subtree of the root are
    // greater tham k2, hence search keys in the left subtree only
    else if(root->data > k2){
        printInRange(root->left, k1, k2);
    }
    // If not the above cases, then search in both subtrees and print the data of the root after
    // searching in left subtree
    else{
        printInRange(root->left, k1, k2);
        cout << root->data << " ";
        printInRange(root->right, k1, k2);
    }
}

// Print inorder traversal of the given binary seacrh tree
void inorder(node *root){
    if(root == NULL) return;

    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

// Given two values k1 and k2, print all the keys in range [k1, k2] in the given binary search tree
// in increasing order (Calls another function with given values of k1 and k2)
void printInRange(node *root, ifstream *inputFile){
    int k1, k2;
    *inputFile >> k1 >> k2;

    printInRange(root, k1, k2);
}

// Create a binary search tree by inputting elements from a file
node *createBST(ifstream *inputFile){

    // Total number of nodes in the binary search tree
    int n;
    *inputFile >> n;

    int element;
    *inputFile >> element;

    // Create the root of the tree with the first input
    node *root = createNode(element);

    // Input elements and insert them into the binary search tree
    for(int i = 1; i < n; i++){
        *inputFile >> element;

        root = insertInBST(root, element);
    }

    // Return the root of the tree
    return root;
}

int main(){

    // Initializing input file
    ifstream inputFile;
    inputFile.open("TestCase_1.txt");

    // Create the binary search tree
    node *root = createBST(&inputFile);


    // Print in range function using the input file and the root of the tree
    cout << "Print in range: ";
    printInRange(root, &inputFile);
    cout << endl;

    cout << "Inorder: ";
    inorder(root);
    cout << endl;
}

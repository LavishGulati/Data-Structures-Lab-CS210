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

node *constructBT(int *preorder, int ps, int pe, int *inorder, int is, int ie){
    if(ps > pe || is > ie) return NULL;

    node *root = createNode(preorder[ps]);

    int rootId;
    for(int i = is; i <= ie; i++){
        if(inorder[i] == root->data){
            rootId = i;
            break;
        }
    }

    node *leftSubTree = constructBT(preorder, ps+1, ps+rootId-is, inorder, is, rootId-1);
    node *rightSubtree = constructBT(preorder, ps+rootId-is+1, pe, inorder, rootId+1, ie);

    root->left = leftSubTree;
    root->right = rightSubtree;

    return root;
}

void inorderTraversal(node *root){
    if(root == NULL) return;

    inorderTraversal(root->left);
    cout << root->data << " ";
    inorderTraversal(root->right);
}

int main(){
    ifstream inputFile;
    inputFile.open("preorder.txt");
    int n;
    inputFile >> n;

    int *preorder = new int[n];
    for(int i = 0; i < n; i++) inputFile >> preorder[i];

    inputFile.close();

    inputFile.open("inorder.txt");
    inputFile >> n;

    int *inorder = new int[n];
    for(int i = 0; i < n; i++) inputFile >> inorder[i];

    inputFile.close();

    node *root = constructBT(preorder, 0, n-1, inorder, 0, n-1);

    inorderTraversal(root);
    cout << endl;
}

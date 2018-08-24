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

/*
node *constructBT2(int *preorder, int ps, int *inorder, int is, int length){
    if(length <= 0) return NULL;

    // if(length == 1){
    //     node *root = createNode(preorder[ps]);
    //     return root;
    // }

    node *root = createNode(preorder[ps]);

    int rootId;
    for(int i = is; i < is+length; i++){
        if(inorder[i] == root->data){
            rootId = i;
            break;
        }
    }

    int leftLength = rootId-is;
    int rightLength = length-rootId-1;

    node *leftChild = constructBT2(preorder, ps+1, inorder, is, leftLength);
    node *rightChild = constructBT2(preorder, ps+leftLength+1, inorder, rootId+1, rightLength);
    root->left = leftChild;
    root->right = rightChild;

    return root;
}
*/

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
    // node *root2 = constructBT2(preorder, 0, inorder, 0, n);

    inorderTraversal(root);
    cout << endl;
    // inorderTraversal(root2);
    // cout << endl;
}

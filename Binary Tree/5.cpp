#include <iostream>
#include <fstream>
#include <ctime>
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


// Time complexity: O(h)
int LCAinBST(node *root, int v, int w){
    if(root == NULL) return -1;

    if(root->data == v || root->data == w) return root->data;

    if(v < root->data && w < root->data){
        return LCAinBST(root->left, v, w);
    }
    else if(v >= root->data && w >= root->data){
        return LCAinBST(root->right, v, w);
    }
    else{
        return root->data;
    }
}

bool find(node *root, int v, int w){
    if(root == NULL) return false;

    if(root->data == v || root->data == w) return true;

    return find(root->right, v, w) || find(root->left, v, w);
}


// Time complexity: O(n^2)
int LCA(node *root, int v, int w){
    if(root == NULL) return -1;

    if(root->data == v || root->data == w) return root->data;

    bool leftAns = find(root->left, v, w);
    bool rightAns = find(root->right, v, w);

    if(leftAns && !rightAns){
        return LCA(root->left, v, w);
    }
    else if(!leftAns && rightAns){
        return LCA(root->right, v, w);
    }
    else{
        return root->data;
    }
}

// Time Complexity: O(n)
int LCA2(node *root, int v, int w){
    if(root == NULL) return -1;

    if(root->data == v || root->data == w) return root->data;

    int leftAns = LCA2(root->left, v, w);
    int rightAns = LCA2(root->right, v, w);

    if(leftAns != -1 && rightAns != -1) return root->data;
    else if(leftAns == -1) return rightAns;
    else return leftAns;
}

int main(){
    node *root = NULL;
    int v, w;

    srand((unsigned)time(0));
    for(int i = 0; i < 25; i++){
        int element = rand()%1000;

        if(i == 7) v = element;
        if(i == 19) w = element;

        root = insertInBST(root, element);
    }


    // int n;
    // cin >> n;
    // for(int i = 0; i < n; i++){
    //     int element;
    //     cin >> element;
    //     root = insertInBST(root, element);
    // }
    //
    // cin >> v >> w;

    int start = clock();
    cout << LCAinBST(root, v, w) << " ";
    int stop = clock();
    cout << (stop-start)/double(CLOCKS_PER_SEC)*1000 << endl;

    start = clock();
    cout << LCA(root, v, w) << " ";
    stop = clock();
    cout << (stop-start)/double(CLOCKS_PER_SEC)*1000 << endl;

    start = clock();
    cout << LCA2(root, v, w) << " ";
    stop = clock();
    cout << (stop-start)/double(CLOCKS_PER_SEC)*1000 << endl;

    deleteTree(root);
}

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <climits>
using namespace std;

typedef struct node{
    int data;
    struct node *left;
    struct node *right;
} node;

typedef struct level{
    int smallest;
    int largest;
} level;

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

level findMinMaxLevel(node *root, int depth){
    if(root == NULL){
        level answer;
        answer.smallest = INT_MAX;
        answer.largest = INT_MIN;
        return answer;
    }

    if(root->left == NULL && root->right == NULL){
        level answer;
        answer.smallest = depth;
        answer.largest = depth;
        return answer;
    }

    level leftAns = findMinMaxLevel(root->left, depth+1);
    level rightAns = findMinMaxLevel(root->right, depth+1);
    level answer;
    answer.smallest = min(leftAns.smallest, rightAns.smallest);
    answer.largest = max(leftAns.largest, rightAns.largest);
    return answer;
}

void deleteTree(node *root){
    if(root == NULL) return;

    deleteTree(root->left);
    deleteTree(root->right);

    delete root;
}

int main(){
    int *difference = new int[100];
    for(int i = 0; i < 100; i++) difference[i] = 0;

    for(int j = 0; j < 50; j++){
        node *root = NULL;

        // srand((unsigned)time(0));
        for(int i = 0; i < 100; i++){
            int element = rand();
            root = insertInBST(root, element);
        }

        level answer = findMinMaxLevel(root, 0);
        difference[answer.largest-answer.smallest]++;
        // cout << "Smallest level in the tree is: " << answer.smallest << endl;
        // cout << "Largest level in the tree is: " << answer.largest << endl;

        deleteTree(root);
    }

    cout << "Frequency of difference between maximum and minimum levels" << endl;
    for(int i = 0; i < 100; i++){
        if(difference[i] != 0){
            printf("%3d: %2d\n", i, difference[i]);
            // cout << i << ": " << difference[i] << endl;
        }
    }
}

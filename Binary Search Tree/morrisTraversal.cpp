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

void morrisInorder(node *root){
    node *temp = root;
    while(temp != NULL){
        if(temp->left == NULL){
            cout << temp->data << " ";
            temp = temp->right;
        }
        else{
            node *temp2 = temp->left;
            while(temp2->right != NULL && temp2->right != temp){
                temp2 = temp2->right;
            }

            if(temp2->right == NULL){
                temp2->right = temp;
                temp = temp->left;
            }
            else{
                cout << temp->data << " ";
                temp2->right = NULL;
                temp = temp->right;
            }
        }
    }
    cout << endl;
}

void morrisPreorder(node *root){
    node *temp = root;
    while(temp != NULL){
        // cout << temp->data << " ";
        if(temp->left == NULL){
            cout << temp->data << " ";
            temp = temp->right;
        }
        else{
            node *temp2 = temp->left;
            while(temp2->right != NULL && temp2->right != temp){
                temp2 = temp2->right;
            }

            if(temp2->right == NULL){
                cout << temp->data << " ";
                temp2->right = temp;
                temp = temp->left;
            }
            else{
                // cout << temp->data << " ";
                temp2->right = NULL;
                temp = temp->right;
            }
        }
    }
    cout << endl;
}

void morrisPostorder(node *root){
    node *temp = root;

    node *dummyNode = createNode(0);
    dummyNode->left = temp;

    temp = dummyNode;

    while(temp != NULL){
        if(temp->left == NULL) temp = temp->right;
        else{
            node *temp2 = temp->left;
            while(temp2->right != NULL && temp2->right != temp){
                temp2 = temp2->right;
            }

            if(temp2->right == NULL){
                temp2->right = temp;
                temp = temp->left;
            }
            else{
                node *first = temp;
                node *middle = temp->left;
                node *last;
                while(middle != temp){
                    last = middle->right;
                    middle->right = first;
                    first = middle;
                    middle = last;
                }

                first = temp;
                middle = temp2;
                while(middle != temp){
                    cout << middle->data << " ";
                    last = middle->right;
                    middle->right = first;
                    first = middle;
                    middle = last;
                }

                temp2->right = NULL;
                temp = temp->right;
            }
        }
    }

    cout << endl;
}

int main(){
    node *root = createBST();

    cout << "Inorder: ";
    morrisInorder(root);

    cout << "Preorder: ";
    morrisPreorder(root);

    cout << "Postorder: ";
    morrisPostorder(root);
}

#include <bits/stdc++.h>
using namespace std;

class node{
    int data;
    int leftHeight;
    int rightHeight;
    node *parent;
    node *left;
    node *right;

    friend class avlTree;

    node(int key){
        data = key;
        leftHeight = 0;
        rightHeight = 0;
        parent = NULL;
        left = NULL;
        right = NULL;
    }

    void updateHeight(){
        if(left == NULL) leftHeight = 0;
        else{
            leftHeight = max(left->leftHeight, left->rightHeight)+1;
        }

        if(right == NULL) rightHeight = 0;
        else{
            rightHeight = max(right->leftHeight, right->rightHeight)+1;
        }
    }
};

class avlTree{
    node *root;

    // void updateHeight(node *head){
    //     if(head->left == NULL) head->leftHeight = 0;
    //     else{
    //         head->leftHeight = max(head->left->leftHeight, head->left->rightHeight)+1;
    //     }
    //
    //     if(head->right == NULL) head->rightHeight = 0;
    //     else{
    //         head->rightHeight = max(head->right->leftHeight, head->right->rightHeight)+1;
    //     }
    // }

    node *rotateLeft(node *head){
        node *a = head;
        node *b = head->right;
        node *parent = head->parent;

        if(parent != NULL){
            if(parent->right == a) parent->right = b;
            else parent->left = b;
        }
        b->parent = parent;


        a->right = b->left;
        if(b->left != NULL) b->left->parent = a;

        b->left = a;
        a->parent = b;

        a->updateHeight();
        b->updateHeight();

        head = b;
        return head;
    }

    node *rotateRight(node *head){
        node *a = head;
        node *b = head->left;
        node *parent = head->parent;

        if(parent != NULL){
            if(parent->left == a) parent->left = b;
            else parent->right = b;
        }
        b->parent = parent;

        a->left = b->right;
        if(b->right != NULL) b->right->parent = a;

        b->right = a;
        a->parent = b;

        a->updateHeight();
        a->updateHeight();

        head = b;
        return head;
    }

    node *rebalance(node *head){
        head->updateHeight();

        int balanceFactor = head->rightHeight - head->leftHeight;

        if(balanceFactor == -2){
            if(head->left->leftHeight >= head->left->rightHeight){
                node *newHead = rotateRight(head);
                head = newHead;
                cout << "Rotate Right" << endl;
            }
            else{
                cout << "Rotate Left Then Right" << endl;
                node *newLeft = rotateLeft(head->left);
                head->left = newLeft;
                node *newHead = rotateRight(head);
                head = newHead;
                // cout << head->left->data << " " << head->data << " " << head->right->data << endl;
                // cout << head->left->parent->data << " " << head->right->parent->data << endl;
            }
        }
        else if(balanceFactor == 2){
            if(head->right->rightHeight >= head->right->leftHeight){
                node *newHead = rotateLeft(head);
                head = newHead;
                cout << "Rotate Left" << endl;
            }
            else{
                cout << "Rotate Right Then Left" << endl;
                node *newRight = rotateRight(head->right);
                head->right = newRight;
                node *newHead = rotateLeft(head);
                head = newHead;
            }
        }

        if(head->parent == NULL) root = head;
        else{
            node *newParent = rebalance(head->parent);
            head->parent = newParent;
        }

        return head;
    }

    void inorder(node *head){
        if(head == NULL) return;

        inorder(head->left);

        cout << head->data << " ";

        if(head->left != NULL) cout << "(" << head->left->data << ") ";
        else cout << "(-) ";

        if(head->right != NULL) cout << "(" << head->right->data << ")" << endl;
        else cout << "(-)" << endl;

        inorder(head->right);
    }

public:
    avlTree(){
        root = NULL;
    }

    bool insertNode(int key){
        if(root == NULL){
            root = new node(key);
            return true;
        }

        node *prev = NULL;
        node *temp = root;

        while(temp != NULL){
            if(temp->data == key) return false;

            prev = temp;

            if(key < temp->data) temp = temp->left;
            else temp = temp->right;
        }

        node *newNode = new node(key);
        newNode->parent = prev;
        if(key > prev->data) prev->right = newNode;
        else prev->left = newNode;

        // rebalance(prev->parent);
        rebalance(prev);

        // cout << root->data << endl;
        // cout << root->parent << endl;
        // if(root->left != NULL){
        //     cout << "L: " << root->left->data << endl;
        //     cout << "LP: " << root->left->parent->data << endl;
        //     cout << "LL: " << root->left->left << endl;
        //     cout << "LR: " << root->left->right << endl;
        // }
        // if(root->right != NULL){
        //     cout << "R: " << root->right->data << endl;
        //     cout << "RP: " << root->right->parent->data << endl;
        //     cout << "RL: " << root->right->left << endl;
        //     cout << "RR: " << root->right->right << endl;
        // }
        return true;
    }

    void inorder(){
        inorder(root);
        cout << endl;
    }
};

int main(){
    avlTree *tree = new avlTree();

    int choice;
    do{
        cout << "1. Create new tree" << endl;
        cout << "2. Add new key to the tree" << endl;
        cout << "3. Search a key in the tree" << endl;
        cout << "4. Delete a key from the tree" << endl;
        cout << "5. Inorder traversal of the tree" << endl;
        cout << "Any other choice to exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cout << endl;

        switch(choice){
            case 1:
                if(tree != NULL){
                    delete tree;
                }
                tree = new avlTree();
                break;

            case 2:
                if(tree == NULL){
                    cout << "Create a tree first" << endl;
                    break;
                }
                int key;
                cout << "Enter key to add: ";
                cin >> key;
                if(tree->insertNode(key)){
                    cout << "Inserted key: " << key << endl;
                }
                else cout << "Could not insert key" << endl;
                cout << endl;
                break;

            case 5:
                if(tree == NULL){
                    cout << "Create a new tree first" << endl;
                    break;
                }
                tree->inorder();
                break;

            default:
                return 0;
        }
    } while(true);
}

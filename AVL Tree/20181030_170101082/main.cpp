#include <bits/stdc++.h>
using namespace std;
#define pb push_back

class node{
    int data;
    int leftHeight;
    int rightHeight;
    int numLeft;
    int numRight;
    node *parent;
    node *left;
    node *right;

    friend class avlTree;

    node(int key){
        data = key;
        leftHeight = 0;
        rightHeight = 0;
        numLeft = 0;
        numRight = 0;
        parent = NULL;
        left = NULL;
        right = NULL;
    }

    void update(){
        if(left == NULL){
            leftHeight = 0;
            numLeft = 0;
        }
        else{
            leftHeight = max(left->leftHeight, left->rightHeight)+1;
            numLeft = left->numLeft + left->numRight + 1;
        }

        if(right == NULL){
            rightHeight = 0;
            numRight = 0;
        }
        else{
            rightHeight = max(right->leftHeight, right->rightHeight)+1;
            numRight = right->numLeft + right->numRight + 1;
        }
    }
};

vector<node *> helper;

class avlTree{
    node *root;

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

        a->update();
        b->update();

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

        a->update();
        b->update();

        head = b;
        return head;
    }

    void rebalance(node *head){
        head->update();

        int balanceFactor = head->rightHeight - head->leftHeight;

        if(balanceFactor == -2){
            if(head->left->leftHeight >= head->left->rightHeight){
                node *newHead = rotateRight(head);
                head = newHead;
            }
            else{
                node *newLeft = rotateLeft(head->left);
                head->left = newLeft;
                node *newHead = rotateRight(head);
                head = newHead;
            }
        }
        else if(balanceFactor == 2){
            if(head->right->rightHeight >= head->right->leftHeight){
                node *newHead = rotateLeft(head);
                head = newHead;
            }
            else{
                node *newRight = rotateRight(head->right);
                head->right = newRight;
                node *newHead = rotateLeft(head);
                head = newHead;
            }
        }

        if(head->parent == NULL) root = head;
        else{
            rebalance(head->parent);
        }
    }

    node *maximum(node *head){
        node *temp = head;
        while(temp->right != NULL) temp = temp->right;
        return temp;
    }

    node *minimum(node *head){
        node *temp = head;
        while(temp->left != NULL) temp = temp->left;
        return temp;
    }

    node *predecessor(node *head){
        if(head->left != NULL) return maximum(head->left);

        node *temp = head;
        node *parentNode = head->parent;
        while(parentNode != NULL && parentNode->right != temp){
            temp = parentNode;
            parentNode = temp->parent;
        }
        return parentNode;
    }

    void deleteNode(node *head){
        if(head != NULL){
            deleteNode(head->left);
            deleteNode(head->right);
            delete head;
        }
    }

public:
    avlTree(){
        root = NULL;
    }

    ~avlTree(){
        deleteNode(root);
    }

    bool insert(int key){
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

        rebalance(prev);

        return true;
    }

    void deleteKey(node *temp){
        node *parentNode = temp->parent;

        if(temp->left == NULL && temp->right == NULL){

            if(temp == root){
                root = NULL;
                return;
            }

            parentNode = temp->parent;
            if(parentNode->left == temp) parentNode->left = NULL;
            else parentNode->right = NULL;

            delete temp;

            rebalance(parentNode);
            return;
        }
        else if(temp->left == NULL || temp->right == NULL){

            if(temp == root){
                root = temp->left != NULL ? temp->left : temp->right;
                delete temp;
                return;
            }

            parentNode = temp->parent;
            node *childNode = temp->left == NULL ? temp->right : temp->left;

            if(parentNode->left == temp){
                parentNode->left = childNode;
                childNode->parent = parentNode;
            }
            else{
                parentNode->right = childNode;
                childNode->parent = parentNode;
            }

            delete temp;
            rebalance(parentNode);
            return;
        }

        node *pred = predecessor(temp);
        int swap = temp->data;
        temp->data = pred->data;
        pred->data = swap;

        deleteKey(pred);
    }

    void printLevelWise(){
        queue<node *> q;
        q.push(root);
        helper.pb(root);

        while(!q.empty()){
            node *currNode = q.front();
            q.pop();

            if(currNode->left != NULL){
                q.push(currNode->left);
                helper.pb(currNode->left);
            }
            if(currNode->right != NULL){
                q.push(currNode->right);
                helper.pb(currNode->right);
            }
        }
    }

    void print(){
        printLevelWise();

        cout << "Sequence of insertions: ";
        int i = 0;
        for(; i < helper.size()-1; i++) cout << helper[i]->data << ", ";
        cout << helper[i]->data << endl << endl;

        cout << "Tree structure" << endl;

        for(int i = 0; i < helper.size(); i++){
            cout << "Node: " << helper[i]->data << "  ";
            if(helper[i]->parent == NULL) cout << "Parent: NULL" << endl;
            else cout << "Parent: " << helper[i]->parent->data << endl;

            if(helper[i]->left == NULL){
                cout << "Left Child: NULL  Nodes in Left subtree: 0  ";
            }
            else{
                cout << "Left Child: " << helper[i]->left->data << "  ";
                cout << "Nodes in Left subtree: " << helper[i]->numLeft << "  ";
            }

            if(helper[i]->right == NULL){
                cout << "Right Child: NULL  Nodes in Right subtree: 0" << endl << endl;
            }
            else{
                cout << "Right Child: " << helper[i]->right->data << "  ";
                cout << "Nodes in Right subtree: " << helper[i]->numRight << endl << endl;
            }
        }
    }

    void change(node *head){
        if(head == NULL) return;

        while(head->numRight - head->numLeft > 1){
            node *minNode = minimum(head->right);
            int key = head->data;
            head->data = minNode->data;
            deleteKey(minNode);

            insert(key);
        }

        while(head->numRight - head->numLeft < 0){
            node *maxNode = maximum(head->left);
            int key = head->data;
            head->data = maxNode->data;
            deleteKey(maxNode);

            insert(key);
        }

        change(head->left);
        change(head->right);
    }

    void change(){
        change(root);
    }
};

int main(){
    avlTree *tree = new avlTree();

    int key;

    while(cin >> key){
        tree->insert(key);
    }
    tree->change();

    tree->print();

    delete tree;
}

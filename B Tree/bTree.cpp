#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair

class node{
    int *keys;
    node **children;
    int minDegree;
    int size;
    bool isLeaf;

    friend class bTree;

    node(int minDegree, bool isLeaf){
        this->keys = new int[2*minDegree-1];
        this->children = new node *[2*minDegree];

        for(int i = 0; i < 2*minDegree; i++){
            children[i] = NULL;
        }

        this->minDegree = minDegree;
        this->size = 0;
        this->isLeaf = isLeaf;
    }

    void split(int k, node *head){
        node *newNode = new node(head->minDegree, head->isLeaf);
        newNode->size = minDegree-1;

        for(int i = 0; i < minDegree-1; i++){
            newNode->keys[i] = head->keys[i+minDegree];
        }

        if(!(head->isLeaf)){
            for(int i = 0; i < minDegree; i++){
                newNode->children[i] = head->children[i+minDegree];
            }
        }

        head->size = minDegree-1;

        for(int i = size; i >= k+1; i--) children[i+1] = children[i];
        children[k+1] = newNode;

        for(int i = size-1; i >= k; i--) keys[i+1] = keys[i];
        keys[k] = head->keys[minDegree-1];
        size++;
    }

    void eagerInsert(int key){
        int i = size-1;

        if(isLeaf){
            while(i >= 0 && keys[i] > key){
                keys[i+1] = keys[i];
                i--;
            }

            keys[i+1] = key;
            size++;
        }
        else{
            while(i >= 0 && keys[i] > key) i--;

            if(children[i+1]->size == 2*minDegree-1){
                split(i+1, children[i+1]);
                if(keys[i+1] < key) i++;
            }

            children[i+1]->eagerInsert(key);
        }
    }

    pair<int, node *> splitInsert(int key){
        if(isLeaf){
            if(size == 2*minDegree-1){
                node *newNode = new node(minDegree, true);
                newNode->size = minDegree-1;
                size = minDegree-1;
                for(int i = 0; i < minDegree-1; i++){
                    newNode->keys[i] = keys[i+minDegree];
                }

                int k = keys[size];

                node *insertRoot;
                if(key < k) insertRoot = this;
                else insertRoot = newNode;

                int i = insertRoot->size - 1;
                while(i >= 0 && insertRoot->keys[i] > key){
                    insertRoot->keys[i+1] = insertRoot->keys[i];
                    i--;
                }

                insertRoot->keys[i+1] = key;
                insertRoot->size++;
                return mp(k, newNode);
            }
            else{
                int i = size-1;
                while(i >= 0 && keys[i] > key){
                    keys[i+1] = keys[i];
                    i--;
                }

                keys[i+1] = key;
                size++;
                return mp(-1, (node *)NULL);
            }
        }
        else{
            int i = size-1;
            while(i >= 0 && keys[i] > key) i--;
            pair<int, node *> p = children[i+1]->splitInsert(key);

            if(p.second == NULL) return p;
            else if(size == 2*minDegree-1){
                node *newNode = new node(minDegree, isLeaf);
                newNode->size = minDegree-1;
                size = minDegree-1;
                for(int i = 0; i < minDegree-1; i++){
                    newNode->keys[i] = keys[i+minDegree];
                }
                for(int i = 0; i < minDegree; i++){
                    newNode->children[i] = children[i+minDegree];
                }

                int k = keys[size];

                node *insertRoot;
                if(p.first < k) insertRoot = this;
                else insertRoot = newNode;

                int i = insertRoot->size - 1;
                while(i >= 0 && insertRoot->keys[i] > key){
                    insertRoot->keys[i+1] = insertRoot->keys[i];
                    insertRoot->children[i+2] = insertRoot->children[i+1];
                    i--;
                }

                insertRoot->keys[i+1] = p.first;
                insertRoot->children[i+2] = p.second;
                insertRoot->size++;
                return mp(k, newNode);
            }
            else{
                int i = size-1;
                while(i >= 0 && keys[i] > p.first){
                    keys[i+1] = keys[i];
                    children[i+2] = children[i+1];
                    i--;
                }

                keys[i+1] = p.first;
                children[i+2] = p.second;
                size++;
                return mp(-1, (node *)NULL);
            }
        }
    }

    void deleteNode(){
        if(!isLeaf){
            for(int i = 0; i <= size; i++){
                children[i]->deleteNode();
            }
        }

        delete[] keys;
        delete[] children;
    }

    node *search(int key){
        int i = 0;
        while(i < size && key > keys[i]) i++;

        if(keys[i] == key) return this;

        if(isLeaf) return NULL;

        return children[i]->search(key);
    }

    void inorder(int depth){
        if(!isLeaf){
            int i = 0;
            for(; i < size; i++){
                children[i]->inorder(depth+1);
                printf("%3d", keys[i]);
                cout << " at depth " << depth << endl;
            }
            children[i]->inorder(depth+1);
        }
        else{
            for(int i = 0; i < size; i++){
                printf("%3d", keys[i]);
                cout << " at depth " << depth << endl;
            }
        }
    }
};

class bTree{
    node *root;
    int minDegree;

    public:

        bTree(int t){
            root = NULL;
            minDegree = t;
        }

        ~bTree(){
            if(root != NULL) root->deleteNode();
        }

        void eagerInsert(int key){
            if(root == NULL){
                root = new node(minDegree, true);
                root->eagerInsert(key);
                return;
            }

            if(root->size == 2*minDegree-1){
                node *newRoot = new node(minDegree, false);
                newRoot->children[0] = root;

                newRoot->split(0, root);

                if(newRoot->keys[0] < key){
                    newRoot->children[1]->eagerInsert(key);
                }
                else newRoot->children[0]->eagerInsert(key);

                root = newRoot;
            }
            else root->eagerInsert(key);
        }

        void splitInsert(int key){
            if(root == NULL){
                root = new node(minDegree, true);
                root->splitInsert(key);
                return;
            }

            if(root->isLeaf && root->size == 2*minDegree-1){
                node *newRoot = new node(minDegree, false);
                newRoot->children[0] = root;
                newRoot->split(0, root);

                if(newRoot->keys[0] < key){
                    newRoot->children[1]->splitInsert(key);
                }
                else newRoot->children[0]->splitInsert(key);

                root = newRoot;
            }
            else{
                pair<int, node *> p = root->splitInsert(key);

                if(p.second != NULL){
                    node *newRoot = new node(minDegree, false);
                    newRoot->children[0] = root;
                    newRoot->keys[0] = p.first;
                    newRoot->children[1] = p.second;
                    newRoot->size = 1;
                    root = newRoot;
                }
            }
        }

        node *search(int key){
            if(root == NULL) return NULL;

            return root->search(key);
        }

        void inorder(){
            root->inorder(1);
        }
};

int main(){
    bTree *tree = NULL;
    int choice;
    while(1){
        cout << "1. Create a new tree\n";
        cout << "2. Add a new key to the tree\n";
        cout << "3. Search a key in the tree\n";
        cout << "4. Inorder traversal of the tree\n";
        cout << "5. Delete a key from the tree\n";
        cout << "Any other choice to exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if(choice == 1){
            if(tree != NULL) delete tree;

            cout << endl;
            int t;
            cout << "Enter the value of minimum degree: ";
            cin >> t;
            tree = new bTree(t);
            cout << "B-tree created\n\n";
        }

        else if(choice == 2){
            cout << endl;

            if(tree == NULL){
                cout << "Create a new tree first\n\n";
                continue;
            }

            int key;
            cout << "Enter key to add: ";
            cin >> key;
            // tree->eagerInsert(key);
            tree->splitInsert(key);
            cout << "Key " << key << " inserted into the B-tree\n\n";
        }

        else if(choice == 3){
            cout << endl;
            if(tree == NULL){
                cout << "Create a new tree first\n\n";
                continue;
            }

            int key;
            cout << "Enter key to search: ";
            cin >> key;
            node *result = tree->search(key);

            if(result == NULL){
                cout << "Key " << key << "not found\n\n";
            }
            else cout << "Key " << key << " found\n\n";
        }

        else if(choice == 4){
            cout << endl;
            tree->inorder();
            cout << endl;
        }

        else if(choice == 5){

        }

        else{
            cout << endl;
            break;
        }
    }
}

#include <bits/stdc++.h>
using namespace std;
#define pb push_back

bool isError=false;

class node{
    int key;
    vector<node *> children;
    int numChild;

    friend class tree;

    node(int k, int num){
        this->key = k;
        this->numChild = num;
    }

    node *search(int k){
        if(this->key == k) return this;

        for(int i = 0; i < this->children.size(); i++){
            node *result = this->children[i]->search(k);
            if(result != NULL) return result;
        }

        return NULL;
    }

    void insert(int k, int num){
        node *newNode = new node(k, num);
        this->children.pb(newNode);
    }

    bool validateDepth(int &k1, int &k2, int depth, int &result){
        if(children.size() != 0 && numChild != children.size()){
            cout << "Answer: This cannot be a valid B Tree.\n";
            cout << "Reason: " << key << " does not satisfy the requirement that Children count = Key count + 1.\n";
            isError = true;
            return false;
        }

        if(children.size() == 0){
            if(result == -1){
                k1 = key;
                result = depth;
                return true;
            }
            else if(result == depth) return true;
            else{
                k2 = key;
                return false;
            }
        }

        for(int i = 0; i < children.size(); i++){
            if(!(children[i]->validateDepth(k1, k2, depth+1, result))) return false;
        }

        return true;
    }
};

class tree{
    node *root;

    public:
        tree(){
            this->root = NULL;
        }

        bool insert(int key, int parentKey, int num){
            if(parentKey == 0){
                this->root = new node(key, num);
                return true;
            }

            node *parentNode = root->search(parentKey);
            if(parentNode == NULL){
                cout << "Answer: This cannot be a valid B Tree.\n";
                cout << "Reason: Incorrect order of given sequence\n";
                return false;
            }

            parentNode->insert(key, num);
            return true;
        }

        bool validateDepth(int &k1, int &k2){
            int result = -1;
            if(root->validateDepth(k1, k2, 0, result)) return true;
            else return false;
        }
};

int main(){
    int maxKeys;
    cin >> maxKeys;

    int t = (maxKeys+1)/2;

    int n;
    cin >> n;

    int totalChild = 0;
    tree *myTree = new tree;
    int key, parentKey, numKeys, numChild;
    for(int i = 0; i < n; i++){
        cin >> key >> parentKey >> numKeys >> numChild;

        totalChild += numChild;

        if(numKeys > maxKeys){
            cout << "Answer: This cannot be a valid B Tree.\n";
            cout << "Reason: " << key << " has more number of keys than allowed.\n";
            return 0;
        }
        else if(parentKey != 0 && numKeys < t-1){
            cout << "Answer: This cannot be a valid B Tree.\n";
            cout << "Reason: " << key << " does not have minimum occupancy.\n";
            return 0;
        }
        else if(numChild != 0 && numChild != numKeys+1){
            cout << "Answer: This cannot be a valid B Tree.\n";
            cout << "Reason: " << key << " does not satisfy the requirement that Children count = Key count + 1.\n";
            return 0;
        }

        if(!(myTree->insert(key, parentKey, numChild))) return 0;
    }

    int k1, k2;
    if(myTree->validateDepth(k1, k2)){
        if(totalChild+1 != n){
            cout << "Answer: This cannot be a valid B Tree.\n";
            cout << "Reason: Total number of nodes in B-tree is not equal to n.\n";
            return 0;
        }

        cout << "Answer: This can be a valid B Tree.\n";
    }
    else{
        if(!isError){
            cout << "Answer: This cannot be a valid B Tree.\n";
            cout << "Reason: " << k1 << " and " << k2 << " are a pair of leaf nodes that do not have the same depth.\n";
        }
    }
}

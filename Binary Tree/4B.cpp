#include <iostream>
#include <fstream>
using namespace std;

typedef struct treeNode{
    int data;
    treeNode *left;
    treeNode *right;
} treeNode;

typedef struct stackNode{
    treeNode *data;
    struct stackNode *next;
} stackNode;

typedef struct stack{
    stackNode *head;
    int size;
} stack;

stackNode *createStackNode(treeNode *element){
    stackNode *newStackNode = new stackNode;
    newStackNode->data = element;
    newStackNode->next = NULL;
    return newStackNode;
}

stack *createStack(){
    stack *s = new stack;
    s->head == NULL;
    s->size = 0;
    return s;
}

treeNode *createTreeNode(int element){
    treeNode *newTreeNode = new treeNode;
    newTreeNode->data = element;
    newTreeNode->left = NULL;
    newTreeNode->right = NULL;
    return newTreeNode;
}

treeNode *insertInBST(treeNode *treeRoot, int element){
    if(treeRoot == NULL){
        treeRoot = createTreeNode(element);
        return treeRoot;
    }

    if(element < treeRoot->data){
        treeRoot->left = insertInBST(treeRoot->left, element);
    }
    else treeRoot->right = insertInBST(treeRoot->right, element);

    return treeRoot;
}

void deleteTree(treeNode *treeRoot){
    if(treeRoot == NULL) return;

    deleteTree(treeRoot->left);
    deleteTree(treeRoot->right);
    delete treeRoot;
}

void push(stack *s, treeNode *element){
    stackNode *newStackNode = createStackNode(element);
    newStackNode->next = s->head;
    s->head = newStackNode;
    (s->size)++;
}

treeNode *pop(stack *s){
    if(s->head == NULL) return NULL;

    stackNode *answer = s->head;
    s->head = answer->next;
    (s->size)--;
    return answer->data;
}

bool isEmpty(stack *s){
    if(s->size == 0) return true;
    else return false;
}

void deleteList(stackNode *head){
    if(head == NULL) return;

    deleteList(head->next);
    delete head;
}

void deleteStack(stack *s){
    deleteList(s->head);
    delete s;
}

void inorder(treeNode *treeRoot){
    stack *s = new stack;
    treeNode *temp = treeRoot;
    while(1){
        while(temp != NULL){
            push(s, temp);
            temp = temp->left;
        }

        if(!isEmpty(s)){
            temp = pop(s);
            cout << temp->data << " ";
            temp = temp->right;
        }

        if(isEmpty(s) && temp == NULL) break;
    }

    deleteStack(s);
}

void preorder(treeNode *treeRoot){
    stack *s = createStack();
    treeNode *temp = treeRoot;

    while(1){
        while(temp != NULL){
            cout << temp->data << " ";
            push(s, temp);
            temp = temp->left;
        }

        if(!isEmpty(s)){
            temp = pop(s);
            // cout << temp->data << " ";
            temp = temp->right;
        }

        if(isEmpty(s) && temp == NULL) break;
    }

    deleteStack(s);
}

treeNode *top(stack *s){
    if(s->head == NULL) return NULL;
    return s->head->data;
}

void postorder(treeNode *treeRoot){
    stack *s = createStack();
    treeNode *temp = treeRoot;

    while(1){
        while(temp != NULL){
            if(temp->right != NULL) push(s, temp->right);
            push(s, temp);
            temp = temp->left;
        }

        if(!isEmpty(s)){
            temp = pop(s);
            treeNode *temp2 = top(s);
            if(temp->right != NULL && temp2 == temp->right){
                pop(s);
                push(s, temp);
                temp = temp2;
            }
            else{
                cout << temp->data << " ";
                temp = NULL;
            }
        }

        if(isEmpty(s) && temp == NULL) break;
    }

    deleteStack(s);
}

int main(){
    treeNode *treeRoot = NULL;
    srand(unsigned(time(0)));
    for(int i = 0; i < 25; i++){
        int element = rand()%1000;
        treeRoot = insertInBST(treeRoot, element);
    }

    cout << "Inorder" << endl;
    inorder(treeRoot);
    cout << endl << endl;

    cout << "Preorder" << endl;
    preorder(treeRoot);
    cout << endl << endl;

    cout << "Postorder" << endl;
    postorder(treeRoot);
    cout << endl << endl;

    deleteTree(treeRoot);
}

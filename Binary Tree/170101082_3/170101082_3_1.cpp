#include <iostream>
#include <fstream>
using namespace std;


// Node of the binary tree which contains data, pointer to the left tree node and pointer to the right tree node
typedef struct node{
	int data;
	struct node *left;
	struct node *right;
} node;


// Create a binary tree node and assign the specified element to that node
node *createNode(int element){

	node *newNode = new node;
	
	newNode->data = element;
	newNode->right = NULL;
	newNode->left = NULL;
	
	return newNode;
	
}

// Given the root of a binary tree, find the specified element in the binary tree by recursion
node *find(node *root, int element){
	
	// If root is NULL, then the element is not found. Thus, return NULL
    if(root == NULL) return NULL;

	// If the data of the root is the specified element, return root itself
    if(root->data == element) return root;

	// Find the element in the left subtree and if found, return the answer
    node *leftAns = find(root->left, element);
    if(leftAns != NULL) return leftAns;

	// Find the element in the right subtree and if found, return the answer
	// If not found, NULL will be returned automatically
    return find(root->right, element);
    
}


// Node of the stack which contains the binary tree node and the pointer to the next stack node
typedef struct stackNode{
    node *data;
    struct stackNode *next;
} stackNode;


// Stack which contains the head pointer to the stack and its size
typedef struct stack{
    stackNode *head;
    int size;
} stack;


// Create a stack node and assign the specified binary tree node to that stack node
stackNode *createStackNode(node *element){

    stackNode *newStackNode = new stackNode;
    
    newStackNode->data = element;
    newStackNode->next = NULL;
    
    return newStackNode;
    
}


// Create a new stack
stack *createStack(){

    stack *s = new stack;
    
    s->head = NULL;
    s->size = 0;
    
    return s;
    
}


// Given a stack, push the specified element into the stack
void push(stack *s, node *element){

    stackNode *newStackNode = createStackNode(element);
    
    newStackNode->next = s->head;
    s->head = newStackNode;
    (s->size)++;
    
}

// Given a stack, pop and return the topmost element in the stack
node *pop(stack *s){

	// If there is no element in the stack, return NULL pointer
    if(s->head == NULL) return NULL;

    stackNode *answer = s->head;
    s->head = answer->next;
    (s->size)--;
    return answer->data;
    
}

// Return true if the stack is empty, else return false
bool isEmpty(stack *s){

    if(s->size == 0) return true;
    else return false;
    
}


// Create the binary tree by inputting elements from an input file
node *createBT(){

	// Opening input file using fstream	
	ifstream inputFile;
	inputFile.open("input.txt");
	
	// Number of inputs in the input file
	int n;
	inputFile >> n;
	
	// Element is the required data to be added to the tree on the left/right side of its parent
	// denoted by variable side as L/R
	int element;
	int parent;
	char side;
	
	// Adding the root data to the binary tree
	inputFile >> element >> parent >> side;
	node *root = createNode(element);
	
	
	
	for(int i = 1; i < n; i++){
		inputFile >> element >> parent >> side;
		
		// Find the parent node in the tree
		node *parentNode = find(root, parent);
		
		// Create new node with required element data
		node *newNode = createNode(element);
	
		// If parent is not found in the tree, that means we are trying to push the required data to 
		// the root of the binary tree. Hence, display the error message
		if(parentNode == NULL){
			cout << root->data << " is already present at the specified position for " << element << endl;
			continue;
		}
		
		// If the node is to be added to the left side of the parent
		if(side == 'L'){
		
			// If the parent already has the left node, display error message
			// else add the new node to the left of the parent node 
			if(parentNode->left != NULL){
				cout << parentNode->left->data << " is already present at the specified position for " << element << endl;
			}
			else{
				parentNode->left = newNode;
			}
			
		}
		// If the node is to be added to the right side of the parent
		else if(side == 'R'){
			
			// If the parent already has the right node, display error message
			// else add the new node to the right of the parent node  
			if(parentNode->right != NULL){
				cout << parentNode->right->data << " is already present at the specified position for " << element << endl; 
			}
			else{
				parentNode->right = newNode;
			}
			
		}
		
	}
	
	
	// Return the root of the tree
	return root;
}

// Return the height of the given tree recursively
int height(node *root){

	if(root == NULL) return -1;
	
	int leftAns = 1+height(root->left);
	int rightAns = 1+height(root->right);
	
	return leftAns > rightAns ? leftAns : rightAns;
}



// Print the inorder and depth of the given tree using stack without recursion
void inorder(node *root){

	// Stack to implement inorder
	stack *s = createStack();
	
	// temp which traverses the whole tree to print the inorder
	node *temp = root;
	int maxSize = 0;
	
	while(1){
	
		// while temp is not equal to NULL, push temp to the stack and move temp to the left
		while(temp != NULL){
			push(s, temp);
			if(maxSize < s->size) maxSize = s->size;
			temp = temp->left;
		}
		
		// Once temp reached NULL, pop a binary tree node from the stack and print its data
		// Also move to its right child
		temp = pop(s);
		cout << temp->data << " ";
		temp = temp->right;
		
		if(isEmpty(s) && temp == NULL) break;
	}
	
	cout << endl << maxSize << endl;
	
	// deleteStack(s);
}


// Delete the tree recursively to free the allocated memory
void deleteTree(node *root){
	if(root == NULL) return;
	
	deleteTree(root->left);
	deleteTree(root->right);
	
	delete root;
}


int main(){
	// Create the binary tree
	node *root = createBT();
	
	// Print the inorder and the height of the tree
	inorder(root);
	cout << height(root) << endl;
	
	// Delete the tree
	deleteTree(root);
}

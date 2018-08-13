#include <iostream>
#include <fstream>
using namespace std;


// Node of the binary tree which contains data, pointer to the left tree node, pointer to the right tree node
// and a boolean value to store whether it is threaded or not
typedef struct node{
	int data;
	struct node *left;
	struct node *right;
	bool isThread;
} node;


// Create a binary tree node and assign the specified element to that node
node *createNode(int element){
	node *newNode = new node;
	
	newNode->data = element;
	newNode->right = NULL;
	newNode->left = NULL;
	newNode->isThread = false;
	
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

	// If the root is right-threaded, return NULL
	// If not, then find the element in the right subtree
    if(root->isThread == false) return find(root->right, element);
    else return NULL;
}


// Create the threaded binary tree by inputting elements from an input file
node *createThreadedBT(){

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
		// the root of the binary tree. Hence, ignore and continue
		if(parentNode == NULL) continue;
		
		// If the node is to be added to the left side of the parent
		if(side == 'L' && parentNode->left == NULL){
			parentNode->left = newNode;
			newNode->right = parentNode;
			newNode->isThread = true;
		}
		// If the node is to be added to the right side of the parent
		else if(side == 'R'){
		
			// If the parent has a real right child, then ignore and continue
			if(parentNode->isThread == false && parentNode->right != NULL) continue;
			// Else add the new node to the right of the parent node
			else{
				newNode->right = parentNode->right;
				
				// If right of the parent node is NULL, then new node should not be threaded
				// Else it must be threaded
				if(newNode->right == NULL) newNode->isThread = false;
				else newNode->isThread = true;
				
				parentNode->right = newNode;
				parentNode->isThread = false;
			}
			
		}
	}
	
	// Return the root of the tree
	return root;
}

// Print the inorder of the given threaded binary tree
void inorder(node *root){

	// temp and temp2 to traverse the whole tree to print the inorder
	node *temp = root;
	node *temp2 = NULL;
	
	while(1){
	
		// while temp is not equal to NULL, move temp to the left
		while(temp != NULL){
			temp2 = temp;
			temp = temp->left;
		}
		
		// While temp is threaded, print the temp data and move to the threaded successor
		temp = temp2;
		while(temp->isThread){
			cout << temp->data << "T ";
			temp = temp->right;
			if(temp == NULL) return;
		}
		
		// Once temp is no longer threaded, print the temp data and move to the right child
		cout << temp->data << " ";
		temp = temp->right;
		
		if(temp == NULL) return;
	}
}

int main(){
	// Create the binary tree
	node *root = createThreadedBT();
	
	// Print the inorder of the threaded binary tree
	inorder(root);
	cout << endl;
}

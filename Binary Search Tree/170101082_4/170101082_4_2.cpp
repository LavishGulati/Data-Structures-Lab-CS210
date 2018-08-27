#include<iostream>
#include<vector>

using namespace std;

/*Tree node definiton*/
struct TreeNode{
	int data;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x){
		data=x;
		left=right=NULL;
	}
};
int preorder_index=0;


// Vector implementation of the function commented out (I have done using arrays)
/*
TreeNode* buildTree(vector<int> &preorder,vector<int> &indexOfinorder,int start,int end){
	if(start<=end){
		TreeNode *node = new TreeNode(preorder[preorder_index]);

		int inorder_index;
		for(int i = start; i <= end; i++){
			if(indexOfinorder[i] > indexOfinorder[preorder_index]){
				inorder_index = i;
				break;
			}
		}

		preorder_index++;
		TreeNode *leftChild = buildTree(preorder, indexOfinorder, start+1, inorder_index-1);
		TreeNode *rightChild = buildTree(preorder, indexOfinorder, inorder_index, end);

		node->left = leftChild;
		node->right = rightChild;
		return node;
	}
	else
		return NULL;
}
*/

TreeNode* buildTree(int preorder[],int indexOfinorder[],int start,int end){

	if(start<=end){

		TreeNode *node = new TreeNode(preorder[preorder_index]);

		// Initialize inorder_index with start+1
		// Search for the first index in indexOfinorder which is greater than the preorder-th
		// index of indexOfinorder and set it to inorder_index
		int inorder_index = start+1;
		for(; inorder_index <= end; inorder_index++){
			if(indexOfinorder[inorder_index] > indexOfinorder[preorder_index]) break;
		}

		// Increment preorder_index by 1
		preorder_index++;

		// Build the left subtree and the right subtree of the given root recursively by giving
		// indexes of the left and right subarrays of the indexOfinorder array
		TreeNode *leftChild = buildTree(preorder, indexOfinorder, start+1, inorder_index-1);
		TreeNode *rightChild = buildTree(preorder, indexOfinorder, inorder_index, end);

		// Assign the left and right child to the node and return the node
		node->left = leftChild;
		node->right = rightChild;
		return node;
	}
	// If start index is greater than end index, then return NULL as the array is not accessible
	else
		return NULL;
}

// Print preorder traversal of the given binary tree recurively
void print_preorder(TreeNode *root){
	if(root == NULL) return;

	cout << root->data << " ";
	print_preorder(root->left);
	print_preorder(root->right);
}

// Print inorder traversal of the given binary tree recursively
void print_inorder(TreeNode *root){
	if(root == NULL) return;

	print_inorder(root->left);
	cout << root->data << " ";
	print_inorder(root->right);
}

int main(){
	int preorder[] = {7,4,2, 3, 6, 5, 12, 9, 8, 11, 19,15, 20};
	int indexOfinorder[] = {5,2,0,1,4,3,9,7,6,8,11,10,12};

	// Size of the indexOfinorder array
	int size = sizeof(indexOfinorder)/sizeof(int);

	// vector<int> preorder = {7,4,2, 3, 6, 5, 12, 9, 8, 11, 19,15, 20},indexOfinorder={5,2,0,1,4,3,9,7,6,8,11,10,12};

	// Build the binary tree and print its preorder and inorder traversal
	TreeNode *root = buildTree(preorder,indexOfinorder,0,size-1);
	print_preorder(root);cout<<endl;
	print_inorder(root);cout<<endl;
}

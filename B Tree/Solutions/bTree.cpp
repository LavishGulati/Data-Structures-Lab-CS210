//	WITH STRUCT PROACTIVE INSERTION

#include<iostream>
#include<utility>
using namespace std;

struct TreeNode{
	int *keys;
	int t;
	int n;
	TreeNode **child;
	bool leaf;
};

TreeNode *mkNode(int t1,bool leaf1){
	TreeNode *root=new TreeNode;
	root->n=0;
	root->t=t1;
	root->keys=new int[2*t1-1];
	root->child=new TreeNode*[2*t1];
	root->leaf=leaf1;
	return root;
}

void Traverse(TreeNode *root){
	int i;
	for(i=0;i<root->n;i++){
		if(root->leaf==false){
			Traverse(root->child[i]);
		}
		cout<<root->keys[i]<<" ";
	}
	if(root->leaf==false){
		Traverse(root->child[i]);
	}
}

TreeNode *search1(TreeNode *root,int k){
	if(root==NULL){
		return NULL;
	}
	int i;
	for(i=0;i<root->n;i++){
		if(root->keys[i]==k){
			return root;
		}
		if(root->keys[i]>k){
			if(root->leaf==true){
				return NULL;
			}else{
				return search1(root->child[i],k);
			}
		}
	}
	if(root->leaf==true){
		return NULL;
	}else{
		return search1(root->child[i],k);
	}
}

TreeNode *search2(TreeNode *root,int k){
	int i=0;
	while(i<root->n && k>root->keys[i]){
		i++;
	}
	if(root->keys[i]==k){
		return root;
	}
	if(root->leaf==true){
		return NULL;
	}
	return search2(root->child[i],k);
}

//y is the child of root
TreeNode *split(int i,TreeNode *y,TreeNode *root){
	TreeNode *z=mkNode(y->t,y->leaf);
	//z is the split image of higher values of keys
	z->n=y->t-1;
	for(int j=0;j<y->t-1;j++){
		z->keys[j]=y->keys[j+y->t];
	}
	if(y->leaf==false){
		for(int j=0;j<y->t;j++){
			z->child[j]=y->child[j+y->t];
		}
	}
	y->n=y->t-1;

	for(int j=root->n;j>=i+1;j--){
		root->child[j+1]=root->child[j];
	}
	root->child[i+1]=z;

	for(int j=root->n-1;j>=i;j--){
		root->keys[j+1]=root->keys[j];
	}
	root->keys[i]=y->keys[y->t-1];
	root->n=root->n+1;
	return root;
}


TreeNode *helpInsert(TreeNode *root,int k){
	int i=root->n-1;
	if(root->leaf==true){
		while(i>=0 && root->keys[i]>k){
			root->keys[i+1]=root->keys[i];
			i--;
		}
		root->keys[i+1]=k;
		root->n=root->n+1;
		return root;
	}else{
		while(i>=0 && root->keys[i]>k){
			i--;
		}
		if(root->child[i+1]->n==(2*(root->t)-1)){
			root=split(i+1,root->child[i+1],root);
			if(root->keys[i+1]<k){
				i++;
			}
		}
		root->child[i+1]=helpInsert(root->child[i+1],k);
		return root;
	}
}

//AGRESSIVE OR PROACTIVE INSERTION
TreeNode *insert(TreeNode *root,int k,int t){
	if(root==NULL){
		root=mkNode(t,true);
		root->keys[0]=k;
		root->n=1;
		return root;
	}else{
		if(root->n==2*t-1){
			TreeNode *newRoot=mkNode(t,false);
			newRoot->child[0]=root;
			newRoot=split(0,root,newRoot);
			int i=0;
			//cout<<"Check";
			//cout<<newRoot->keys[i]<<endl;
			if(newRoot->keys[i]<k){
				i++;
			}
			newRoot->child[i]=helpInsert(newRoot->child[i],k);
			return newRoot;
		}else{
			return helpInsert(root,k);
		}
	}
}




int main(){
	TreeNode *root=NULL;
	root=insert(root,10,3);
	root=insert(root,20,3);
	root=insert(root,5,3);
	root=insert(root,6,3);
	root=insert(root,12,3);
	root=insert(root,30,3);
	root=insert(root,7,3);
	root=insert(root,17,3);
	cout<<"Traversal of the tree is"<<endl;
	Traverse(root);
	cout<<endl;
	if(search2(root,6)){
		cout<<"Present"<<endl;
	}else{
		cout<<"Not present"<<endl;
	}
	if(search2(root,15)){
		cout<<"Present"<<endl;
	}else{
		cout<<"Not present"<<endl;
	}

	return 0;

}
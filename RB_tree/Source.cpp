#include <iostream>
#include <iomanip> 
using namespace std;

enum Spalva {RED, BLACK};

struct node
{
	Spalva color;
	int key_value;
	node *top;
	node *left;
	node *right;
};

class btree
{
public:
	btree(){ root = NULL; }
	void Left_Rotate(node *leaf)
	{
		Left_Rotate(root, leaf);
	}
	void Right_Rotate(node *leaf)
	{
		Right_Rotate(root, leaf);
	}
	void RB_Insert(node *leaf)
	{
		RB_Insert(root, leaf);
	}
	void RB_Insert_Fixup(node *leaf)
	{
		RB_Insert_Fixup(root, leaf);
	}

	/*
	~btree(){ destroy_tree(); }
	void insert(int key)
	{
	if(root!=NULL)
	insert(key, root);
	else
	{
	root=new node;
	root->key_value=key;
	root->top=NULL;
	root->left=NULL;
	root->right=NULL;
	}
	}
	node *Tree_Search(int key)
	{
	return Tree_Search(key, root);
	}
	node *Iterative_Tree_Search(int key)
	{
	return Iterative_Tree_Search(key, root);
	}
	void destroy_tree()
	{
	destroy_tree(root);
	}
	void Inorder_Tree_Walk()
	{
	Inorder_Tree_Walk(root);
	}
	node *Tree_Minimum()
	{
	return Tree_Minimum(root);
	}
	node *Tree_Maximum()
	{
	return Tree_Maximum(root);
	}*/
	node *Tree_Successor(node *leaf)
	{
	if ( leaf->right != NULL)
	return Tree_Minimum(leaf->right);
	node *Successor = leaf->top;
	while ( Successor != NULL && leaf == Successor->right ){
	leaf = Successor;
	Successor = Successor->top; }
	return Successor;
	}
	/*
	node *Tree_Predecessor(node *leaf)
	{
	if ( leaf->left != NULL)
	return Tree_Maximum(leaf->left);
	node *Predecessor = leaf->top;
	while ( Predecessor != NULL && leaf == Predecessor->left ){
	leaf = Predecessor;
	Predecessor = Predecessor->top; }
	return Predecessor;
	}
	node *Tree_Delete(node *leaf)
	{
	node *y, *x;
	if ( leaf->left == NULL || leaf->right == NULL){
	y = leaf;
	} else { y = Tree_Successor(leaf); }
	if ( y->left != NULL ) {
	x = y->left;
	} else { x = y->right; }
	if ( x != NULL )
	x->top = y->top;
	if ( y->top == NULL ) {
	root->top = x;
	} else { if ( y == y->top->left ){
	y->top->left = x;
	} else { y->top->right = x; } }
	if ( y != leaf)
	leaf->key_value = y->key_value;
	//
	return y;
	}
	void Tree_Insert(int key)
	{
	node *ideti;
	ideti = new node;
	ideti->key_value=key;
	ideti->left = NULL;
	ideti->right = NULL;
	ideti->top = NULL;
	Tree_Insert(ideti);
	}
	*/
private:
	node *root;
	node *nil;
	void Left_Rotate(node *root, node *leaf)
	{
		node *y = leaf->right;
		leaf->right = y->left;
		if (y->left != nil)
			y->left->top = leaf;
		y->top = leaf->top;
		if (leaf->top == nil){
			root = y;
		} else if (leaf == leaf->top->left){
				leaf->top->left = y;
			} else { leaf->top->right = y; }
		y->left = leaf;
		leaf->top = y;
	}
	void Right_Rotate(node *root, node *leaf)
	{
		node *y = leaf->left;
		leaf->left = y->right;
		if (y->right != nil)
			y->right->top = leaf;
		y->top = leaf->top;
		if (leaf->top == nil){
			root = y;
		} else if (leaf == leaf->top->right){
			leaf->top->right = y;
		} else { leaf->top->left = y; }
		y->right = leaf;
		leaf->top = y;
	}
	void RB_Insert(node *root, node*leaf)
	{
		node *y = nil;
		node *x = root;
		while (x != nil){
			y = x;
			if (leaf->key_value < x->key_value) {
				x = x->left;
			} else { x = x->right; } }
		leaf->top = y;
		if (y == nil){
			root = leaf;
			} else if (leaf->key_value < y->key_value){
						y->left = leaf;
				} else { y->right = leaf; }
		leaf->left = nil;
		leaf->right = nil;
		leaf->color = RED;
		RB_Insert_Fixup(root, leaf);
	}
	void RB_Insert_Fixup(node *root, node *leaf)
	{
		while ( leaf->top->color == RED){
			if (leaf->top == leaf->top->top->left){
				node *y = leaf->top->top->right;
				if (y->color == RED) {
					leaf->top->color = BLACK;
					y->color = BLACK;
					leaf->top->top->color = RED;
					leaf = leaf->top->top;
				} else { if (leaf== leaf->top->right){
					leaf = leaf->top;
					Left_Rotate(root, leaf->top->top); } 
				leaf->top->color = BLACK;
				leaf->top->top->color = RED;
				Right_Rotate(root, leaf->top->top); }
			} else {
				node *y = leaf->top->top->left;
				if (y->color == RED) {
					leaf->top->color = BLACK;
					y->color = BLACK;
					leaf->top->top->color = RED;
					leaf = leaf->top->top;
				} else { if (leaf== leaf->top->left){
					leaf = leaf->top;
					Left_Rotate(root, leaf->top->top); } 
				leaf->top->color = BLACK;
				leaf->top->top->color = RED;
				Right_Rotate(root, leaf->top->top); }
			}
		}
		root->color = BLACK;
	}
	node *RB_Delete(node *root, node *leaf)
	{
		node *y, *x;
		if(leaf->left == nil || leaf->right == nil){
			y = leaf;
		} else {y = Tree_Successor(leaf); }
		if (y->left != nil){
			x = y->left;
		} else {x = y->right;}
		x->top = y->top;
		if (y->top == nil){
			root = x;
		} else {if (y == y->top->left){
					y->top->left = x;
			} else { y->top->right = x; }}
		if (y != leaf)
			leaf->key_value = y->key_value;
		if (y->color == BLACK)
			RB_Delete_Fixup(root, x);
		return y;

	}

	/*
	void destroy_tree(node *leaf){
	if(leaf!=NULL)
	{
	destroy_tree(leaf->left);
	destroy_tree(leaf->right);
	delete leaf;
	}
	}
	void insert(int key, node *leaf){
	if(key < leaf->key_value)
	{
	if(leaf->left != NULL)
	insert(key, leaf->left);
	else
	{
	leaf->left=new node;
	leaf->left->key_value=key;
	leaf->left->top = leaf;
	leaf->left->left=NULL;    //Sets the left child of the child node to null
	leaf->left->right=NULL;   //Sets the right child of the child node to null
	}  
	}
	else if(key>=leaf->key_value)
	{
	if(leaf->right != NULL)
	insert(key, leaf->right);
	else
	{
	leaf->right=new node;
	leaf->right->key_value=key;
	leaf->right->top = leaf;
	leaf->right->left=NULL;  //Sets the left child of the child node to null
	leaf->right->right=NULL; //Sets the right child of the child node to null
	}
	}
	}
	node *Tree_Search(int key, node *leaf)
	{
	if ( leaf == NULL || key == leaf->key_value ) {
	return leaf; }
	if ( key < leaf->key_value ){ 
	return Tree_Search( key, leaf->left );
	} else { return Tree_Search( key, leaf->right ); }
	}
	node *Iterative_Tree_Search(int key, node *leaf)
	{
	while ( leaf != NULL && key != leaf->key_value){
	if ( key < leaf->key_value ){
	leaf = leaf->left;
	} else { leaf = leaf->right; }
	}
	return leaf;
	}
	void Inorder_Tree_Walk(node *leaf)
	{
	if ( leaf != NULL){
	Inorder_Tree_Walk( leaf->left );
	cout << "--> " << setw(3) << leaf->key_value << " <--" << endl;
	////if (leaf->top != NULL)
	////	cout << "   " << leaf->top->key_value << endl;
	//if ( leaf->left != NULL)
	//	cout << leaf->left->key_value;
	//cout << " <-- " << leaf->key_value << " --> ";
	//if ( leaf->right != NULL)
	//	cout << leaf->right->key_value;
	//cout << endl;
	Inorder_Tree_Walk( leaf->right );
	}
	}*/
	node *Tree_Minimum(node *leaf)
	{
	while ( leaf->left != NULL ){
	leaf = leaf->left; }
	return leaf;
	}
	/*node *Tree_Maximum(node *leaf)
	{
	while ( leaf->right != NULL ){
	leaf = leaf->right; }
	return leaf;
	}
	void Tree_Insert(node *leaf)
	{
	node *y = NULL;
	node *x = root;
	while ( x != NULL ){
	y =x;
	if ( leaf->key_value < x->key_value ) {
	x = x->left;
	} else { x = x->right; } }
	leaf->top = y;
	if ( y == NULL ){
	root = leaf;
	} else { if ( leaf->key_value < y->key_value){
	y->left = leaf;
	} else { y->right = leaf; } }
	}
	*/
};

int main()
{
	Spalva si = RED;
	cout << "Si spalva yra: RED - " << si << endl;
	if (si == RED){ cout << si<<endl;}
	si = BLACK;
	cout << "Si spalva yra: BLACK - " << si << endl;
	if (si == BLACK){ cout << si<<endl;}
	//cout << si == Spalva(RED);
	system("pause");
}
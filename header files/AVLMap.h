#pragma once

#include "AVLNode.h"

#define ALLOWED_IMBALANCE 1

template <class K, class T>
class AVLMap {
	AVLNode<K, T>* root;
public:
	AVLMap() {
		root = nullptr;
	}
	AVLMap(AVLNode<K, T>* r) {
		root = r;
	}
	int max(int a, int b) {
		int temp = a;
		if (b > a)
			temp = b;
		return temp;
	}
	int height(AVLNode<K, T>* &t) {
		if (t == nullptr)												//if no node, then height is -1
			return -1;
		else if (t->right == nullptr && t->left == nullptr)				//leaf node, height is zero
			return 0;
		else
			return 1 + max(height(t->left), height(t->right));
	}
	void rightRotate(AVLNode<K, T>* &x) {
		AVLNode<K, T>* orphan = x->left->right;				//detach left child's right sub tree

		AVLNode<K, T>* y = x->left;							//consider left child to be the parent

		y->right = x;										//attach old parent to new parent's right
		x->left = orphan;									//attach new parent's right sub tree to old parent's left
		x->height = height(x);								//update the heights
		y->height = height(y);

		x = y;												//update the link of the parent
	}

	void leftRotate(AVLNode<K, T>* &x) {
		AVLNode<K, T>* orphan = x->right->left;				//detach right child's left sub tree

		AVLNode<K, T>* y = x->right;						//consider right child to be the parent

		y->left = x;										//attach old parent to new parent's left
		x->right = orphan;									//attach new parent's left sub tree to old parent's right
		x->height = height(x);								//update the heights
		y->height = height(y);

		x = y;												//update link of parent
	}

	void doubleLeftRightRotation(AVLNode<K, T>* &x) {
		leftRotate(x->left);
		rightRotate(x);
	}

	void doubleRightLeftRotation(AVLNode<K, T>* &x) {
		rightRotate(x->right);
		leftRotate(x);
	}

	void balance(AVLNode<K,T> * & t)
	{
		if (t == nullptr)
			return;
		if (height(t->left) - height(t->right) > ALLOWED_IMBALANCE)
			if (height(t->left->left) >= height(t->left->right))
				rightRotate(t);
			else
				doubleLeftRightRotation(t);


		else if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE)
			if (height(t->right->right) >= height(t->right->left))
				leftRotate(t);
			else
				doubleRightLeftRotation(t);

		t->height = max(height(t->left), height(t->right)) + 1;
	}
	bool Insert(K k, T d) {
		if (LookUp(k))								//if the given key already exists, no need to insert
			return false;
		else {
			Insert(root, k, d);
			return true;
		}
	}
	void Insert(AVLNode<K, T>* &r, K k, T d) {
		if (r == nullptr) 
			r = new AVLNode<K, T>(k, d, 0);			//height will be zero since node inserted is always a leaf
			
		else if (k > r->key)
			Insert(r->right, k, d);
		else if (k < r->key)
			Insert(r->left, k, d);

		balance(r);
		
	}
	void PrintInOrder() {
		if (root)
			PrintInOrder(root);
		else
			cout << endl << "There are no items in the map" << endl << endl;
	}

	void PrintInOrder(AVLNode<K,T>* ptr) {
		if (ptr) {
			PrintInOrder(ptr->left);
			cout << ptr->key<< "\t"<< *(ptr->data) << endl;
			PrintInOrder(ptr->right);
		}

	}

	bool LookUp(K val) {
		return LookUp(val, root);

	}

	bool LookUp(K val, AVLNode<K, T>* bptr) {
		if (bptr == nullptr) 
			return false;
		
		else if (val == bptr->key) {
			cout << endl << endl << bptr->key <<" "<< *(bptr->data) << endl;
			return true;
		}
		else if (val > bptr->key)
			return LookUp(val, bptr->right);
		else if (val < bptr->key)
			return LookUp(val, bptr->left);
	}


	bool Delete(K val) {					//wrapper function since root is not accessible in main
		if (LookUp(val)) {					//if the key exists, then delete it
			Delete(val, root);
			return true;
		}
		else
			return false;					//otherwise theres no need to go into the delete function
	}
	void Delete(K d, AVLNode<K, T>* &node) {
		if (node == nullptr)
			return;
		
		else if (node->key > d)
			Delete(d, node->left);
		else if (node->key < d)
			Delete(d, node->right);
		else if (node->key == d) 
			DeleteNode(node);

		balance(node);
		
	}
	void FindMax(AVLNode<K,T>* node, AVLNode<K,T>* &maxNode) {
		while (node->right != nullptr) 
			node = node->right;
		
		maxNode = node;									//now maxNode has the node with the largest key
	}
	void DeleteNode(AVLNode<K,T>* &node) {		
		AVLNode<K,T>* temp = node;
		if (node->left == nullptr) {					//both these conditions are in the case the node has 
			node = node->right;							//either 1 child or no children
			delete temp;
			temp = nullptr;
		}
		else if (node->right == nullptr) {
			node = node->left;
			delete temp;
			temp = nullptr;
		}
		else {											//the node to be deleted has two immediate children
			
			FindMax(node->left, temp );					//find maximum from left subtree and save it in temp
			node->key = temp->key;						//put the max key in the node and then delete the maxnode
			swap(node->data, temp->data);				//swap the data pointers. Now the maxnode contains the data
														//of the node to be deleted
			Delete(node->key, node->left);				//delete that maximum
		}
	}

	void printArray(int a[], int size) {
		for (int i = 0; i < size; i++)
			cout << a[i] << " ";
		cout << endl;
	}

	void printCodes(int a[], int top) {
		return printCodes(root, a, top);
	}

	void printCodes(AVLNode<K,T>* bptr, int a[], int top) {

		if (bptr->left) {
			a[top] = 0;
			printCodes(bptr->left, a, top + 1);
		}

		if (bptr->right) {
			a[top] = 1;
			printCodes(bptr->right, a, top + 1);
		}


		if (!bptr->right && !bptr->left)
		{
			printArray(a, top);
		}

	}

	
	void Print() {
		if (root) {
			int offset = pow(2, root->height);
			return Print(root, 38, 0, offset, root->height, 1);				//38 because we have to start from centre of the screen
																			//y is 0 since we start from the first line
		}
		else
			cout << endl << "There are no items in the map" << endl << endl;
	}
	void Print(AVLNode<K, T>* ptr, int x, int y, int offset, int treeHeight, int level); 
	//definition given in the main.cpp file

	void toArray() {
		toArray(root);
	}

	int Node_Count() {
		return Node_Count(root);
	}
	int Node_Count(AVLNode<K,T>* bptr) {
		if (bptr) {
			int count = 1 + Node_Count(bptr->right) + Node_Count(bptr->left);
			return count;
		}
		return 0;
	}

	void toArray(AVLNode<K, T>* ptr) {
		int nodes = Node_Count(ptr);
		K* arr = new K[nodes];
	}

	void Destroy(AVLNode<K, T>* node) {
		if (node) {
			Destroy(node->left);
			Destroy(node->right);
			delete node;
		}
	}
	~AVLMap() {
		Destroy(root);
	}
};
#pragma once

template <class K, class T>
class AVLNode {
public:
	K key;
	T* data;
	int height;
	AVLNode<K, T> *left, *right;
	AVLNode() {
		left = right = nullptr;
	}

	AVLNode(K k, T d, int h, AVLNode<K,T>* l=nullptr, AVLNode<K, T>* r=nullptr) {
		key = k;
		data = new T(d);
		height = h;
		left = l;
		right = r;
	}
	~AVLNode() {
		//to avoid memory leaks we need to delete any memory that we allocated on the heap
		//which in this case is the data since we kept T* and not T
		if (data)
			delete data;
	}
};
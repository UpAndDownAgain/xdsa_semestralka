#pragma once

//cerveno cerny strom
template<class T>
struct Node
{
	Node *leftChild;
	Node *rightChild;
	Node *parent;
	bool isRed; // true -> red false-> black
	T value;

	Node<T>();
	Node<T>(T n) : value(n), leftChild(nullptr), rightChild(nullptr), parent(nullptr) {};
	Node<T>(T n, Node *p, Node *l, Node *r) : value(n), parent(p), leftChild(l), rightChild(r) {};
	Node<T>(T n, Node *p) : value(n), parent(p), leftChild(nullptr), rightChild(nullptr) {};

};

template<class T>
class Tree
{
private:
	Node<T> *root;

	void deleteHelper(Node<T> *n);
	void printHelper(Node<T> *n);
	Node<T> *leftRotate(Node<T> *n);
	Node<T> *rightRotate(Node<T> *n);
	Node<T> *insertHelper(Node<T> *n, T &item);
	void colourFlip(Node<T> *n);
	Node<T> *moveRedLeft(Node<T> *n);
	Node<T> *moveRedRight(Node<T> *n);
	Node<T> *fix(Node<T> *n);

public:
	Tree() : root(nullptr) {};
	Tree(T i);
	~Tree();

	void insert(T &item);

	void printInOrder();
	Node<T> * search(T &n);
};

template<class T>
inline Node<T>::Node()
{
	leftChild = nullptr;
	rightChild = nullptr;
	isRed = false;
}


template<class T>
void Tree<T>::deleteHelper(Node<T> * n)
{
	if (n == nullptr) return;
	deleteHelper(n->leftChild);
	deleteHelper(n->rightChild);
	delete n;
}


template<class T>
void Tree<T>::printHelper(Node<T> * n)
{
	if (n == nullptr) return;
	printHelper(n->leftChild);
	std::cout << n->value << std::endl;
	printHelper(n->rightChild);
}

template<class T>
Node<T> * Tree<T>::rightRotate(Node<T> * n)
{
	Node<T> * x = n->leftChild;
	n->leftChild = n->rightChild;
	x->rightChild = n;
	x->isRed = n->rightChild->isRed;
	x->rightChild->isRed = true;
	
	return x;
}

template<class T>
Node<T> * Tree<T>::leftRotate(Node<T> * n)
{
	Node<T> * x = n->rightChild;
	n->rightChild = x->leftChild;
	x->leftChild = n;
	x->isRed = x->leftChild->isRed;
	x->leftChild->isRed = true;
	return x;
}


template<class T>
Node<T> * Tree<T>::insertHelper(Node<T> *n, T &item)
{
	if (n == nullptr) {
		return new Node<T>(item);
	}
	if (n->leftChild != nullptr && n->leftChild->isRed
		&& n->rightChild != nullptr && n->rightChild->isRed) {
		colourFlip(n);
	}
	if (item == n->value) {
		return n;
	}
	else {
		n->rightChild = insertHelper(n->rightChild, item);
	}
	if (n->rightChild != nullptr && n->rightChild->isRed) {
		n = leftRotate(n);
	}
	if (n->leftChild != nullptr && n->leftChild->isRed
		&& n->leftChild->leftChild != nullptr && n->leftChild->leftChild->isRed) {
		n = rightRotate(n);
	}
	return n;
}

template<class T>
inline void Tree<T>::colourFlip(Node<T>* n)
{

	n->isRed = !n->isRed;
	n->leftChild->isRed = !n->leftChild->isRed;
	n->rightChild->isRed = !n->rightChild->isRed;

}

template<class T>
inline Node<T>* Tree<T>::moveRedLeft(Node<T>* n)
{
	colourFlip(n);
	if (n->rightChild->leftChild != nullptr && n->rightChild->leftChild->isRed) {
		n->rightChild = rightRotate(n->rightChild);
		n = leftRotate(n);
		colourFlip(n);
	}
	return n;
}

template<class T>
inline Node<T>* Tree<T>::moveRedRight(Node<T>* n)
{
	colourFlip(n);
	if (n->leftChild->leftChild != nullptr && n->leftChild->leftChild->isRed) {
		n = rightRotate;
		colourFlip(n);
	}
	return n;
}

template<class T>
inline Node<T>* Tree<T>::fix(Node<T>* n)
{
	if (n->rightChild != nullptr && n->rightChild->isRed) {
		n = leftRotate(n);
	}
	if (n->leftChild != nullptr && n->leftChild->isRed && n->leftChild->leftChild != nullptr && n->leftChild->leftChild->isRed) {
		n = rightRotate(n);
	}
	if (n->leftChild != nullptr && n->leftChild->isRed && n->rightChild != nullptr && n->rightChild->isRed) {
		colourFlip(n);
	}
	return n;
}



template<class T>
Tree<T>::Tree(T i)
{
	auto *n = new Node<T>(i);
	root = n;
	n->isRed = false;

}

template<class T>
Tree<T>::~Tree()
{
	deleteHelper(root);
}

template<class T>
void Tree<T>::insert(T &item)
{
	root = insertHelper(root, item);
	root->isRed = false;
}


template<class T>
void Tree<T>::printInOrder()
{
	printHelper(root);
}

template<class T>
Node<T> * Tree<T>::search(T &n)
{
	auto *rider = root;
	while (rider != nullptr) {
		if (rider->value == n) return rider;
		else rider = (rider->value > n) ? rider->rightChild : rider->leftChild;
	}
	return nullptr;
}

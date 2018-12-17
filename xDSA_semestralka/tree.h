#pragma once

//cerveno cerny strom
template<class T>
struct Node
{
	Node *_pLeft;
	Node *_pRight;
	Node *_pParent;
	bool isRed; // true -> red false-> black
	T _value;

	Node<T>();
	Node<T>(T n) : _value(n), _pLeft(nullptr), _pRight(nullptr), _pParent(nullptr) {};
	Node<T>(T n, Node *p, Node *l, Node *r) : _value(n), _pParent(p), _pLeft(l), _pRight(r) {};
	Node<T>(T n, Node *p) : _value(n), _pParent(p), _pLeft(nullptr), _pRight(nullptr) {};

};

template<class T>
class Tree
{
private:
	Node<T> *_pRoot;

	void deleteHelper(Node<T> *n);
	void printHelper(Node<T> *n);
	void leftRotate(Node<T> *&x);
	void rightRotate(Node<T> *&x);
	void fixViolations(Node<T> *&n);
	Node<T> *insertHelper(Node<T> *&n);
public:
	Tree() : _pRoot(nullptr) {};
	Tree(T i);
	~Tree();

	Node<T> *insert(T &item);

	void printInOrder();
	Node<T> * search(T &n);
};

template<class T>
inline Node<T>::Node()
{
	_pLeft = nullptr;
	_pRight = nullptr;
	isRed = false;
}


template<class T>
void Tree<T>::deleteHelper(Node<T> * n)
{
	if (n == nullptr) return;
	deleteHelper(n->_pLeft);
	deleteHelper(n->_pRight);
	delete n;
}


template<class T>
void Tree<T>::printHelper(Node<T> * n)
{
	if (n == nullptr) return;
	printHelper(n->_pLeft);
	std::cout << n->_value << std::endl;
	printHelper(n->_pRight);
}

template<class T>
void Tree<T>::leftRotate(Node<T> *&x)
{
	Node<T> *y = x->_pRight;
	x->_pRight = y->_pLeft;

	if (y->_pLeft != nullptr) {
		y->_pLeft->_pParent = x;
	}
	y->_pParent = x->_pParent;
	if (x->_pParent == nullptr) {
		_pRoot = y;
	}
	else if (x == x->_pParent->_pLeft) {
		x->_pParent->_pLeft = y;
	}
	else {
		x->_pParent->_pRight = y;
	}
	y->_pLeft = x;
	x->_pParent = y;
}

template<class T>
void Tree<T>::rightRotate(Node<T> *& x)
{
	Node<T> *y = x->_pLeft;
	x->_pLeft = y->_pRight;

	if (y->_pLeft != nullptr) {
		y->_pLeft->_pParent = x;
	}
	y->_pParent = x->_pParent;
	if (x->_pParent == nullptr) {
		_pRoot = y;
	}
	else if (x == x->_pParent->_pLeft) {
		x->_pParent->_pLeft = y;
	}
	else {
		x->_pParent->_pRight = y;
	}
	y->_pRight = x;
	x->_pParent = y;
}

template<class T>
void Tree<T>::fixViolations(Node<T> *& n)
{
	while (n->_pParent != nullptr && n->_pParent->isRed) {
		if (n->_pParent == n->_pParent->_pParent->_pLeft) {
			Node<T> * y = n->_pParent->_pParent->_pRight;
			if (y->isRed) {
				n->_pParent->isRed = false;
				y->isRed = false;
				n->_pParent->_pParent->isRed = true;
				n = n->_pParent->_pParent;
			}
			else if (n == n->_pParent->_pRight) {
				n = n->_pParent;
				leftRotate(n);
			}
			n->_pParent->isRed = false;
			n->_pParent->_pParent->isRed = true;
			rightRotate(n->_pParent->_pParent);
		}
		else {
			Node<T> * y = n->_pParent->_pParent->_pLeft;
			if (y->isRed) {
				n->_pParent->isRed = false;
				y->isRed = false;
				n->_pParent->_pParent->isRed = true;
				n = n->_pParent->_pParent;
			}
			else if (n == n->_pParent->_pLeft) {
				n = n->_pParent;
				leftRotate(n);
			}
			n->_pParent->isRed = false;
			n->_pParent->_pParent->isRed = true;
			rightRotate(n->_pParent->_pParent);
		}
	}
	_pRoot->isRed = false;
}

template<class T>
Node<T> * Tree<T>::insertHelper(Node<T> *&n)
{
	Node<T> *x = _pRoot;
	Node<T> *y = nullptr;

	while (x != nullptr) {
		y = x;
		if (n->_value < x->_value) {
			x = x->_pLeft;
		}
		else {
			x = x->_pRight;
		}
	}
	n->_pParent = y;

	if (y == nullptr) {
		_pRoot = n;
	}
	else if (n->_value < y->_value) {
		y->_pLeft = n;
	}
	else {
		y->_pRight = n;
	}
	n->_pLeft = nullptr;
	n->_pRight = nullptr;
	n->isRed = true;

	fixViolations(n);
	return n;
}



template<class T>
Tree<T>::Tree(T i)
{
	auto *n = new Node<T>(i);
	_pRoot = n;
	n->isRed = false;

}

template<class T>
Tree<T>::~Tree()
{
	deleteHelper(_pRoot);
}

template<class T>
Node<T> * Tree<T>::insert(T &item)
{
	auto *p = search(item);
	if (p == nullptr) {
		Node<T> *n = new Node<T>(item);
		p = insertHelper(n);
	}
	return p;
}


template<class T>
void Tree<T>::printInOrder()
{
	printHelper(_pRoot);
}

template<class T>
Node<T> * Tree<T>::search(T &n)
{
	auto *rider = _pRoot;
	while (rider != nullptr) {
		if (rider->_value == n) return rider;
		else rider = (rider->_value < n) ? rider->_pRight : rider->_pLeft;
	}
	return nullptr;
}

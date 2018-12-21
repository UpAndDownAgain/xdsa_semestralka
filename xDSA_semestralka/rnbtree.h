#pragma once
#include <iostream>
template <class T>

struct Node {
	T value;
	Node * leftChild;
	Node * rightChild;
	Node * parent;
	int isRed; // 0-black 1-red 3-doubleblack
	//bool doubleBlack;
	

	Node<T>(T n) : value(n), leftChild(nullptr), 
			rightChild(nullptr), parent(nullptr),isRed(1)/*, doubleBlack(0) */{};
};

template<class T>
class RnBtree
{
private:
	Node<T> * root;
	
	void rotateLeft(Node<T> *n);
	void rotateRight(Node<T> *n);
	int isRed(Node<T> *n);
	void swapColours(Node<T> *n1, Node<T> *n2);
	void setColour(Node<T> *n, int color);
	void fixViolations(Node<T> *&n);	
	Node<T> * insert(Node<T> *n, Node<T> * item);
	std::ostream& printInOrder(std::ostream&, Node<T> * n);
	Node<T> * deleteHelper(Node<T> *&n, T &item);
	Node<T> * minValueNode(Node<T> *n);
	void fixDeletion(Node<T> *&n);
	void cleanup(Node<T> *n);
	
public:
	~RnBtree<T>();
	void push(T item);
	std::ostream& print(std::ostream& os);
	void deleteValue(T item);
	bool isEmpty();
	void purge();

	
};

template<class T>
inline void RnBtree<T>::rotateLeft(Node<T>* n)
{
	Node<T> * rightChild = n->rightChild;
	n->rightChild = rightChild->leftChild;
	
	if (n->rightChild != nullptr) {
		n->rightChild->parent = n;
	}
	
	rightChild->parent = n->parent;
	
	if (n->parent == nullptr) {
		root = rightChild;
	}
	else if (n == n->parent->leftChild) {
		n->parent->leftChild = rightChild;
	}
	else {
		n->parent->rightChild = rightChild;
	}

	rightChild->leftChild = n;
	n->parent = rightChild;
}

template<class T>
inline void RnBtree<T>::rotateRight(Node<T>* n)
{
	Node<T> * leftChild = n->leftChild;
	n->leftChild = leftChild->rightChild;

	if (n->leftChild == nullptr) {
		root = leftChild;
	}
	else if (n == n->parent->leftChild) {
		n->parent->leftChild = leftChild;
	}
	else {
		n->parent->rightChild = n;
	}

	leftChild->rightChild = n;
	n->parent = leftChild;
}

template<class T>
inline int RnBtree<T>::isRed(Node<T>* n)
{
	if (n != nullptr) return n->isRed;
	else return false;
}

template<class T>
inline void RnBtree<T>::swapColours(Node<T>* n1, Node<T>* n2)
{

	bool tmp = n1->isRed;
	n1->isRed = n2->isRed;
	n2->isRed = tmp;

}

template<class T>
inline void RnBtree<T>::setColour(Node<T>* n, int color)
{
	if (n == nullptr) return;
	n->isRed = color;
}

template<class T>
inline void RnBtree<T>::fixViolations(Node<T> *& n)
{
	Node<T> * parent = nullptr;
	Node<T> * grandparent = nullptr;
	while (n != root && isRed(n) == 1 && isRed(n->parent) == 1) {
		parent = n->parent;
		grandparent = parent->parent;

		if (parent == grandparent->leftChild) {
			Node<T> * uncle = grandparent->rightChild;
			if (isRed(uncle)==1) {
				setColour(uncle, 0);
				setColour(parent, 0);
				setColour(grandparent, 1);
				n = grandparent;
			}
			else {
				if (n == parent->rightChild) {
					rotateLeft(parent);
					n = parent;
					parent = n->parent;
				}
				rotateRight(grandparent);
				swapColours(parent, grandparent);
				n = parent;
			}
		}
		else
		{
			Node<T> * uncle = grandparent->leftChild;
			if (isRed(uncle) == 1) {
				setColour(uncle, 0);
				setColour(parent, 0);
				setColour(grandparent, 1);
				n = grandparent;
			}
			else {
				if (n == parent->leftChild) {
					rotateRight(parent);
					n = parent;
					parent = n->parent;
				}
				rotateLeft(grandparent);
				swapColours(parent, grandparent);
				n = parent;
			}
		}
	}
	setColour(root, 0);
}

template<class T>
inline Node<T>* RnBtree<T>::insert(Node<T>* n, Node<T> * item)
{
	if (n == nullptr) return item;

	if (item->value < n->value) {
		n->leftChild = insert(n->leftChild, item);
		n->leftChild->parent = n;
	}
	else if (item->value > n->value) {
		n->rightChild = insert(n->rightChild, item);
		n->rightChild->parent = n;
	}
	return n;
}

template<class T>
void RnBtree<T>::push(T item)
{
	Node<T> *n = new Node<T>(item);
	root = insert(root, n);
	fixViolations(n);
}

template<class T>
inline std::ostream& RnBtree<T>::print(std::ostream &os)
{
	printInOrder(os,root);
	return os;
}

template<class T>
inline void RnBtree<T>::deleteValue(T item)
{
	Node<T> *n = deleteHelper(root, item);
	fixDeletion(n);
}

template<class T>
inline bool RnBtree<T>::isEmpty()
{
	if (root = nullptr) return true;
	return false;
}

template<class T>
inline void RnBtree<T>::purge()
{
	cleanup(root);
}

template<class T>
inline std::ostream& RnBtree<T>::printInOrder(std::ostream &os,Node<T>* n)
{
	if (n == nullptr) return os;
	printInOrder(os, n->leftChild);
	os << n->value << std::endl;
	printInOrder(os, n->rightChild);
}

template<class T>
inline Node<T>* RnBtree<T>::deleteHelper(Node<T> *&n, T &item)
{
	if (n == nullptr) return n;
	if (item < n->value) {
		return deleteHelper(n->leftChild, item);
	}
	if (item > n->value) {
		return deleteHelper(n->rightChild, item);
	}
	if (n->leftChild == nullptr || n->rightChild == nullptr) {
		return n;
	}

	Node<T> * temp = minValueNode(n->rightChild);
	n->value = temp->value;
	return deleteHelper(n->rightChild, temp->value);
}

template<class T>
inline Node<T>* RnBtree<T>::minValueNode(Node<T>* n)
{
	Node<T> *p = n;
	while (p->leftChild != nullptr) {
		p = p->leftChild;
	}
	return p;
}

template<class T>
inline void RnBtree<T>::fixDeletion(Node<T>*& n)
{
	if (n == nullptr) return;

	if (n == root) {
		delete n;
		root = nullptr;
		return;
	}
	if (isRed(n) == 1 || isRed(n->leftChild) == 1 || isRed(n->rightChild) == 1) {
		Node<T> * child = n->leftChild != nullptr ? n->leftChild : n->rightChild;

		if (n == n->parent->leftChild) {
			n->parent->leftChild = child;
			if (child != nullptr) {
				child->parent = n->parent;
			}
			setColour(child, 0);
			delete n;
		}
		else {
			n->parent->rightChild = child;
			if (child != nullptr) {
				child->parent = n->parent;
			}
			setColour(child, 0);
			delete n;
		}
	}
	else {
		Node<T> * sibling = nullptr;
		Node<T> * parent = nullptr;
		Node<T> * p = n;
		//p->doubleBlack = 1;
		setColour(p, 3);
		while (p != root && isRed(p) == 3/*p != nullptr && p->doubleBlack == 1*/) {
			parent = p->parent;
			if (p == parent->leftChild) {
				sibling = parent->rightChild;
				if (isRed(sibling) == 1) {
					setColour(sibling, 0);
					setColour(parent, 1);
					rotateLeft(parent);
				}
				else {
					if (isRed(sibling->leftChild) == 0 && isRed(sibling->rightChild) == 0) {
						setColour(sibling, 1);
						if (isRed(parent) == 1) {
							setColour(parent, 0);
						}
						else {
							//parent->doubleBlack = 1;
							setColour(parent, 3);
						}
						p = parent;
					}
					else {
						if (isRed(sibling->rightChild) == 0) {
							setColour(sibling->leftChild, 0);
							setColour(sibling, 1);
							rotateRight(sibling);
							sibling = parent->rightChild;
						}
						setColour(sibling, parent->isRed);
						setColour(parent, 0);
						setColour(sibling->rightChild, 0);
						rotateLeft(parent);
						break;
					}
				}
			}
			else {
				sibling = parent->leftChild;
				if (isRed(sibling) == 1) {
					setColour(sibling, 0);
					setColour(parent, 1);
					rotateRight(parent);
				}
				else {
					if (isRed(sibling->leftChild) == 0 && isRed(sibling->rightChild) == 0) {
						setColour(sibling, 1);
						if (isRed(parent) == 1) {
							setColour(parent, 0);
						}
						else {
							setColour(parent, 3);
						}
						p = parent;
					}
					else {
						if (isRed(sibling->leftChild) == 0) {
							setColour(sibling->rightChild, 0);
							setColour(sibling, 1);
							rotateLeft(sibling);
							sibling = parent->leftChild;
						}
			
						setColour(sibling, parent->isRed);
						setColour(parent, 0);
						setColour(sibling->leftChild, 0);
						rotateRight(parent);
						break;
					}
				}
			}
		}
		if (n == n->parent->leftChild) {
			n->parent->leftChild = nullptr;
		}
		else {
			n->parent->rightChild = nullptr;
		}
		delete n;
		setColour(root, 0);
	}
}

template<class T>
inline void RnBtree<T>::cleanup(Node<T>* n)
{
	if (n == nullptr) return;
	cleanup(n->leftChild);
	cleanup(n->rightChild);
	delete n;
}

template<class T>
inline RnBtree<T>::~RnBtree()
{
	cleanup(root);
}

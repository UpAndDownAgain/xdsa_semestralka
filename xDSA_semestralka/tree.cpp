#include "pch.h"
#include "tree.h"



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
Tree<T>::~Tree()
{
	deleteHelper(_pRoot);
}

template<class T>
void Tree<T>::printInOrder()
{
	printHelper(_pRoot);
}

template<class T>
Node<T> Tree<T>::search(T &n)
{
	auto *rider = _pRoot;
	while (rider != nullptr) {
		if (rider->_value == n) return rider;
		else rider = (rider->_value > n) ? rider->_pLeft : rider->_pRight;
	}
	return nullptr();
}

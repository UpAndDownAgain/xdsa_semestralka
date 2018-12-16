#pragma once
#include <string>
//cerveno cerny strom
template<class T>
struct Node
{
	Node *_pLeft;
	Node *_pRight;
	Node *_pParent;
	bool colour; // true -> red false-> black
	T _value;

	Node(T n) : _value(n), _pLeft(nullptr), _pRight(nullptr), _pParent(nullptr) {};
	Node(T n, Node *p, Node *l, Node *r) : _value(n), _pParrent(p), _pLeft(l), _pRight(r) {};
	Node(T n, Node *p) : _value(n), _pParrent(p), _pLeft(nullptr), _pRight(nullptr) {};

};

template<class T>
class Tree
{
private:
	Node<T> *_pRoot;

	void deleteHelper(Node *n);
	void printHelper( Node *n);
public:
	Tree() : _pRoot(nullptr) {};
	~Tree();

	void insert(T &item);
	void printInOrder();
	Node<T> search(T &n);
};


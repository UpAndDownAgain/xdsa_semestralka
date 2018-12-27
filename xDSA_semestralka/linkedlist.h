#pragma once


template<class T>
class LinkedList {

	template<class T>
	struct llNode {
		T value;
		llNode<T> * next;

		llNode<T>(T item) : value(item), next(nullptr) {};
	};

	size_t elementsNum;
	llNode<T> * head;
	llNode<T> * end;

public:
	LinkedList<T>() : elementsNum(0), head(nullptr), end(nullptr) {};
	~LinkedList<T>();
	size_t size() { return this->elementsNum; };
	void push_back(T item);
	llNode<T> * getHead() { return this->head; };

};

template<class T>
inline void LinkedList<T>::push_back(T item)
{
	if (head == nullptr) {
		head = new llNode<T>(item);
		end = head;
	}
	else {
		end->next = new llNode<T>(item);
		end = end->next;
	}
	++elementsNum;
}

template<class T>
inline LinkedList<T>::~LinkedList()
{
	auto * rider = head;
	while (rider != nullptr) {
		auto * tmp = rider->next;
		delete rider;
		rider = tmp;
	}
}

// xDSA_semestralka.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

#include "tree.h"
#include "Student.h"

int main()
{
	//auto * n = new Node<int>();
	//std::cout << n->_value << std::endl;
	
	auto *strom = new Tree<int>();
	for (int i = 0; i < 10; ++i) {
		strom->insert(i);
	}
	strom->printInOrder();
}

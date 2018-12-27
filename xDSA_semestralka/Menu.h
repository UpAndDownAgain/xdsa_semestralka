#pragma once
#ifndef __MENU_H_
#define __MENU_H_

//#include <vector>
#include <string>
#include <iostream>
#include <initializer_list>
#include "linkedlist.h"


class Menu
{
protected:
	//std::vector<std::string> menuItems;
	LinkedList<std::string> menuItems;
	char userInput;
public:
	Menu();
	Menu(std::initializer_list<std::string>); //inicializace polozek pomoci listu
	~Menu();
	void addMenuItem(std::string);
	void printMenu(); //vypise menu do cout
	bool readUserChoice(); //precte volbu z cin
	char getUserChoice() { return this->userInput; };
};

#endif

#pragma once
#ifndef __MENU_H_
#define __MENU_H_

#include <vector>
#include <string>
#include <iostream>
#include <initializer_list>

class Menu
{
protected:
	std::vector<std::string> menuItems;
	char userInput;
public:
	Menu();
	Menu(std::initializer_list<std::string>);
	~Menu();
	void addMenuItem(std::string);
	void printMenu();
	bool readUserChoice();
	char getUserChoice() { return this->userInput; };
};

#endif

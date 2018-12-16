#include "pch.h"
#include "menu.h"


Menu::Menu(std::initializer_list<std::string> init_list)
{
	for (auto element : init_list) {
		menuItems.push_back(element);
	}
}

Menu::Menu()
{
}

Menu::~Menu()
{
}

void Menu::addMenuItem(std::string item) {
	menuItems.push_back(item);
}
void Menu::printMenu() {

	for (std::size_t iter = 0; iter < menuItems.size(); ++iter ) {
		std::cout << iter << " - " << menuItems[iter] << std::endl;
	}
}
bool Menu::readUserChoice() {
	std::string buffer;
	
	std::cout << "> ";
	std::getline(std::cin, buffer);
	
	//pro vstupy vyssi nez 9 aby userInput mohl byt char a trida menu fungovala se switchem az pro 15 polozek
	//s vice polozkami se nepocitalo
	if (buffer.size() > 1) {
		int choice = std::stoi(buffer);
		if (choice > 15) {
			std::cerr << "Neplatna volba" << std::endl;
			return 0;
		}
		char hexArr[] = { 'A', 'B', 'C', 'D', 'E', 'F' };
		userInput = hexArr[choice - 10];
	}
	else {
		userInput = buffer[0];
	}
	return 1;
}

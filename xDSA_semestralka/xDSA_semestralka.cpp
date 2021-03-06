// xDSA_semestralka.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>

#include "Student.h"
#include "rnbtree.h"
#include "Menu.h"


void readFromFile(std::string &, RnBtree<Student>*);

void printToFile(std::string &, RnBtree<Student>*);
void vytvorStudenta(RnBtree<Student>*);
void smazStudenta(RnBtree<Student>*);
void generuj(RnBtree<Student>*, size_t);

int main()
{
	bool exitFlag(0);
	std::string helperString;
	Node<Student> * helperNode(nullptr);
	RnBtree<Student> *rbtree = new RnBtree<Student>();
	Menu * menu = new Menu({"Konec", "Nacist data ze souboru", "ulozit data do soubouru",
		"Vypsat data", "Zapsat noveho studenta","Vyhledat studenta podle id", "Smazat studenta", "Smazat vsechny studenty", "Vygeneruj studenty se vzestupnym id (smaze soucasne studenty)"});
	

	while (!exitFlag) {
		menu->printMenu();
		while (!menu->readUserChoice());

		switch (menu->getUserChoice()) {
		default:
			std::cout << "Neplatna volba" << std::endl;
			break;

		case '0': //exit
			exitFlag = true;
			break;
		case '1': //nacist ze souboru
			rbtree->purge();
			std::cout << "Zadejte nazev souboru" << std::endl;
			std::getline(std::cin, helperString);
			readFromFile(helperString, rbtree);
			break;
		case '2': //ulozit
			std::cout << "Zadejte nazev souboru" << std::endl;
			std::getline(std::cin, helperString);
			printToFile(helperString, rbtree);
			break;
		case '3'://vypsat
			rbtree->print(std::cout);
			break;
		case '4'://novy stud
			vytvorStudenta(rbtree);
			break;
		case '5'://vyhledat
			int id;
			std::cout << "Zadejte id" << std::endl;
			std::cin >> id;
			helperNode = rbtree->search(id);
			if (helperNode == nullptr) std::cout << "Zaznam nenalezen" << std::endl;
			else std::cout << helperNode->value << std::endl;
			break;
		case '6'://smazat
			smazStudenta(rbtree);
			break;
		case '7'://smazat vse
			rbtree->purge();
			break;
		case '8'://generuj;
			size_t count;
			std::cout << "zadejte mnozstvi" << std::endl;
			std::cin >> count;
			generuj(rbtree, count);
			break;
		}
		std::getline(std::cin, helperString);	
	}
	delete menu;
	delete rbtree;
}

void readFromFile(std::string &s, RnBtree<Student>*tree) {
	std::string jmeno, prijmeni;
	int id;
	std::ifstream fHandler;
	fHandler.open(s);
	if (!fHandler.is_open()) {
		std::cerr << "Chyba otevirani souboru" << std::endl;
		return;
	}
	while (fHandler >> id >> jmeno >> prijmeni) {
		Student tmp = Student(jmeno, prijmeni, id);
		tree->push(tmp);
	}
	fHandler.close();
}

void printToFile(std::string &s, RnBtree<Student>*tree) {
	std::ofstream fHandler;
	fHandler.open(s);
	if (!fHandler.is_open()) {
		std::cerr << "Chyba otevirani souboru" << std::endl;
		return;
	}
	tree->print(fHandler);
	fHandler.close();
}

void vytvorStudenta(RnBtree<Student>*tree) {
	std::string jmeno, prijmeni;
	int id;
	std::cout << "Jmeno: ";
	std::cin >> jmeno;
	std::cout << "Prijmeni: ";
	std::cin >> prijmeni;
	std::cout << "id: ";
	std::cin >> id;

	Student tmp = Student(jmeno, prijmeni, id);
	tree->push(tmp);
}

void smazStudenta(RnBtree<Student>*tree) {
	int id;
	std::cout << "Zadej ID studenta pro smazani: ";
	std::cin >> id;
	Student tmp = Student(id);
	tree->deleteValue(tmp);
}
void generuj(RnBtree<Student>*tree, size_t c) {
	tree->purge();
	for (size_t i = 0; i < c; ++i) {
		tree->push(Student(i));
	}
}
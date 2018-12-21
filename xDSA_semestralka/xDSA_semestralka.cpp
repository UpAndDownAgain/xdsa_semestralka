// xDSA_semestralka.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

#include "Student.h"
#include "rnbtree.h"
#include "Menu.h"



int main()
{
	bool exitFlag(0);
	RnBtree<Student> *rbtree = new RnBtree<Student>();
	Menu * menu = new Menu({"Konec", "Nacist data ze souboru", "ulozit data do soubouru",
		"Vypsat data", "Zapsat noveho studenta", "Vyhledat studenta podle ID", "Smazat studenta"});

	_CrtDumpMemoryLeaks();
}

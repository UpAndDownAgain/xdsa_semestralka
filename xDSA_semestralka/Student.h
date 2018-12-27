#pragma once
#include <string>
#include <iostream>
#include <random>

using std::string;

class Student
{

private:
	string _jmeno;
	string _prijmeni;
	int _id;

public:
	Student(int i) : _id(i) { //konstruktor pro sekvencni generovani
		_jmeno = "John";
		_prijmeni = "Doe";
	};
	Student(string n, string p, int i) : _jmeno(n), _prijmeni(p), _id(i) {};
	~Student();
	string getName() { return _jmeno + " " + _prijmeni; };
	int getID() { return _id; };

	friend std::ostream& operator<<(std::ostream &os, const Student &s); //tisk do streamu "id jmeno prijmeni"
	friend bool operator>(const Student &s1, const Student &s2); // porovnani podle id
	friend bool operator>(const Student &s1, const int &i);
	friend bool operator<(const Student &s1, const Student &s2);
	friend bool operator<(const Student &s1, const int &i);
	friend bool operator==(const Student &s1, const Student &s2); 
	friend bool operator==(const Student &s1, const int &i);
};


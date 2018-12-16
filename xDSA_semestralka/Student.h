#pragma once
#include <string>
#include <iostream>
using std::string;

class Student
{

private:
	string _jmeno;
	string _prijmeni;
	int _id;

public:
	Student(string n, string p, int i) : _jmeno(n), _prijmeni(p), _id(i) {};
	~Student();
	string getName() { return _jmeno + " " + _prijmeni; };
	int getID() { return _id; };

	friend std::ostream& operator<<(std::ostream &os, const Student &s);
};


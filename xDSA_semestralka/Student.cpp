#include "pch.h"
#include "Student.h"


std::ostream & operator<<(std::ostream & os, const Student & s)
{
	os << s._id << " - " << s._jmeno << " " << s._prijmeni;
	return os;
}

Student::~Student()
{
}

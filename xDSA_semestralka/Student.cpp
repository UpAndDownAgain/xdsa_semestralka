#include "pch.h"
#include "Student.h"


std::ostream & operator<<(std::ostream & os, const Student & s)
{
	os << s._id << " " << s._jmeno << " " << s._prijmeni;
	return os;
}

bool operator>(const Student & s1, const Student & s2)
{
	return s1._id > s2._id;
}

bool operator>(const Student & s1, const int & i)
{
	return s1._id > i;
}

bool operator<(const Student & s1, const Student & s2)
{
	return s1._id < s2._id;
}

bool operator<(const Student & s1, const int & i)
{
	return s1._id < i;
}

bool operator==(const Student & s1, const Student & s2)
{
	if (s1._id == s2._id) return true;
	return false;
}

bool operator==(const Student & s1, const int & i)
{
	return s1._id == i;
}

Student::~Student()
{
}

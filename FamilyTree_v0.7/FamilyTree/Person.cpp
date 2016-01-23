#include <iostream>
#include "Person.h"

int Person::count = 0;

Person::Person()
{
	count++;
	id = count;
	active = 0;
}

Person::Person(Gender sx, std::string snm, std::string nm, std::string otc)
{
	count++;
	id = count;

	gender = sx;
	surname = snm;
	name = nm;
	otch = otc;
	active = 1;
	date_of_birth = nullptr;
	date_of_death = nullptr;
}

Person::Person(Gender sx, std::string snm, std::string nm, std::string otc, std::tm *dob)
{
	count++;
	id = count;

	gender = sx;
	surname = snm;
	name = nm;
	otch = otc;
	date_of_birth = new tm;
	(*date_of_birth).tm_mday = (*dob).tm_mday;
	(*date_of_birth).tm_mon = (*dob).tm_mon;
	(*date_of_birth).tm_year = (*dob).tm_year;
	date_of_death = nullptr;
	active = 1;
}


Person::~Person()
{
	count--;
}

int Person::getId()
{
	return id;
}

void Person::setId(int new_id)
{
	if (new_id > count)
		id = new_id;
	count = id;
}

int Person::getLastId()
{
	return count;
}

std::ostream& operator<< (std::ostream& out, Person& pers)
{
	if (pers.active == 0)
	{
		out << "(Empty person)";
	}
	else
	{
		out << pers.id << " " << pers.gender << " " << pers.surname << " " << pers.name << " " << pers.otch << " ";
		if (pers.date_of_birth) {
			out << (*pers.date_of_birth).tm_mday << "-" << (*pers.date_of_birth).tm_mon + 1 << "-" << (*pers.date_of_birth).tm_year + 1900;
		}
		else
		{
			out << "N/A";
		}
	}
	
	return out;
}

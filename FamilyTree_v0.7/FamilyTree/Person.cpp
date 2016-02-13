#include <iostream>
#include "Person.h"

int Person::count = -1;

Person::Person()
{
	dob_day = 0, dob_month = 0, dob_year = 0;
	dod_day = 0, dod_month = 0, dod_year = 0;

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
	dob_day = 0, dob_month = 0, dob_year = 0;
	dod_day = 0, dod_month = 0, dod_year = 0;

	active = 1;
}

Person::Person(Gender sx, std::string snm, std::string nm, std::string otc, std::tm *dob)
{
	count++;
	id = count;

	gender = sx;
	surname = snm;
	name = nm;
	otch = otc;
	dob_day = (*dob).tm_mday, dob_month = (*dob).tm_mon + 1, dob_year = (*dob).tm_year;
	dod_day = 0, dod_month = 0, dod_year = 0;

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
		if (pers.dob_day != 0) {
			out << pers.dob_day << "-" << pers.dob_month << "-" << pers.dob_year + 1900;
		}
		else
		{
			out << "N/A";
		}
	}
	
	return out;
}

#pragma once

#include <string>
#include <ctime>
#include <iostream>
#include "Gender.h"

class Person
{
	static int count; // количество людей, чтобы не напутать с айдишниками
	int id;
public:
	int active = 0; // есть ли данные
	Gender gender;
	std::string name;
	std::string surname;
	std::string otch;
	int dob_day, dob_month, dob_year;
	int dod_day, dod_month, dod_year;
public:
	Person();
	Person(Gender sx, std::string snm, std::string nm, std::string otc);
	Person(Gender sx, std::string snm, std::string nm, std::string otc, std::tm *dob);
	virtual ~Person();
	int getId();
	void setId(int new_id);
	static int getLastId();

	friend std::ostream& operator<< (std::ostream& out, Person& pers);
	
	/*
	void *Person::operator new[](size_t size)
	{
		printf("[Person] Allocated %d bytes\n", size);
		return malloc(size);
	}

	void Person::operator delete[](void *p)
	{
		printf("[Person] Freed bytes\n");
		free(p);
	}*/

};


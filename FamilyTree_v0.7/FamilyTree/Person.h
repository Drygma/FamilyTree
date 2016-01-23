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
	std::tm *date_of_birth;
	std::tm *date_of_death;
public:
	Person();
	Person(Gender sx, std::string snm, std::string nm, std::string otc);
	Person(Gender sx, std::string snm, std::string nm, std::string otc, std::tm *dob);
	~Person();
	int getId();
	void setId(int new_id);
	static int getLastId();

	friend std::ostream& operator<< (std::ostream& out, Person& pers);

};


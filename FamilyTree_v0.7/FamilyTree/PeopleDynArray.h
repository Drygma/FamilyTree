#pragma once

#include <iostream>
#include "Person.h"

class PeopleDynArray
{
	unsigned size;
public:
	PeopleDynArray();
	PeopleDynArray(const PeopleDynArray& arr);
	~PeopleDynArray();
public:
	unsigned GetSize() const;
	void Resize(unsigned new_size);
	void PushBack(Person &p);
	Person PopBack();
	Person* Get(unsigned i) const;
	Person* GetById(unsigned id);
	void Set(unsigned i, Person &p);
	void Clear();

	friend std::ostream& operator<< (std::ostream& out, const PeopleDynArray& arr);
public:
	Person *people;
};


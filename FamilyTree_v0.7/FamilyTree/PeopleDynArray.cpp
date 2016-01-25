#include <iostream>
#include "PeopleDynArray.h"

PeopleDynArray::PeopleDynArray()
{
	people = 0;
	size = 0;
}

PeopleDynArray::PeopleDynArray(const PeopleDynArray& arr)
{
	size = arr.GetSize();
	people = new Person[size];
	for (unsigned i = 0; i < size; i++)
		people[i] = *(arr.Get(i));
}

PeopleDynArray::~PeopleDynArray()
{
	delete[] people;
}

unsigned PeopleDynArray::GetSize() const
{
	return size;
}

void PeopleDynArray::Resize(unsigned new_size)
{
	if (new_size <= 0)
	{
		std::cout << "Wrong new size" << std::endl;
	}	
	else if (new_size != size)
	{
		Person *new_people = new Person[new_size];
		for (unsigned i = 0; i < new_size; i++)
		{
			if (i < size)
				new_people[i] = people[i];
		}

		delete[] people;
		people = new_people;

		size = new_size;
	}
}

void PeopleDynArray::PushBack(Person &p)
{
	if (size == 0)
	{
		people = new Person[1];
		people[0] = p;
		size = 1;
	}
	else
	{
		Resize(size + 1);
		people[size - 1] = p;
	}
}

Person PeopleDynArray::PopBack()
{
	Person ans = people[size - 1];
	Resize(size - 1);
	return ans;
}

Person* PeopleDynArray::Get(unsigned i) const
{
	if (i >= 0 && i < size)
		return &people[i];
	else
		return (Person*)0;
}

Person* PeopleDynArray::GetById(unsigned id)
{
	for (unsigned i = 0; i < size; i++)
	{
		if (people[i].getId() == id)
			return &people[i];
	}
	return (Person*)0;
}

void PeopleDynArray::Set(unsigned i, Person &p)
{
	if (i >= 0 && i < size)
		people[i] = p;
	else
		std::cout << "Wrong index" << std::endl;
}

void PeopleDynArray::Clear()
{
	delete[] people;
	people = 0;
	size = 0;
}

std::ostream& operator<< (std::ostream& out, const PeopleDynArray& arr)
{
	out << arr.GetSize() << std::endl;
	for (unsigned i = 0; i < arr.size; i++)
		out << arr.people[i] << std::endl;
	//out.flush();
	return out;
}

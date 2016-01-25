#pragma once
#include "Person.h"
#include "Relation.h"
#include <string>
#include <map>

class Family
{
	Person **members;
	Relation *relations;
	int size;
	int relation_count;
public:
	Family();
	Family(const Family& family);
	Family(Person *husband, Person *wife);
	virtual ~Family();
	void AddChild(Person *child);
	Person* getMember(int i);
	int getChildrenCount() const;
	int getRelationsCount() const;
	int getSize() const;
	Relation* getRelations();

	friend std::ostream& operator<< (std::ostream& out, Family& family);
	Family& operator=(const Family& family);

	/*
	void *Family::operator new[](size_t size)
	{
	printf("[Family] Allocated %d bytes\n", size);
	return malloc(size);
	}

	void Family::operator delete[](void *p)
	{
	printf("[Family] Freed bytes\n");
	free(p);
	}*/

};


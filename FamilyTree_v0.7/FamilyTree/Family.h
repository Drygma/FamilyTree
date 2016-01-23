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
	Family(Person *husband, Person *wife);
	~Family();
	void AddChild(Person *child);
	Person* getMember(int i);
	int getChildrenCount();
	int getRelationsCount();
	int getSize();
	Relation* getRelations();

	friend std::ostream& operator<< (std::ostream& out, Family& family);
};


#pragma once

#include "Person.h"
#include "Relation_types.h"

class Relation
{
	Person *p1;
	Person *p2;
	Relation_type type;
public:
	Relation();
	Relation(Person *n1, Person *n2, Relation_type t);
	~Relation();
	Relation_type getType();
};


#include "Relation.h"
#include "Person.h"
#include "Relation_types.h"



Relation::Relation()
{
	p1 = nullptr;
	p2 = nullptr;
}

Relation::Relation(Person *n1, Person *n2, Relation_type t)
{
	p1 = n1;
	p2 = n2;
	type = t;
}

Relation::~Relation()
{
}

Relation_type Relation::getType()
{
	return type;
}

#include "Relation.h"
#include "Person.h"
#include "Relation_types.h"



Relation::Relation()
{
	p1 = 0;
	p2 = 0;
}

Relation::Relation(const Relation& rel)
{
	p1 = rel.p1;
	p2 = rel.p2;
	type = rel.type;
}

Relation::Relation(Person *n1, Person *n2, Relation_type t)
{
	p1 = n1;
	p2 = n2;
	type = t;
}

Relation::~Relation()
{
	p1 = 0;
	p2 = 0;
}

Relation_type Relation::getType()
{
	return type;
}
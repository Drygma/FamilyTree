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
	Relation(const Relation& rel);
	Relation(Person *n1, Person *n2, Relation_type t);
	virtual ~Relation();
	Relation_type getType();
	
	/*
	void *Relation::operator new[](size_t size)
	{
		printf("[Relation] Allocated %d bytes\n", size);
		return malloc(size);
	}

	void Relation::operator delete[](void *p)
	{
		printf("[Relation] Freed bytes\n");
		free(p);
	}*/
};


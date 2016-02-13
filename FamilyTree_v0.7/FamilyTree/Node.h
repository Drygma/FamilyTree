#pragma once
#include "Person.h"

class CNode
{
	Person profile;
public:
	CNode();
	CNode(Person &member);
	~CNode();
public:
	int EditProfile(Person &member);
public:
	CNode *parent;
	CNode *mate;
	CNode *left;
	CNode *right;
};


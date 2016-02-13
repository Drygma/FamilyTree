#include "Node.h"
#include "Person.h"


CNode::CNode()
{
	parent = 0;
	mate = 0;
	left = 0;
	right = 0;
}

CNode::CNode(Person &member)
{
	profile = member;
}

CNode::~CNode()
{
}

int CNode::EditProfile(Person &member)
{
	profile = member;
	return 0;
}

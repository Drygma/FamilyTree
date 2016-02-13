#pragma once
#include <string>
#include "Node.h"
#include "PeopleDynArray.h"
#include "FamilyDynArray.h"

class CFamilyTree
{
	CNode root;
public:
	CFamilyTree(const char* filename);
	~CFamilyTree();
	int Init(PeopleDynArray &people, FamilyDynArray &families);
	CNode CreateNode();
	int Add(CNode nodeParent, CNode nodeChild);
	int Remove(CNode *node);
	int Clear();
	CNode Find(std::string name);
	int Load();
	int Save();

};


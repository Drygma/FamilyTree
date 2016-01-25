#pragma once

#include <iostream>
#include "Family.h"

class FamilyDynArray
{
	unsigned size;
public:
	FamilyDynArray();
	FamilyDynArray(const FamilyDynArray& arr);
	~FamilyDynArray();
public:
	unsigned GetSize() const;
	void Resize(unsigned new_size);
	void PushBack(Family &f);
	Family PopBack();
	Family* Get(unsigned i) const;
	void Set(unsigned i, Family &f);
	void Clear();

	friend std::ostream& operator<< (std::ostream& out, const FamilyDynArray& arr);
public:
	Family *families;
};


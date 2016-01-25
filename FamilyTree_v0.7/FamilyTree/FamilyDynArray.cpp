#include <iostream>
#include "FamilyDynArray.h"

FamilyDynArray::FamilyDynArray()
{
	families = 0;
	size = 0;
}

FamilyDynArray::FamilyDynArray(const FamilyDynArray& arr)
{
	size = arr.GetSize();
	families = new Family[size];
	for (unsigned i = 0; i < size; i++)
		families[i] = *(arr.Get(i));
}

FamilyDynArray::~FamilyDynArray()
{
	delete[] families;
}

unsigned FamilyDynArray::GetSize() const
{
	return size;
}

void FamilyDynArray::Resize(unsigned new_size)
{
	if (new_size <= 0)
	{
		std::cout << "Wrong new size" << std::endl;
	}
	else if (new_size != size)
	{
		Family *new_families = new Family[new_size];
		for (unsigned i = 0; i < new_size; i++)
		{
			if (i < size)
				new_families[i] = families[i];
		}

		delete[] families;
		families = new_families;

		size = new_size;
	}
}

void FamilyDynArray::PushBack(Family &f)
{
	if (size == 0)
	{
		families = new Family[1];
		families[0] = f;
		size = 1;
	}
	else
	{
		Resize(size + 1);
		families[size - 1] = f;
	}
}

Family FamilyDynArray::PopBack()
{
	Family ans = families[size - 1];
	Resize(size - 1);
	return ans;
}

Family* FamilyDynArray::Get(unsigned i) const
{
	if (i >= 0 && i < size)
		return &families[i];
	else
		return (Family*)0;
}

void FamilyDynArray::Set(unsigned i, Family &f)
{
	if (i >= 0 && i < size)
		families[i] = f;
	else
		std::cout << "Wrong index" << std::endl;
}

void FamilyDynArray::Clear()
{
	delete[] families;
	families = 0;
	size = 0;
}

std::ostream& operator<< (std::ostream& out, const FamilyDynArray& arr)
{
	out << arr.GetSize() << std::endl;
	for (unsigned i = 0; i < arr.size; i++)
		out << arr.families[i] << std::endl;
	//out.flush();
	return out;
}

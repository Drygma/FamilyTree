#include "Family.h"
#include "Relation.h"
#include <iostream>

Family::Family()
{
	relations = 0;
	members = 0;

	size = 0;
	relation_count = 0;
}

Family::Family(const Family& family)
{
	size = family.size;
	relation_count = family.relation_count;

	relations = new Relation[relation_count];
	for (unsigned i = 0; i < relation_count; i++)
		relations[i] = family.relations[i];

	members = new Person*[size];
	for (unsigned i = 0; i < size; i++)
		members[i] = family.members[i];
}

Family::Family(Person *husband, Person *wife)
{
	members = new Person*[2];
	members[0] = husband;
	members[1] = wife;
	size = 2;

	relations = new Relation[1];
	relations[0] = Relation(members[0], members[1], HUSBAND_WIFE);
	relation_count = 1;
}

Family::~Family()
{
	if (relations) delete[] relations;
	if (members) delete[] members;

	members = 0;
	relations = 0;
}

void Family::AddChild(Person *child)
{
	Person **new_members = new Person*[size + 1];
	for (int i = 0; i < size; i++) new_members[i] = members[i];
	new_members[size] = child;

	delete[] members;

	members = new_members;
	size++;

	Relation *new_relations = new Relation[relation_count + 2];
	for (int i = 0; i < relation_count; i++) new_relations[i] = relations[i];
	switch ((*members[size - 1]).gender)
	{
		case MALE:
			new_relations[relation_count] = Relation(members[0], members[size - 1], FATHER_SON);
			new_relations[relation_count + 1] = Relation(members[1], members[size - 1], MOTHER_SON);
			break;
		case FEMALE:
			new_relations[relation_count] = Relation(members[0], members[size - 1], FATHER_DAUGHTER);
			new_relations[relation_count + 1] = Relation(members[1], members[size - 1], MOTHER_DAUGHTER);
			break;
		default:
			break;
	}

	delete[] relations;

	relations = new_relations;
	new_relations = 0;
	relation_count += 2;

	//Если дети до этого уже были, то нужно добавить дополнительные Relations между ними и новым ребенком
	if (int childrenCount = getChildrenCount() - 1)
	{
		new_relations = new Relation[relation_count + childrenCount];
		for (int i = 0; i < relation_count; i++) new_relations[i] = relations[i];
		for (int i = 2; i < size - 1; i++)
		{
			switch ((*members[size - 1]).gender)
			{
				case MALE:
					new_relations[relation_count + (i - 1 - childrenCount)] = Relation(members[size - 1], members[i], (*members[i]).gender ? BROTHER_SISTER : BROTHER_BROTHER);
					break;
				case FEMALE:
					new_relations[relation_count + (i - 1 - childrenCount)] = Relation(members[size - 1], members[i], (*members[i]).gender ? SISTER_SISTER : BROTHER_SISTER);
					break;
				default:
					break;
			}
		}

		delete[] relations;

		relations = new_relations;
		relation_count += childrenCount;
		childrenCount++;
	}

}

Person* Family::getMember(int i)
{
	return members[i];
}

int Family::getChildrenCount() const
{
	int count = 0;
	for (int i = 0; i < relation_count; i++)
	{
		if (relations[i].getType() == FATHER_SON || relations[i].getType() == FATHER_DAUGHTER)
		{
			count++;
		}
	}
	return count;
}

int Family::getRelationsCount() const
{
	return relation_count;
}

int Family::getSize() const
{
	return size;
}

Relation* Family::getRelations()
{
	return relations;
}

std::ostream& operator<< (std::ostream& out, Family& family)
{
	if (family.getSize() == 0)
	{
		out << "(Empty family)";
	}
	else
	{
		out << (*family.getMember(0)).getId() << " " << (*family.getMember(1)).getId();
		for (int i = 2; i < family.getChildrenCount() + 2; i++)
			out << " " << (*family.getMember(i)).getId();
	}

	return out;
}

Family& Family::operator=(const Family& family)
{
	size = family.size;
	relation_count = family.relation_count;

	relations = new Relation[relation_count];
	for (unsigned i = 0; i < relation_count; i++)
		relations[i] = family.relations[i];

	members = new Person*[size];
	for (unsigned i = 0; i < size; i++)
		members[i] = family.members[i];

	return *this;
}

#include <fstream>
#include <iostream>
#include <vector>
#include <boost/algorithm/string.hpp>

#include "FamilyTree.h"

#include "Person.h"
#include "Family.h"
#include "Relation.h"
#include "PeopleDynArray.h"
#include "FamilyDynArray.h"

using namespace std;
using namespace boost;

CFamilyTree::CFamilyTree(const char* filename)
{
	string str;
	ifstream file;
	file.open(filename, ios::in);
	if (file.is_open())
	{
		PeopleDynArray people;
		FamilyDynArray families;

		people.Clear();
		families.Clear();

		//Загружаем массив людей
		int i = -1;
		while (getline(file, str))
		{
			if (str == "families") break;

			if (i != -1)
			{
				vector<string> fields;
				split(fields, str, is_any_of(" "), token_compress_on);

				vector<string> date;
				split(date, fields[5], is_any_of("-"), token_compress_on);
				tm *dt = new tm;
				(*dt).tm_year = atoi(date[2].c_str()) - 1900;
				(*dt).tm_mon = atoi(date[1].c_str()) - 1;
				(*dt).tm_mday = atoi(date[0].c_str());

				people.PushBack(Person(Gender(atoi(fields[1].c_str())), fields[2], fields[3], fields[4], dt));

				delete dt;
			}
			i++;
		}

		//Загружаем массив семей
		i = -1;
		while (getline(file, str))
		{
			if (i != -1)
			{
				vector<string> fields;
				split(fields, str, is_any_of(" "), token_compress_on);

				int one = atoi(fields[0].c_str());
				int two = atoi(fields[1].c_str());
				Family f = Family(people.GetById(one), people.GetById(two));
				unsigned k = 2;
				while (k < fields.size())
				{
					if (fields[k].c_str())
					{
						f.AddChild(people.GetById(atoi(fields[k].c_str())));
						k++;
					}
				}

				families.PushBack(f);
			}
			i++;
		}

		file.close();
		if (!Init(people, families))
			cout << "FamilyTree Init Success!" << endl;
		else
			cout << "FamilyTree Init Failed!" << endl;
	}
	else
		cout << "Error opening file! FamilyTree Init Failed!" << endl;
}


CFamilyTree::~CFamilyTree()
{
	cout << "FamilyTree Destruct" << endl;
}

int CFamilyTree::Init(PeopleDynArray &people, FamilyDynArray &families)
{
	// Ищем самого старого человека. Он будет корнем дерева.
	Person oldest;
	int flag = 0;
	for (int i = 0; i < people.GetSize(); i++)
	{
		Person pers = (*people.Get(i));
		if (flag == 0)
		{
			oldest = pers;
			flag = 1;
		}
		else
		{
			if (oldest.dob_year > pers.dob_year)
				oldest = pers;
			else if (oldest.dob_year == pers.dob_year)
			{
				if (oldest.dob_month > pers.dob_month)
					oldest = pers;
				else if (oldest.dob_month == pers.dob_month)
				{
					if (oldest.dob_day > pers.dob_day)
						oldest = pers;
				}
			}
		}
				
	}
	cout << oldest.getId() << " " << oldest.name << endl;
	
	root = CNode(oldest);

	//Теперь смотрим, состоит ли он в семье, если нет, то строим призрачные связи со всеми родителями след. поколения
	for (int i = 0; i < families.GetSize(); i++)
	{

	}

	return 0;
}

CNode CFamilyTree::CreateNode()
{

}

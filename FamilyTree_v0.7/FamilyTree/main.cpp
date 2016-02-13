#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <fstream>

#include <boost/algorithm/string.hpp>

#include "Person.h"
#include "Family.h"
#include "Relation.h"
#include "PeopleDynArray.h"
#include "FamilyDynArray.h"
#include "FamilyTree.h"

using namespace std;
using namespace boost;

int Init();
int Load(PeopleDynArray *people, FamilyDynArray *families, const char* filename);
int Save(PeopleDynArray &people, FamilyDynArray &families, const char* filename);

int main()
{
	/*
	string programName = "FamilyTree v0.7";
	

	PeopleDynArray people;
	FamilyDynArray families;
	*/
	const char* filename = "OurTree.ftf"; // Family Tree File
	CFamilyTree ft1(filename);

 	_getch();
	return 0;
}

int Save(PeopleDynArray &people, FamilyDynArray &families, const char* filename)
{
	ofstream file;
	file.open(filename, ios::out | ios::trunc);
	if (file.is_open())
	{
		file << people;
		file << "families" << endl;
		file << families;
		file.close();
		return 0;
	}
	else
	{
		return 1;
	}
	
}
int Load(PeopleDynArray *people, FamilyDynArray *families, const char* filename)
{
	string str;
	ifstream file;
	file.open(filename, ios::in);
	if (file.is_open())
	{
		(*people).Clear();
		(*families).Clear();

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

				(*people).PushBack(Person(Gender(atoi(fields[1].c_str())), fields[2], fields[3], fields[4], dt));

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

				Family *f = new Family((*people).GetById(atoi(fields[0].c_str())), (*people).GetById(atoi(fields[1].c_str())));
				unsigned k = 2;
				while (k < fields.size())
				{
					if (fields[k].c_str())
					{
						(*f).AddChild((*people).GetById(atoi(fields[k].c_str())));
						k++;
					}
				}

				(*families).PushBack(*f);
			}
			i++;
		}

		file.close();
		return 0;
	}
	else
	{
		return 1;
	}
}
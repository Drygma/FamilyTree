#include <iostream>
#include <string>
#include <vector>
#include <locale>
#include <conio.h>
#include <ctime>
#include <fstream>

#include <boost/algorithm/string.hpp>

#include "Person.h"
#include "Family.h"
#include "Relation.h"
#include "PeopleDynArray.h"
#include "FamilyDynArray.h"

using namespace std;
using namespace boost;

void changePersonData(Person person);

int Init();
int Load(PeopleDynArray *people, FamilyDynArray *families, const char* filename);
int Save(PeopleDynArray &people, FamilyDynArray &families, const char* filename);

int main()
{
	string programName = "FamilyTree v0.7";
	const char* filename = "OurTree.ftf"; // Family Tree File

	PeopleDynArray people;
	FamilyDynArray families;

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

		//��������� ������ �����
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

		//��������� ������ �����
		i = -1;
		while (getline(file, str))
		{
			if (i != -1)
			{
				vector<string> fields;
				split(fields, str, is_any_of(" "), token_compress_on);

				Family *f = new Family((*people).GetById(atoi(fields[0].c_str())), (*people).GetById(atoi(fields[1].c_str())));
				int k = 2;
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

void changePersonData(Person person)
{
	if (person.active == 0)
	{
		cout << "�������������� ���� ������..." << endl;

		cout << "�������� ��� (1 - ������� | 2 - �������): ";
		char c = _getch();
		cout << c << endl;
		while (c)
		{
			if (c == '1')
			{
				person.gender  = MALE;
				break;
			}
			else if (c == '2')
			{
				person.gender = FEMALE;
				break;
			}
			else
			{
				cout << "�������� ��� (1 - ������� | 2 - �������): ";
			}
		}

		string tmp;
		char q = 'n';
		while (q != 'y') 
		{
			cout << "������� �������: ";
			cin >> tmp;
			cout << "�� ����� '" << tmp << "'. ��� �����? (y - �����) ";
			q = _getch();
			cout << endl;
		}
		person.surname = tmp;

		q = 'n';
		while (q != 'y')
		{
			cout << "������� ���: ";
			cin >> tmp;
			cout << "�� ����� '" << tmp << "'. ��� �����? (y - �����) ";
			q = _getch();
			cout << endl;
		}
		person.name = tmp;

		q = 'n';
		while (q != 'y')
		{
			cout << "������� ��������: ";
			cin >> tmp;
			cout << "�� ����� '" << tmp << "'. ��� �����? (y - �����) ";
			q = _getch();
			cout << endl;
		}
		person.otch = tmp;

		tm date;

		time_t now = time(0);
		tm *cur_date = nullptr;
		localtime_s(cur_date, &now);

		int year = 0, month = 0, day = 0;

		q = 'n';
		while (q != 'y')
		{
			while (year < 1900 || year > cur_date->tm_year + 1900)
			{
				cout << "������� ��� �������� (1900-" << cur_date->tm_year + 1900 << "): ";
				cin >> year;
			}
			cout << "�� ����� '" << year << "'. ��� �����? (y - �����) ";
			q = _getch();
			cout << endl;
		}
		date.tm_year = year - 1900;

		q = 'n';
		while (q != 'y')
		{
			while (month < 1 || month > 12)
			{
				cout << "������� ����� ������ �������� (1-12): ";
				cin >> month;
			}
			cout << "�� ����� '" << month << "'. ��� �����? (y - �����) ";
			q = _getch();
			cout << endl;
		}
		date.tm_mon = month - 1;

		q = 'n';
		while (q != 'y')
		{
			while (day < 1 || day > 31)
			{
				cout << "������� ���� �������� (1-31): ";
				cin >> day;
			}
			cout << "�� ����� '" << day << "'. ��� �����? (y - �����) ";
			q = _getch();
			cout << endl;
		}
		date.tm_mday = day;

		person.date_of_birth = new tm;
		person.date_of_birth->tm_year = date.tm_year;
		person.date_of_birth->tm_mon = date.tm_mon;
		person.date_of_birth->tm_mday = date.tm_mday;

		person.active = 1;
	}
	else
	{
		cout << "������� ������..." << endl;
		cout << person.getId() << " " << person.surname << " " << person.name << " " << person.otch << endl;
		
		cout << "���: "; 
		switch (person.gender)
		{
			case MALE:
				cout << "�������";
				break;
			case FEMALE:
				cout << "�������";
				break;
			default:
				break;
		}
		cout << endl;

		cout << "�������(����) " << person.date_of_birth << endl;
		if (person.date_of_death)
		{
			cout << "����(��) " << person.date_of_death << endl;
		}
	}

}
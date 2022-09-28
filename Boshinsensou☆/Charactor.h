#pragma once

#include "System.h"

class Charactor
{
public:
	string Name;
	int ID;
	int HP;

	Charactor(string Name, int ID, int HP)
	{
		this->Name = Name;
		this->ID = ID;
		this->HP = HP;
	}
	Charactor()
	{
		Charactor("", 0, 0);
	}
};

void ShowCharaInfo(Charactor);
string GetCharaDescription(Charactor);
vector<Charactor> GetCharaList();
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
};

void ShowCharaInfo(Charactor);
string GetCharaDescription(Charactor);
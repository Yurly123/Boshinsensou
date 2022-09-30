#pragma once

#include "System.h"
#include <fstream>
#include <sstream>

class Charactor
{
public:
	Name name;
	int ID;
	int HP;
	CharaData CData;

	Charactor(string name, int IsAlt, int ID, int HP)
	{
		this->name = Name(name, IsAlt);
		this->ID = ID;
		this->HP = HP;
	}
	Charactor() : Charactor("", false, 0, 0) { }
};

void ShowCharaInfo(Charactor);
string GetCharaDescription(Charactor);
vector<Charactor> GetAllChara();
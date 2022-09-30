#pragma once

#include <iostream>
#include <vector>
#include <array>

#define Wait getchar();
using namespace std;
class CharaData;
class Charactor;
class Name
{
public:
	string Text;
	bool IsAlt;

	Name(string text, bool isalt)
	{
		Text = text;
		IsAlt = isalt;
	}
	Name() : Name("", false) { }

	string GetPP(string PP)
	{
		//ori 는 가 를 로   와 나   로서   로써
		//alt 은 이 을 으로 과 이나 으로서 으로써
		if (IsAlt)
		{
			if (PP == "는") PP = "은";
			else if (PP == "가") PP = "이";
			else if (PP == "를") PP = "을";
			else if (PP == "로") PP = "으로";
			else if (PP == "와") PP = "과";
			else if (PP == "나") PP = "이나";
			else if (PP == "로서") PP = "으로서";
			else if (PP == "로써") PP = "으로써";
		}
		else
		{
			if (PP == "은") PP = "는";
			else if (PP == "이") PP = "가";
			else if (PP == "을") PP = "를";
			else if (PP == "으로") PP = "로";
			else if (PP == "과") PP = "와";
			else if (PP == "이나") PP = "나";
			else if (PP == "으로서") PP = "로서";
			else if (PP == "으로써") PP = "로써";
		}
		return PP;
	}
};

#include "CharaData.h"
#include "Shop.h"
#include "Train.h"
#include "Charactor.h"

void PrintLine();
int GetInput(vector<int>);
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
		//ori �� �� �� ��   �� ��   �μ�   �ν�
		//alt �� �� �� ���� �� �̳� ���μ� ���ν�
		if (IsAlt)
		{
			if (PP == "��") PP = "��";
			else if (PP == "��") PP = "��";
			else if (PP == "��") PP = "��";
			else if (PP == "��") PP = "����";
			else if (PP == "��") PP = "��";
			else if (PP == "��") PP = "�̳�";
			else if (PP == "�μ�") PP = "���μ�";
			else if (PP == "�ν�") PP = "���ν�";
		}
		else
		{
			if (PP == "��") PP = "��";
			else if (PP == "��") PP = "��";
			else if (PP == "��") PP = "��";
			else if (PP == "����") PP = "��";
			else if (PP == "��") PP = "��";
			else if (PP == "�̳�") PP = "��";
			else if (PP == "���μ�") PP = "�μ�";
			else if (PP == "���ν�") PP = "�ν�";
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
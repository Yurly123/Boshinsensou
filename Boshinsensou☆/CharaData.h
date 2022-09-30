#pragma once

#include "System.h"

class CharaData
{
public:
	enum Cflag
	{
		�ִ�ü�� = 0,
		����ü�� = 1,

	};
	enum CTalent
	{
		���� = 0,
		���� = 1,
		��Ű = 2,
		���� = 3,

	};
	enum Cstr
	{
		�̸� = 0,

	};
	
	array<int, numeric_limits<enum Cflag>::max()> cflag = { 0 };
	array<bool, numeric_limits<enum CTalent>::max()> ctalent = { 0 };
	array<string, numeric_limits<enum Ctr>::max()> cstr = { 0 };
};
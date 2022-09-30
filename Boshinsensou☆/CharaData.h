#pragma once

#include "System.h"

class CharaData
{
public:
	enum Cflag
	{
		최대체력 = 0,
		현재체력 = 1,

	};
	enum CTalent
	{
		남자 = 0,
		여자 = 1,
		쿠키 = 2,
		음몽 = 3,

	};
	enum Cstr
	{
		이름 = 0,

	};
	
	array<int, numeric_limits<enum Cflag>::max()> cflag = { 0 };
	array<bool, numeric_limits<enum CTalent>::max()> ctalent = { 0 };
	array<string, numeric_limits<enum Ctr>::max()> cstr = { 0 };
};
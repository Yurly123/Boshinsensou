#pragma once

#include "System.h"

#include "com000.h"
#include "com009.h"
#include "com010.h"
#include "com999.h"

class Parameter
{
private:
	static map<string, int> Param_ID;
public:
	static int Get(string);
	static string Get(int);
	static map<int, string> ParamList;
	static void Load();
};

class Command
{
public:
	string Name;
	int ID;
	void (*Commit)(Character&, map<int, int>&);
	static void Load();
	static map<int, Command> ComList;

	Command();
	Command(int, string, void(Character&, map<int, int>&));
};
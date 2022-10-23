#pragma once

#include "System.h"

#include "com000.h"
#include "com010.h"
#include "com999.h"

class Parameter
{
private:
	static map<string, int> Param_ID;
public:
	static int GetParam(string);
	static string GetParam(int);
	static map<int, string> ParamList;
	static void LoadParam();
};

class Command
{
public:
	string Name;
	int ID;
	void (*Commit)(Character&, map<int, int>&);
	static void LoadCommands();
	static map<int, Command> ComList;
};
#pragma once

#include "System.h"

#include "com000.h"
#include "com010.h"
#include "com999.h"

class Parameter
{
private:
	static map<int, string> Param_Name;
	static map<string, int> Param_ID;
public:
	static int GetParam(string);
	static string GetParam(int);
	static int Param_Length;
	static void LoadParam();
};

class Command
{
public:
	string Name;
	int ID;
	void (*Commit)(Charactor&, vector<int>&);
	static void LoadCommands();
	static map<int, Command> ComList;
};
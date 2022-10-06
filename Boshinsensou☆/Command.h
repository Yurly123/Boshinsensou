#pragma once

#include "System.h"

#include "com000.h"
#include "com999.h"

class Parameter
{
private:
	static vector<string> Param_Name;
	static unordered_map<string, int> Param_ID;
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
	static unordered_map<int, Command> ComList;
};
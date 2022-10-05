#pragma once

#include "System.h"
#include "com999.h"

class Command
{
public:
	string Name;
	int ID;
	void (*Commit)();
	static void LoadCommands();
	static unordered_map<int, Command> ComList;
};
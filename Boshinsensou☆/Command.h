#pragma once

#include "System.h"

#include "com000.h"
#include "com999.h"

class Command
{
public:
	string Name;
	int ID;
	void (*Commit)(Charactor&);
	static void LoadCommands();
	static unordered_map<int, Command> ComList;
};
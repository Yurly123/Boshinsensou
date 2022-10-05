#include "Command.h"
#include "999.cpp"

void(*Commit) = NULL;
unordered_map<int, Command> ComList = unordered_map<int, Command>();

void Command::LoadCommands()
{
	Loadcom999();
}
#include "Command.h"

unordered_map<int, Command> Command::ComList = unordered_map<int, Command>();

void Command::LoadCommands()
{
	Loadcom000();
	Loadcom999();
}
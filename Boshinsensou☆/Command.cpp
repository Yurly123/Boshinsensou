#include "Command.h"

unordered_map<int, Command> Command::ComList = unordered_map<int, Command>();

void Command::LoadCommands()
{
	Loadcom999();
}
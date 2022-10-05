#include "System.h"

void Command999()
{

}

void Loadcom999()
{
	Command::ComList.emplace(make_pair(999, Command()));
	Command::ComList[999].ID = 999;
	Command::ComList[999].Name = "훈련 종료";
	Command::ComList[999].Commit = Command999;
}
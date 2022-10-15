#include "Command.h"

map<int, Command> Command::ComList = map<int, Command>();
map<int, string> Parameter::Param_Name = map<int, string>();
map<string, int> Parameter::Param_ID = map<string, int>();
int Parameter::Param_Length = 0;

void Parameter::LoadParam()
{
	ifstream ParamS("CSV\\Param.csv");
	string Buffer;

	while (!ParamS.eof())
	{
		getline(ParamS, Buffer, ',');
		int id = stoi(Buffer);

		getline(ParamS, Buffer, ',');
		string name = Buffer;

		Param_Name.emplace(make_pair(id, name));
		Param_ID.emplace(make_pair(name, id));
		++Param_Length;

		getline(ParamS, Buffer);
	}

	ParamS.close();
}
int Parameter::GetParam(string name)
{
	return Param_ID[name];
}
string Parameter::GetParam(int id)
{
	return Param_Name[id];
}

void Command::LoadCommands()
{
	Loadcom000();
	Loadcom010();
	Loadcom999();
}
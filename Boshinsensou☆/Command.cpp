#include "Command.h"

map<int, Command> Command::ComList = map<int, Command>();
map<string, int> Parameter::Param_ID = map<string, int>();
map<int, string> Parameter::ParamList = map<int, string>();

Command::Command()
{

}
Command::Command(int ID, string Name, void Commit (Character&, map<int, int>&))
{
	this->ID = ID;
	this->Name = Name;
	this->Commit = Commit;
}
void Parameter::LoadParam()
{
	ifstream paramStream("CSV\\Param.csv");
	string Buffer;

	while (!paramStream.eof())
	{
		getline(paramStream, Buffer, ',');
		int id = stoi(Buffer);

		getline(paramStream, Buffer, ',');
		string name = Buffer;

		Param_ID[name] = id;
		ParamList[id] = name;

		getline(paramStream, Buffer);
	}

	paramStream.close();
}
int Parameter::GetParam(string name)
{
	return Param_ID[name];
}
string Parameter::GetParam(int id)
{
	return ParamList[id];
}

void Command::LoadCommands()
{
	Loadcom000();
	Loadcom009();
	Loadcom010();
	Loadcom999();
}
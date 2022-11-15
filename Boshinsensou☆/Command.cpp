#include "Command.h"

#pragma region 클래스 멤버

#pragma region Command
map<int, Command> Command::ComList = map<int, Command>();

Command::Command()
{

}
Command::Command(int ID, string Name, void Commit (Character&, map<int, int>&))
{
	this->ID = ID;
	this->Name = Name;
	this->Commit = Commit;
}
#pragma endregion

#pragma region Parameter
map<string, int> Parameter::Param_ID = map<string, int>();
map<int, string> Parameter::ParamList = map<int, string>();

void Parameter::LoadParam()
{
	ifstream paramStream("CSV\\Param.csv");
	string buffer;

	while (!paramStream.eof())
	{
		getline(paramStream, buffer, ',');
		int id = stoi(buffer);

		getline(paramStream, buffer, ',');
		string name = buffer;

		Param_ID[name] = id;
		ParamList[id] = name;

		getline(paramStream, buffer);
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
#pragma endregion

#pragma endregion
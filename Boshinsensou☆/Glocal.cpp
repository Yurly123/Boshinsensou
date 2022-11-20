#include "Glocal.h"

#pragma region 클래스 멤버

#pragma region Global
map<string, int> Global::Global_ID = map<string, int>();
map<int, string> Global::Global_Name = map<int, string>();
map<int, int> Global::GlobalList = map<int, int>();

int Global::Get(string name)
{
	return GlobalList[Global_ID[name]];
}
string Global::Get(int id)
{
	return Global_Name[id];
}
void Global::Set(string name, int value)
{
	GlobalList[Global_ID[name]] = value;
}
void Global::Add(string name, int value)
{
	GlobalList[Global_ID[name]] += value;
}
void Global::Load()
{
	ifstream globalStream("CSV\\Global.csv");
	string buffer;

	while (!globalStream.eof())
	{
		getline(globalStream, buffer, ',');
		int id = stoi(buffer);

		getline(globalStream, buffer, ',');
		string name = buffer;

		Global_ID[name] = id;
		Global_Name[id] = name;
		GlobalList[id] = 0;

		getline(globalStream, buffer);
	}

	globalStream.close();
}
#pragma endregion

#pragma region Local
map<string, int> Local::Local_ID = map<string, int>();
map<int, string> Local::Local_Name = map<int, string>();
map<int, int> Local::LocalList = map<int, int>();

int Local::Get(string name)
{
	return LocalList[Local_ID[name]];
}
string Local::Get(int id)
{
	return Local_Name[id];
}
void Local::Set(string name, int value)
{
	LocalList[Local_ID[name]] = value;
}
void Local::Add(string name, int value)
{
	LocalList[Local_ID[name]] += value;
}
void Local::Load()
{
	ifstream localStream("CSV\\Local.csv");
	string buffer;

	while (!localStream.eof())
	{
		getline(localStream, buffer, ',');
		int id = stoi(buffer);

		getline(localStream, buffer, ',');
		string name = buffer;

		Local_ID[name] = id;
		Local_Name[id] = name;
		LocalList[id] = 0;

		getline(localStream, buffer);
	}

	localStream.close();
}
#pragma endregion

#pragma endregion

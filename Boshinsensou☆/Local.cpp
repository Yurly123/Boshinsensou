#include "Local.h"

#pragma region 클래스 멤버

#pragma region Local
map<string, int> Local::Local_ID = map<string, int>();
map<int, string> Local::Local_Name = map<int, string>();
map<int, int> Local::LocalList = map<int, int>();

int Local::GetLocal(string name)
{
	return LocalList[Local_ID[name]];
}
string Local::GetLocal(int id)
{
	return Local_Name[id];
}
void Local::SetLocal(string name, int value)
{
	LocalList[Local_ID[name]] = value;
}
void Local::AddLocal(string name, int value)
{
	LocalList[Local_ID[name]] += value;
}
void Local::LoadLocal()
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

#include "Local.h"

#pragma region 클래스 멤버

#pragma region Local
map<string, int> Local::Local_ID = map<string, int>();
map<int, string> Local::LocalList = map<int, string>();
map<int, int> Local::Locals = map<int, int>();

int Local::GetLocal(string name)
{
	return Local_ID[name];
}
string Local::GetLocal(int id)
{
	return LocalList[id];
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
		LocalList[id] = name;

		getline(localStream, buffer);
	}

	localStream.close();
}
#pragma endregion

#pragma endregion

#include "CData.h"

#pragma region 클래스 멤버

#pragma region CData
map<int, string> CData::CFlagList = map<int, string>();
map<int, string> CData::CTalentList = map<int, string>();
map<int, string> CData::CStrList = map<int, string>();
map<string, int> CData::CFlag_ID = map<string, int>();
map<string, int> CData::CTalent_ID = map<string, int>();
map<string, int> CData::CStr_ID = map<string, int>();

void CData::Load()
{
	ifstream flagStream("CSV\\CFlag.csv");
	ifstream talentStream("CSV\\CTalent.csv");
	ifstream strStream("CSV\\CStr.csv");
	string Buffer;

	while (!flagStream.eof())
	{
		getline(flagStream, Buffer, ',');
		int id = stoi(Buffer);

		getline(flagStream, Buffer, ',');
		string name = Buffer;

		CFlagList[id] = name;
		CFlag_ID[name] = id;

		getline(flagStream, Buffer);
	}
	while (!talentStream.eof())
	{
		getline(talentStream, Buffer, ',');
		int id = stoi(Buffer);

		getline(talentStream, Buffer, ',');
		string name = Buffer;

		CTalentList[id] = name;
		CTalent_ID[name] = id;

		getline(talentStream, Buffer);
	}
	while (!strStream.eof())
	{
		getline(strStream, Buffer, ',');
		int id = stoi(Buffer);

		getline(strStream, Buffer, ',');
		string name = Buffer;

		CStrList[id] = name;
		CStr_ID[name] = id;

		getline(strStream, Buffer);
	}
}
int CData::Flag(string name)
{
	return CFlag_ID[name];
}
string CData::Flag(int id)
{
	return CFlagList[id];
}
int CData::Talent(string name)
{
	return CTalent_ID[name];
}
string CData::Talent(int id)
{
	return CTalentList[id];
}
int CData::Str(string name)
{
	return CStr_ID[name];
}
string CData::Str(int id)
{
	return CStrList[id];
}
#pragma endregion

#pragma endregion

#pragma region 전역 함수

void LoadDefaultCData(string filepath, Character& chara)
{
	ifstream FileStream(filepath);
	if (!FileStream.is_open() || !FileStream.good()) return;

	while (!FileStream.eof())
	{
		string Buffer;
		getline(FileStream, Buffer, ',');

		if (Buffer == "flag")
		{
			getline(FileStream, Buffer, ',');
			int index = stoi(Buffer);
			
			getline(FileStream, Buffer, ',');
			int value = stoi(Buffer);

			chara.Cflag[index] = value;
		}
		else if (Buffer == "talent")
		{
			getline(FileStream, Buffer, ',');
			int index = stoi(Buffer);

			chara.Ctalent[index] = true;
		}
		else if (Buffer == "str")
		{
			getline(FileStream, Buffer, ',');
			int index = stoi(Buffer);

			getline(FileStream, Buffer, ',');
			string str = Buffer;

			chara.Cstr[index] = str;
		}

		getline(FileStream, Buffer);
	}

	FileStream.close();
}

#pragma endregion
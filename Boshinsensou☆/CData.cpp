#include "CData.h"

vector<string> CData::CFlag_Name = vector<string>();
vector<string> CData::CTalent_Name = vector<string>();
vector<string> CData::CStr_Name = vector<string>();
unordered_map<string, int> CData::CFlag_ID = unordered_map<string, int>();
unordered_map<string, int> CData::CTalent_ID = unordered_map<string, int>();
unordered_map<string, int> CData::CStr_ID = unordered_map<string, int>();
int CData::Flag_Length = 0;
int CData::Talent_Length = 0;
int CData::Str_Length = 0;

void CData::LoadCDatas()
{
	ifstream FlagS("CSV\\CFlag.csv");
	ifstream TalentS("CSV\\CTalent.csv");
	ifstream StrS("CSV\\CStr.csv");
	string Buffer;

	while (!FlagS.eof())
	{
		getline(FlagS, Buffer, ',');
		int id = stoi(Buffer);

		getline(FlagS, Buffer, ',');
		string name = Buffer;

		CFlag_Name.emplace(CFlag_Name.begin() + id, name);
		CFlag_ID.emplace(make_pair(name, id));
		++Flag_Length;

		getline(FlagS, Buffer);
	}
	while (!TalentS.eof())
	{
		getline(TalentS, Buffer, ',');
		int id = stoi(Buffer);

		getline(TalentS, Buffer, ',');
		string name = Buffer;

		CTalent_Name.emplace(CTalent_Name.begin() + id, name);
		CTalent_ID.emplace(make_pair(name, id));
		++Talent_Length;

		getline(TalentS, Buffer);
	}
	while (!StrS.eof())
	{
		getline(StrS, Buffer, ',');
		int id = stoi(Buffer);

		getline(StrS, Buffer, ',');
		string name = Buffer;

		CStr_Name.emplace(CStr_Name.begin() + id, name);
		CStr_ID.emplace(make_pair(name, id));
		++Str_Length;

		getline(StrS, Buffer);
	}
}
int CData::GetFlag(string name)
{
	return CFlag_ID[name];
}
string CData::GetFlag(int id)
{
	return CFlag_Name[id];
}
int CData::GetTalent(string name)
{
	return CTalent_ID[name];
}
string CData::GetTalent(int id)
{
	return CTalent_Name[id];
}
int CData::GetStr(string name)
{
	return CStr_ID[name];
}
string CData::GetStr(int id)
{
	return CStr_Name[id];
}

void LoadDefaultCData(string filepath, Charactor& chara)
{
	ifstream FileStream(filepath);
	if (!FileStream.is_open()) return;

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
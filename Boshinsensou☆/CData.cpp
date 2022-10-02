#include "CData.h"

vector<string> CData::CFlag_Name = vector<string>();
vector<string> CData::CTalent_Name = vector<string>();
vector<string> CData::CStr_Name = vector<string>();
unordered_map<string, int> CData::CFlag_ID = unordered_map<string, int>();
unordered_map<string, int> CData::CTalent_ID = unordered_map<string, int>();
unordered_map<string, int> CData::CStr_ID = unordered_map<string, int>();
int CData::CFlag_Length = 0;
int CData::CTalent_Length = 0;
int CData::CStr_Length = 0;

CData::CData()
{
	cflag = vector<int>(CFlag_Length, 0);
	ctalent = vector<bool>(CTalent_Length, false);
	cstr = vector<string>(CStr_Length, "");
}
void CData::LoadCDatas()
{
	ifstream FlagS("CFlag.csv");
	ifstream TalentS("CTalent.csv");
	ifstream StrS("CStr.csv");
	string Buffer;

	while (!FlagS.eof())
	{
		getline(FlagS, Buffer, ',');
		int id = stoi(Buffer);

		getline(FlagS, Buffer, ',');
		string name = Buffer;

		CFlag_Name.emplace(CFlag_Name.begin() + id, name);
		CFlag_ID.emplace(make_pair(name, id));
		++CFlag_Length;

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
		++CTalent_Length;

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
		++CStr_Length;

		getline(StrS, Buffer);
	}
}
int CData::CFlag(string name)
{
	return CFlag_ID[name];
}
string CData::CFlag(int id)
{
	return CFlag_Name[id];
}
int CData::CTalent(string name)
{
	return CTalent_ID[name];
}
string CData::CTalent(int id)
{
	return CTalent_Name[id];
}
int CData::CStr(string name)
{
	return CStr_ID[name];
}
string CData::CStr(int id)
{
	return CStr_Name[id];
}

CData LoadCharaData(string filepath)
{
	ifstream FileStream(filepath);
	CData charaData;
	if (!FileStream.is_open()) return charaData;

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

			charaData.cflag[index] = value;
		}
		else if (Buffer == "talent")
		{
			getline(FileStream, Buffer, ',');
			int index = stoi(Buffer);

			charaData.ctalent[index] = true;
		}
		else if (Buffer == "str")
		{
			getline(FileStream, Buffer, ',');
			int index = stoi(Buffer);

			getline(FileStream, Buffer, ',');
			string str = Buffer;

			charaData.cstr[index] = str;
		}

		getline(FileStream, Buffer);
	}

	FileStream.close();
	return charaData;
}
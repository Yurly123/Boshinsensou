#include "CData.h"

map<int, string> CData::CFlag_Name = map<int, string>();
map<int, string> CData::CTalent_Name = map<int, string>();
map<int, string> CData::CStr_Name = map<int, string>();
map<string, int> CData::CFlag_ID = map<string, int>();
map<string, int> CData::CTalent_ID = map<string, int>();
map<string, int> CData::CStr_ID = map<string, int>();
int CData::Flag_Length = 0;
int CData::Talent_Length = 0;
int CData::Str_Length = 0;

void CData::LoadCDatas()
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

		CFlag_Name[id] = name;
		CFlag_ID[name] = id;
		++Flag_Length;

		getline(flagStream, Buffer);
	}
	while (!talentStream.eof())
	{
		getline(talentStream, Buffer, ',');
		int id = stoi(Buffer);

		getline(talentStream, Buffer, ',');
		string name = Buffer;

		CTalent_Name[id] = name;
		CTalent_ID[name] = id;
		++Talent_Length;

		getline(talentStream, Buffer);
	}
	while (!strStream.eof())
	{
		getline(strStream, Buffer, ',');
		int id = stoi(Buffer);

		getline(strStream, Buffer, ',');
		string name = Buffer;

		CStr_Name[id] = name;
		CStr_ID[name] = id;
		++Str_Length;

		getline(strStream, Buffer);
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

void AbstractEP(Charactor& chara, int amount)
{
	if (chara.GetCflag("현재기력") - amount >= 0)
	{
		chara.AddCflag("현재기력", -amount);
	}
	else if (chara.GetCflag("현재기력") > 0)
	{
		chara.SetCflag("현재기력", 0);
	}
	else
	{
		chara.AddCflag("현재체력", -amount);
	}
}
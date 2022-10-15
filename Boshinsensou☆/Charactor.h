#pragma once

#include "System.h"
#include <fstream>
#include <sstream>

static class CData
{
private:
	static map<int, string> CFlag_Name;
	static map<int, string> CTalent_Name;
	static map<int, string> CStr_Name;
	static map<string, int> CFlag_ID;
	static map<string, int> CTalent_ID;
	static map<string, int> CStr_ID;
public:
	static int GetFlag(string);
	static int GetTalent(string);
	static int GetStr(string);
	static string GetFlag(int);
	static string GetTalent(int);
	static string GetStr(int);
	static int Flag_Length;
	static int Talent_Length;
	static int Str_Length;
	static void LoadCDatas();
};

class Name
{
private:
	string Text;
public:
	bool IsAlt;

	Name(string = "", bool = false);
	string GetPP(string);
	string WithPP(string);
	operator string() const
	{
		return Text;
	}
	friend ostream& operator <<(ostream& out, const Name& name)
	{
		out << name.Text;
		return out;
	}
};

class Charactor
{
private:
	void LoadCData();
public:
	Name Name;
	int ID;
	map<int, int> Cflag;
	map<int, bool> Ctalent;
	map<int, string> Cstr;
	int GetCflag(string);
	bool GetCtalent(string);
	string GetCstr(string);
	void SetCflag(string, int);
	void SetCtalent(string, bool);
	void SetCstr(string, string);
	void AddCflag(string, int);

	static vector<Charactor> CharaList;
	static void LoadCharaList();
	Charactor(string = "", bool = false, int = -1);
};

string GetCharaDescription(Charactor&);
void PrintCharaHPEP(Charactor&);
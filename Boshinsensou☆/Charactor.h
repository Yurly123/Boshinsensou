#pragma once

#include "System.h"
#include <fstream>
#include <sstream>

static class CData
{
private:
	static unordered_map<int, string> CFlag_Name;
	static unordered_map<int, string> CTalent_Name;
	static unordered_map<int, string> CStr_Name;
	static unordered_map<string, int> CFlag_ID;
	static unordered_map<string, int> CTalent_ID;
	static unordered_map<string, int> CStr_ID;
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
public:
	string Text;
	bool IsAlt;

	Name(string = "", bool = false);
	string GetPP(string);
	string WithPP(string);
};

class Charactor
{
private:
	void LoadCData();
	static vector<Charactor> CharaList;
public:
	Name Name;
	int ID;
	vector<int> Cflag;
	vector<bool> Ctalent;
	vector<string> Cstr;

	static void LoadCharaList();
	static void UpdateCharaList(vector<Charactor>&);
	static vector<Charactor> GetAllChara();
	Charactor(string = "", bool = false, int = -1);
};

string GetCharaDescription(Charactor&);
void PrintCharaHPEP(Charactor&);
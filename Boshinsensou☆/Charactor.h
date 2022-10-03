#pragma once

#include "System.h"
#include <fstream>
#include <sstream>

class CData
{
private:
	static vector<string> CFlag_Name;
	static vector<string> CTalent_Name;
	static vector<string> CStr_Name;
	static unordered_map<string, int> CFlag_ID;
	static unordered_map<string, int> CTalent_ID;
	static unordered_map<string, int> CStr_ID;
public:
	static int CFlag(string);
	static int CTalent(string);
	static int CStr(string);
	static string CFlag(int);
	static string CTalent(int);
	static string CStr(int);
	static int CFlag_Length;
	static int CTalent_Length;
	static int CStr_Length;
	static void LoadCDatas();

	vector<int> cflag;
	vector<bool> ctalent;
	vector<string> cstr;

	CData();
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
	CData cData;

	static void LoadCharaList();
	static void UpdateCharaList(vector<Charactor>);
	static vector<Charactor> GetAllChara();
	Charactor(string = "", bool = false, int = -1);
};

string GetCharaDescription(Charactor);
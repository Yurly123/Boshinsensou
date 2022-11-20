#pragma once

#include "System.h"

class Global
{
private:
	static map<int, string> Global_Name;
	static map<string, int> Global_ID;
public:
	static string Get(int);
	static int Get(string);
	static void Set(string, int);
	static void Add(string, int);
	static void Load();
	static map<int, int> GlobalList;
};

class Local
{
private:
	static map<int, string> Local_Name;
	static map<string, int> Local_ID;
public:
	static string Get(int);
	static int Get(string);
	static void Set(string, int);
	static void Add(string, int);
	static void Load();
	static map<int, int> LocalList;
};
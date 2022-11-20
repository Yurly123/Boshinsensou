#pragma once

#include "System.h"

class Local
{
private:
	static map<int, string> Local_Name;
	static map<string, int> Local_ID;
public:
	static string GetLocal(int);
	static int GetLocal(string);
	static void SetLocal(string, int);
	static void AddLocal(string, int);
	static void LoadLocal();
	static map<int, int> LocalList;
};
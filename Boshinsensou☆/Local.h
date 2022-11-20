#pragma once

#include "System.h"

class Local
{
private:
	static map<string, int> Local_ID;
public:
	int GetLocal(string);
	static string GetLocal(int);
	static void LoadLocal();
	static map<int, string> LocalList;

	static map<int, int> Locals;
};
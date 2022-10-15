#pragma once

#include <iostream>
#include <iomanip>
#include <vector>
#include <array>
#include <map>
#include <Windows.h>
#include <ctime>
#include <cstdlib>

#define Wait getchar();
#define SetColor(color) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color)
using namespace std;
class CData;
class Name;
class Charactor;
class Command;

#include "CData.h"
#include "Shop.h"
#include "Train.h"
#include "Charactor.h"
#include "SaveLoad.h"
#include "Command.h"

void PrintLine();
int GetInput(vector<int>);
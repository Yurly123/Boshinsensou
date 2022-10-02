#pragma once

#include <iostream>
#include <iomanip>
#include <vector>
#include <array>
#include <unordered_map>
#include <Windows.h>

#define Wait getchar();
#define SetColor(color) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color)
using namespace std;
class CData;
class Name;
class Charactor;

#include "CData.h"
#include "Shop.h"
#include "Train.h"
#include "Charactor.h"
#include "SaveLoad.h"

void PrintLine();
int GetInput(vector<int>);
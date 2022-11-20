#pragma once

#include "System.h"
#include <fstream>
#include <sstream>
#include <chrono>
#include <ctime>

int SelectSaveSlot(int);
ifstream GetSlotStream(int);
void Save(int, int);
void Load(int, int&);
stringstream Encode(stringstream&);
stringstream Decode(stringstream&);
void AutoSave(int);
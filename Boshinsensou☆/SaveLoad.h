#pragma once

#include "System.h"
#include <fstream>
#include <sstream>
#include <chrono>
#include <ctime>

int SelectSaveSlot(int);
ifstream GetSlotStream(int);
void Save(int);
void Load(int);
stringstream Encode(stringstream&);
stringstream Decode(stringstream&);
void AutoSave();
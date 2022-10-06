#pragma once

#include "System.h"
#include <fstream>
#include <chrono>
#include <ctime>

int SelectSaveSlot(int);
ifstream GetSlotStream(int);
void Save(int, Charactor&);
void Load(int, Charactor&);
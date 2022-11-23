#pragma once

#include "System.h"

void Train(Character&);
map<int, int> TrainLoop(Character&);
void AbstractEP(Character&, int);
void ImproveCharaStat(Character&, map<int, int>&);
void UpCStat(Character&, map<int, int>&, int);
map<int, int> StatRequirement(int, Character&, map<int, int>&, bool&);
#pragma once
#include "System.h"

void Battle(Character&);
void BattleMap(Character&);
void PrintBattleMap(int);
void BattleLoop(Character&, Enemy&);
void PrintHpBar(Character&);
void PrintEpBar(Character&);
void ChangeTurn(Character&, Enemy&);
void Attack(Character&, Character&);
void ConsumeEp(Character&, int);
void GetDamage(Character&, int);
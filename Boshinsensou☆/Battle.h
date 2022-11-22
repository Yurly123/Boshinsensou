#pragma once
#include "System.h"

enum passive
{
	NONE,
	BeforeCommand,
	MyEpChange,
	MyHpChange,
	EnemyEpChange,
	EnemyHpChange,
	DoneAttack,
	GotAttack,
};

void Battle(Character&);
void BattleMap(Character&);
void PrintBattleMap(int);
void BattleLoop(Character&, Enemy&);
void PrintHpBar(Character&);
void PrintEpBar(Character&);
void ChangeTurn(Character&, Enemy&);
void Attack(Character&, Character&);
void ConsumeEp(Character&, Character&, int);
void GetDamage(Character&, Character&, int);
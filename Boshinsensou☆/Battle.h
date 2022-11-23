#pragma once
#include "System.h"

enum passive
{
	NONE,
	Interface,
	MyEpConsume,
	MyHpDamage,
	EnemyEpConsume,
	EnemyHpDamage,
	DoneAttack,
	GotAttack,
	TurnStart,
	TurnEnd,
	EndOfBattle,
};

void Battle(Character&);
void PrintBattleMap(int);
void BattleLoop(Character&, Enemy&);
void PrintHpBar(Character&);
void PrintEpBar(Character&);
void ChangeTurn(Character&, Enemy&);
void Attack(Character&, Character&);
void Guard(Character&, Character&);
void UseTurnSkill(Character&, Character&);
void UseEpSkill(Character&, Character&);
void ConsumeEp(Character&, Character&, int);
void GetDamage(Character&, Character&, int);
bool Run(Character&, Enemy&);
void Win(Character&, Enemy&);
void PrintHpEpChange(Character&);
void PrintBattleInterface(Character&, Enemy&, void (*)(passive, Character&, Character&));
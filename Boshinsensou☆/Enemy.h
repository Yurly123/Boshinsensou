#pragma once

#include "System.h"

class Enemy
{
public:
	static void LoadEnemy();
	static vector<Enemy> EnemyList;
	static int Progression;

	int id;
	string name;

	Enemy(int = -1, string = "");
};

void ShowEnemyInfo(Enemy&);
string GetEnemyDescription(int);
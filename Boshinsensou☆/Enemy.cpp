#include "Enemy.h"

#pragma region 클래스 멤버

#pragma region Enemy
vector<Enemy> Enemy::EnemyList = vector<Enemy>();

Enemy::Enemy(Character& chara)
{
	this->ID = chara.ID;
	this->Name = chara.Name;
	this->Cflag = chara.Cflag;
	this->Ctalent = chara.Ctalent;
	this->Cstr = chara.Cstr;
}
#pragma endregion

#pragma endregion

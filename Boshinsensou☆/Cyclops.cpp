#include "System.h"

void Cyclops_Load()
{
	Enemy::TurnSkillList["AI사이클롭스"] = Cyclops_Turn;
	Enemy::EpSkillList["AI사이클롭스"] = Cyclops_EP;
	Enemy::PassiveSkillList["AI사이클롭스"] = Cyclops_Passive;
	Enemy::EnemyAIList["AI사이클롭스"] = Cyclops_AI;
}

void Cyclops_AI(Enemy& enemy, Character& chara)
{

}

void Cyclops_Turn(Character& enemy, Character& chara)
{

}

void Cyclops_EP(Character& enemy, Character& chara)
{

}

void Cyclops_Passive(passive timing, Character& chara, Character& enemy)
{

}
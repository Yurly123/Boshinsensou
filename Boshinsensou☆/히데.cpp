#include "히데.h"

void 히데_Load()
{
	Enemy::TurnSkillList["히데"] = 히데_Turn;
	Enemy::EpSkillList["히데"] = 히데_EP;
	Enemy::PassiveSkillList["히데"] = 히데_Passive;
	Enemy::EnemyAIList["히데"] = 히데_AI;
}

void 히데_AI(Enemy& enemy, Character& chara)
{
	Attack(enemy, chara);
}

void 히데_Turn(Character&, Character&)
{

}

void 히데_EP(Character&, Character&)
{

}

void 히데_Passive(passive, Character&, Character&)
{

}
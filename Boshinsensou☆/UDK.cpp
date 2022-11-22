#include "UDK.h"

void UDK_LoadSkill()
{
	Character::TurnSkillList["UDK"] = UDK_Turn;
	Character::EpSkillList["UDK"] = UDK_EP;
	Character::PassiveSkillList["UDK"] = UDK_Passive;
}

void UDK_Turn(Character& chara, Character& enemy)
{

}

void UDK_EP(Character&, Character&)
{

}

void UDK_Passive(passive, Character&, Character&)
{

}
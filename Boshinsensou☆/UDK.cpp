#include "UDK.h"

void UDK_Load()
{
	Character::TurnSkillList["UDK"] = UDK_Turn;
	Character::EpSkillList["UDK"] = UDK_EP;
	Character::PassiveSkillList["UDK"] = UDK_Passive;
}

void UDK_Turn(Character& chara, Character& enemy)
{
	int amount = 20;
	ConsumeEp(enemy, chara, amount);
	cout << enemy.Name.WithPP("의") << " 기력이 " << amount << "만큼 감소했다" << endl;
	Wait;
}

void UDK_EP(Character& chara, Character& enemy)
{
	int damage = 50;
	GetDamage(enemy, chara, damage);
	cout << enemy.Name.WithPP("에게") << " " << damage << "의 데미지" << endl;
	Wait;
}

void UDK_Passive(passive timing, Character& chara, Character& enemy)
{
	if (timing == Interface && Local::Get("턴") % 2)
	{
		int amount = 10;
		if (chara.GetFlag("기력변화") == 0)
			chara.AddFlag("현재기력", amount);

		cout << "                         ";
		cout << chara.GetStr("패시브스킬") << "의 효과로 " << chara.Name << "의 기력 " << amount << "회복";
	}
}
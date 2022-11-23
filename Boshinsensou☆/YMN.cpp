#include "YMN.h"

void YMN_Load()
{
	Character::TurnSkillList["YMN"] = YMN_Turn;
	Character::EpSkillList["YMN"] = YMN_EP;
	Character::PassiveSkillList["YMN"] = YMN_Passive;
}

void YMN_Turn(Character& chara, Character& enemy)
{
	double damageMultiple = 3.0;

	GetDamage(enemy, chara, chara.GetFlag("공격력") * damageMultiple);

	cout << chara.Name.WithPP("은") << " 검을 능숙하게 휘둘러 " << enemy.Name.WithPP("를") << " 잘게 베어낸다." << endl;
	Wait;

	cout << enemy.Name.WithPP("에게") << " " << -enemy.GetFlag("체력변화") << "의 데미지" << endl;
	Wait;
}

void YMN_EP(Character& chara, Character& enemy)
{
	double damageAddition = -chara.GetFlag("기력변화");

	GetDamage(enemy, chara, chara.GetFlag("공격력") + damageAddition);

	cout << chara.Name.WithPP("은") << " 체내의 기를 한 곳으로 모아 " << enemy.Name << " 방향으로 방출했다." << endl;
	Wait;

	cout << enemy.Name.WithPP("에게") << " " << -enemy.GetFlag("체력변화") << "의 데미지" << endl;
	Wait;
}

void YMN_Passive(passive timing, Character& chara, Character& enemy)
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
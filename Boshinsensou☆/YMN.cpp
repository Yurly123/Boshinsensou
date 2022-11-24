#include "System.h"

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

	cout << chara.Name.WithPP("은") << " 검을 능숙하게 휘둘러 " << enemy.Name.WithPP("를") << " 잘게 베어낸다" << endl;
	Wait;

	cout << enemy.Name.WithPP("에게") << " " << -enemy.GetFlag("체력변화") << "의 데미지" << endl;
	Wait;
}

void YMN_EP(Character& chara, Character& enemy)
{
	double damageAddition = -chara.GetFlag("기력변화") / 2.0;

	GetDamage(enemy, chara, chara.GetFlag("공격력") + damageAddition);

	cout << chara.Name.WithPP("은") << " 체내의 기를 한 곳으로 모아 " << enemy.Name << " 방향으로 방출했다" << endl;
	Wait;

	cout << enemy.Name.WithPP("에게") << " " << -enemy.GetFlag("체력변화") << "의 데미지" << endl;
	Wait;
}

void YMN_Passive(passive timing, Character& chara, Character& enemy)
{
	if (chara.GetTalent("이어지는의지"))
	{
		double defenseIncrease = chara.GetFlag("방어력") * 5.0;

		switch (timing)
		{
		case TurnEnd:
			chara.AddFlag("방어력", defenseIncrease);
			break;
		case TurnStart:
			chara.AddFlag("방어력", -defenseIncrease);
			break;
		}
	}
}
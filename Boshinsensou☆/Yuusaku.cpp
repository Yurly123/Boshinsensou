#include "System.h"

void Yuusaku_Load()
{
	Enemy::TurnSkillList["유사쿠"] = Yuusaku_Turn;
	Enemy::EpSkillList["유사쿠"] = Yuusaku_EP;
	Enemy::PassiveSkillList["유사쿠"] = Yuusaku_Passive;
	Enemy::EnemyAIList["유사쿠"] = Yuusaku_AI;
}

void Yuusaku_AI(Enemy& enemy, Character& chara)
{
	if (enemy.GetFlag("턴대기") >= enemy.GetFlag("턴스킬대기시간") && chara.GetFlag("말벌") >= 5)
		UseTurnSkill(enemy, chara);
	else if (enemy.GetFlag("현재기력") >= enemy.GetFlag("기력스킬소모량"))
		UseEpSkill(enemy, chara);
	else
		Attack(enemy, chara);
}

void Yuusaku_Turn(Character& enemy, Character& chara)
{
	int hornetDamage = 10;
	GetDamage(chara, enemy, hornetDamage * chara.GetFlag("말벌"));
	chara.SetFlag("말벌", 0);

	cout << enemy.Name.WithPP("는") << " 모든 말벌들에게 일제히 공격하라고 지시했다" << endl;
	Wait;

	cout << chara.Name.WithPP("에게") << " 붙은 모든 말벌들은 " << -chara.GetFlag("체력변화") << "의 데미지를 입히고 물러났다" << endl;
	Wait;
}

void Yuusaku_EP(Character& enemy, Character& chara)
{
	chara.AddFlag("말벌", 2);

	cout << enemy.Name.WithPP("는") << " " << chara.Name.WithPP("에게") << " 말벌을 끌어들였다" << endl;
	Wait;

	cout << enemy.Name.WithPP("에게") << " 붙은 현재 말벌수는" << chara.GetFlag("말벌") << "마리 이다." << endl;
	Wait;
}

void Yuusaku_Passive(passive timing, Character& chara, Character& enemy)
{
	int hornetDamage = 5;
	if (timing == BeforeInput)
		GetDamage(chara, enemy, hornetDamage * chara.GetFlag("말벌"));
	else if (timing == Interface)
	{
		cout << "                         ";
		cout << "현재 " << chara.Name.WithPP("에게") << " 붙은 말벌은 " << chara.GetFlag("말벌") << "마리 입니다.";
	}
	else if (timing == DoneAttack)
	{
		chara.AddFlag("말벌", 1);
		cout << chara.Name.WithPP("에게") << " 말벌이 붙어 " << chara.GetFlag("말벌") << "마리가 되었습니다." << endl;
		Wait;
	}
}
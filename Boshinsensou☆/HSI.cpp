#include "System.h"

void HSI_Load()
{
	Enemy::TurnSkillList["HSI"] = HSI_Turn;
	Enemy::EpSkillList["HSI"] = HSI_EP;
	Enemy::PassiveSkillList["HSI"] = HSI_Passive;
	Enemy::EnemyAIList["HSI"] = HSI_AI;
}

void HSI_AI(Enemy& enemy, Character& chara)
{
	if (enemy.GetFlag("턴대기") >= enemy.GetFlag("턴스킬대기시간"))
		UseTurnSkill(enemy, chara);
	else
	{
		if (enemy.GetFlag("현재기력") >= enemy.GetFlag("기력스킬소모량"))
		{
			if (enemy.GetFlag("턴스킬대기시간") - enemy.GetFlag("턴대기") >= 3)
				Guard(enemy, chara);
			else
				UseEpSkill(enemy, chara);
		}
		else
		{
			if (enemy.GetFlag("현재체력") <= enemy.GetFlag("최대체력") / 3.5)
				Guard(enemy, chara);
			else
				Attack(enemy, chara);
		}
	}
}

void HSI_Turn(Character& enemy, Character& chara)
{
	enemy.AddFlag("현재체력", enemy.GetFlag("최대체력"));
	enemy.AddFlag("최대체력", enemy.GetFlag("최대체력"));
	enemy.AddFlag("현재기력", enemy.GetFlag("최대기력"));
	enemy.AddFlag("최대기력", enemy.GetFlag("최대기력"));
	enemy.AddFlag("공격력", enemy.GetFlag("공격력"));
	enemy.AddFlag("방어력", enemy.GetFlag("방어력"));
	enemy.SetFlag("턴스킬대기시간", 100);

	cout << "Target Captured.. Body Sensor.." << endl;
	Wait;

	cout << enemy.Name.WithPP("는") << " 메탈화 하였다!" << endl;
	Wait;
}

void HSI_EP(Character& enemy, Character& chara)
{
	double damageMultiple = 3.5;
	GetDamage(chara, enemy, damageMultiple * enemy.GetFlag("공격력"));

	cout << enemy.Name.WithPP("의") << " 입 속에서 불이 뿜어져 나와 " << chara.Name.WithPP("을") << " 덮쳤다" << endl;
	Wait;

	cout << chara.Name.WithPP("은") << " " << -chara.GetFlag("체력변화") << " 의 데미지를 입었다" << endl;
	Wait;
}

void HSI_Passive(passive timing, Character& chara, Character& enemy)
{
	int hpRecover = enemy.GetFlag("최대체력") * 0.075;

	if (timing == EnemyTurnEnd)
		enemy.AddFlag("현재체력", hpRecover);
	else if (timing == Interface)
	{
		cout << "                              ";
		cout << enemy.Name.WithPP("의") << " 체력이 " << hpRecover << "만큼 회복";
	}
}
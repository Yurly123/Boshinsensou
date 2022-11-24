#include "System.h"

void KMR_Load()
{
	Enemy::TurnSkillList["KMR"] = KMR_Turn;
	Enemy::EpSkillList["KMR"] = KMR_EP;
	Enemy::PassiveSkillList["KMR"] = KMR_Passive;
	Enemy::EnemyAIList["KMR"] = KMR_AI;
}

void KMR_AI(Enemy& enemy, Character& chara)
{
	if (enemy.GetFlag("턴대기") >= enemy.GetFlag("턴스킬대기시간"))
		UseTurnSkill(enemy, chara);
	else
	{
		if (enemy.GetFlag("현재기력") >= enemy.GetFlag("기력스킬소모량"))
		{
			if (enemy.GetFlag("최대체력") - enemy.GetFlag("현재체력") >= enemy.GetFlag("기력스킬소모량"))
				UseEpSkill(enemy, chara);
		}
		else
			Attack(enemy, chara);
	}
}

void KMR_Turn(Character& enemy, Character& chara)
{
	enemy.AddFlag("공격력", 15);
	enemy.AddFlag("방어력", 5);
	enemy.AddFlag("현재체력", 30);
	enemy.AddFlag("최대체력", 30);
	enemy.AddFlag("현재기력", 15);
	enemy.AddFlag("최대기력", 15);

	cout << enemy.Name.WithPP("는") << " 각성하여 자신의 능력을 일깨웠다" << endl;
	Wait;

	cout << enemy.Name.WithPP("의") << " 능력치가 여러 방면으로 상승했다" << endl;
	Wait;
}

void KMR_EP(Character& enemy, Character& chara)
{
	enemy.AddFlag("현재체력", enemy.GetFlag("기력스킬소모량"));

	cout << enemy.Name.WithPP("는") << " 잠시 생각을 하더니, 체력을 창조해냈다" << endl;
	Wait;

	cout << enemy.Name.WithPP("의") << " 체력이 " << enemy.GetFlag("기력변화") << "만큼 회복 되었다." << endl;
	Wait;

}

void KMR_Passive(passive timing, Character& chara, Character& enemy)
{
	if (timing == DoneAttack)
	{
		int amount = 2;
		enemy.AddFlag("공격력", amount);
	}
}
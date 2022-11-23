#include "System.h"

void KBS_Load()
{
	Enemy::TurnSkillList["KBS트리오"] = KBS_Turn;
	Enemy::EpSkillList["KBS트리오"] = KBS_EP;
	Enemy::PassiveSkillList["KBS트리오"] = KBS_Passive;
	Enemy::EnemyAIList["KBS트리오"] = KBS_AI;
}

void KBS_AI(Enemy& enemy, Character& chara)
{
	switch (Local::Get("턴") % 3)
	{
	case 0:	// K!
		Attack(enemy, chara);
		break;
	case 1:	// B!
		if (enemy.GetFlag("현재기력") >= enemy.GetFlag("기력스킬소모량"))
			UseEpSkill(enemy, chara);
		else
			Attack(enemy, chara);
		break;
	case 2:	// S!
		if (enemy.GetFlag("턴대기") >= enemy.GetFlag("턴스킬대기시간"))
			UseTurnSkill(enemy, chara);
		else
			Attack(enemy, chara);
		break;
	}
}

void KBS_Turn(Character& enemy, Character& chara)
{
	double recoverMultiple = 0.1;
	enemy.AddFlag("현재체력", enemy.GetFlag("최대체력") * recoverMultiple);
	enemy.AddFlag("현재기력", enemy.GetFlag("최대기력") * recoverMultiple);

	cout << enemy.Name.WithPP("는") << " 이번 턴에는 지원에 집중한다" << endl;
	Wait;

	cout << enemy.Name.WithPP("의") << " 체력이 " << enemy.GetFlag("체력변화") << "만큼," << endl;
	cout << "기력이 " << enemy.GetFlag("기력변화") << "만큼 회복되었다" << endl;
	Wait;
}

void KBS_EP(Character& enemy, Character& chara)
{
	double defenseMultiple = 2.0;
	enemy.AddFlag("방어력", enemy.GetFlag("방어력") * defenseMultiple);

	cout << enemy.Name.WithPP("는") << " 이번 턴에는 방어에 집중한다" << endl;
	Wait;

	cout << enemy.Name.WithPP("의") << " 방어력이 " << enemy.GetFlag("방어력") << "이 되었다" << endl;
	Wait;
}

void KBS_Passive(passive timing, Character& enemy, Character& chara)
{
	if (timing == BeforeInput)
		enemy.SetFlag("방어력", enemy.GetFlag("방어력") / 3.0);
}
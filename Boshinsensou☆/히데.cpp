#include "System.h"

void 히데_Load()
{
	Enemy::TurnSkillList["히데"] = 히데_Turn;
	Enemy::EpSkillList["히데"] = 히데_EP;
	Enemy::PassiveSkillList["히데"] = 히데_Passive;
	Enemy::EnemyAIList["히데"] = 히데_AI;
}

void 히데_AI(Enemy& enemy, Character& chara)
{
	if (enemy.GetFlag("현재기력") >= enemy.GetFlag("기력스킬소모량")
		&& chara.GetFlag("현재기력") >= chara.GetFlag("최대기력") * 0.5)
		UseEpSkill(enemy, chara);
	else
		Attack(enemy, chara);
}

void 히데_Turn(Character&, Character&)
{

}

void 히데_EP(Character& enemy, Character& chara)
{
	int epDecrease = chara.GetFlag("최대기력") * 0.25;
	ConsumeEp(chara, enemy, epDecrease);

	cout << enemy.Name.WithPP("는") << " 크게 비명을 질러서 " << chara.Name.WithPP("의") << " 집중력을 떨어뜨렸다" << endl;
	Wait;

	cout << chara.Name.WithPP("의") << " 기력이 " << -chara.GetFlag("기력변화") << "만큼 감소했다" << endl;
	Wait;
}

void 히데_Passive(passive, Character&, Character&)
{

}
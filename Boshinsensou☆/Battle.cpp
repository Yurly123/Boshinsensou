#include "System.h"

#pragma region 전역 함수

void Battle(Character& currentChara)
{
	PrintLine();
	cout << endl << "전장으로 진입합니다." << endl;
	Wait;

	int progression = Local::Get("진행도");
	Enemy currentEnemy = Enemy::EnemyList[progression];

	while (true)
	{
		PrintLine();
		cout << endl;

		vector<int> inputLIst;
		PrintBattleMap(progression);

		cout << endl;
		PrintLine();
		cout << endl;

		string space = "    ";
		AddInput(inputLIst, 100, "전투 개시", space);
		AddInput(inputLIst, 101, "아군 정보", space);
		AddInput(inputLIst, 102, "적의 정보", space);
		AddInput(inputLIst, 999, "나가기", space);
		cout << endl;

		int input = GetInput(inputLIst);
		if (input == 999) break;
		switch (input)
		{
		case 100:	// 전투 개시
			BattleLoop(currentChara, currentEnemy);
			Local::Set("턴", 0);
			Character::PassiveSkillList[currentChara.Name](EndOfBattle, currentChara, currentEnemy);
			ProgressTime();
			return;
		case 101:	// 아군 정보
			ShowCharaInfo(currentChara);
			break;
		case 102:	// 적의 정보
			ShowCharaInfo(currentEnemy);
			break;
		case 999:	// 나가기
			return;
		}
	}
	Wait;
}

void PrintBattleMap(int index)
{
	switch (index)
	{
	case 0:
		//printf("-------------------------------------------------------------------------------------------------\n");
		printf("     <마을>                                                                                      \n");
		printf("                                                                                                 \n");
		printf("                                                                                                 \n");
		printf("                                                                                                 \n");
		printf("			  %s 히데                                                                            \n", (index == 0 ? "▶" : "  "));
		printf("                                                                                                 \n");
		printf("                                                                                                 \n");

		break;
	}
}

bool isGuarding = false;
bool isEPGuarding = false;

void BattleLoop(Character& chara, Enemy& enemy)
{
	Local::Set("턴", 0);
	chara.SetFlag("턴대기", 0);
	enemy.SetFlag("턴대기", 0);

	PrintLine();
	cout << endl << "전투를 시작합니다." << endl;
	Wait;

	while (true)
	{
		Character::PassiveSkillList[chara.Name](TurnStart, chara, enemy);

		if (enemy.GetFlag("현재체력") <= 0)
		{
			Win(chara, enemy);
			return;
		}

		PrintBattleInterface(chara, enemy, Character::PassiveSkillList[chara.Name]);

		// 입력 커맨드들
		string space = "    ";
		vector<int> inputList;
		// 턴 소모 하는 커맨드
		AddInput(inputList, 0, "공격", space);
		AddInput(inputList, 1, "방어", space);

		if (chara.GetFlag("턴대기") < chara.GetFlag("턴스킬대기시간")) SetColor(8);
		AddInput(inputList, 10, chara.GetStr("턴스킬"), space);
		cout << " " << chara.GetFlag("턴대기") << "/" << chara.GetFlag("턴스킬대기시간");
		SetColor(7);

		if (chara.GetFlag("현재기력") >= chara.GetFlag("기력스킬소모량")) SetColor(9);
		else SetColor(8);
		AddInput(inputList, 11, chara.GetStr("기력스킬"), space);
		cout << " " << chara.GetFlag("기력스킬소모량") << "EP";
		SetColor(7);

		AddInput(inputList, 999, "도망가기", space);
		cout << endl;

		PrintLine();
		// 턴 소모 하지 않는 커맨드
		if (isEPGuarding) SetColor(9);
		else SetColor(8);
		AddInput(inputList, 20, "기력 방어", space);
		if (isEPGuarding) cout << " ON";
		else cout << " OFF";
		SetColor(7);
		AddInput(inputList, 101, "아군 정보", space);
		AddInput(inputList, 102, "적의 정보", space);
		cout << endl;

		Character::PassiveSkillList[chara.Name](BeforeInput, chara, enemy);
		cout << endl;
		int input = GetInput(inputList);

		switch (input)
		{
		case 0:	// 공격
			Attack(chara, enemy);
			ChangeTurn(chara, enemy);
			break;
		case 1:	// 방어
			Guard(chara, enemy);
			ChangeTurn(chara, enemy);
			break;
		case 10:	// 턴스킬
			if (chara.GetFlag("턴대기") >= chara.GetFlag("턴스킬대기시간"))
			{
				UseTurnSkill(chara, enemy);
				ChangeTurn(chara, enemy);
			}
			else
			{
				cout << endl << "턴 대기중 입니다." << endl;
				Wait;
			}
			break;
		case 11:	// 기력스킬
			if (chara.GetFlag("현재기력") >= chara.GetFlag("기력스킬소모량"))
			{
				UseEpSkill(chara, enemy);
				ChangeTurn(chara, enemy);
			}
			else
			{
				cout << endl << "기력이 부족합니다." << endl;
				Wait;
			}
			break;
		case 20:
			isEPGuarding = !isEPGuarding;
			break;
		case 101:	// 아군 정보
			ShowCharaInfo(chara);
			break;
		case 102:	// 적의 정보
			ShowCharaInfo(enemy);
			break;
		case 999:	// 도망가기
			if (Run(chara, enemy)) return;
			break;
		}
	}
}

void ChangeTurn(Character& chara, Enemy& enemy)
{
	PrintLine();
	cout << endl;
	PrintHpEpChange(enemy);
	cout << endl;
	PrintHpEpChange(chara);
	Wait;

	if (chara.GetFlag("현재체력") <= 0)
		CharaDeath(chara);
	if (enemy.GetFlag("현재체력") <= 0)
		return;
	Character::PassiveSkillList[chara.Name](TurnEnd, chara, enemy);

	PrintLine();
	cout << endl << enemy.Name.WithPP("의") << " 턴" << endl << endl;
	PrintLine();
	Wait;

	PrintBattleInterface(chara, enemy, Enemy::PassiveSkillList[enemy.Name]);
	Wait;

	PrintLine();
	Enemy::EnemyAIList[enemy.Name](enemy, chara);

	PrintLine();
	cout << endl;
	PrintHpEpChange(enemy);
	cout << endl;
	PrintHpEpChange(chara);
	Wait;

	if (chara.GetFlag("현재체력") <= 0)
		CharaDeath(chara);
	if (enemy.GetFlag("현재체력") <= 0)
		return;

	PrintLine();
	cout << endl << chara.Name.WithPP("의") << " 턴" << endl << endl;
	PrintLine();
	Wait;

	Local::Add("턴", 1);
	if (chara.GetFlag("턴대기") < chara.GetFlag("턴스킬대기시간"))
		chara.AddFlag("턴대기", 1);
	if (enemy.GetFlag("턴대기") < enemy.GetFlag("턴스킬대기시간"))
		enemy.AddFlag("턴대기", 1);
}

void UseTurnSkill(Character& chara, Character& opponent)
{
	cout << endl << chara.GetStr("턴스킬") << endl;
	Wait;
	Character::TurnSkillList[chara.Name](chara, opponent);
	chara.SetFlag("턴대기", -1);
}
void UseEpSkill(Character& chara, Character& opponent)
{
	ConsumeEp(chara, opponent, chara.GetFlag("기력스킬소모량"));
	cout << endl << chara.GetStr("기력스킬") << endl;
	Wait;
	Character::EpSkillList[chara.Name](chara, opponent);
}

void Attack(Character& attacker, Character& defender)
{
	int damage = attacker.GetFlag("공격력");
	int epRecover = attacker.GetFlag("최대기력") * 0.1;
	cout << endl << attacker.Name.WithPP("의") << " 공격" << endl;
	Wait;

	GetDamage(defender, attacker, damage);
	attacker.AddFlag("현재기력", epRecover);
	if (!attacker.GetTalent("적"))
		Character::PassiveSkillList[attacker.Name](DoneAttack, attacker, defender);
	else
		Character::PassiveSkillList[defender.Name](GotAttack, defender, attacker);

	cout << defender.Name.WithPP("에게") << " " << -defender.GetFlag("체력변화") << "의 데미지" << endl;
	Wait;
	cout << attacker.Name.WithPP("의") << " 기력이 " << attacker.GetFlag("기력변화") << "만큼 회복" << endl;
	Wait;
}
void Guard(Character& defender, Character& opponent)
{
	isGuarding = true;
	cout << endl << defender.Name.WithPP("는") << " 이번 턴, 방어에 전념하기로 했다" << endl;
	Wait;
}

void ConsumeEp(Character& chara, Character& opponent, int amount)
{
	chara.AddFlag("현재기력", -amount);
	if (!chara.GetTalent("적"))
		Character::PassiveSkillList[chara.Name](MyEpConsume, chara, opponent);
	else
		Character::PassiveSkillList[opponent.Name](EnemyEpConsume, opponent, chara);
}
void GetDamage(Character& chara, Character& opponent, int amount)
{
	amount -= amount * (chara.GetFlag("방어력") / 100.0);

	if (opponent.GetTalent("적"))
	{
		if (isGuarding) amount /= 2.0;
		if (isEPGuarding)
		{
			amount /= 2.0;
			chara.AddFlag("현재기력", -amount);
			if (chara.GetFlag("현재기력") < 0) chara.SetFlag("현재기력", 0);
		}
	}

	chara.AddFlag("현재체력", -amount);

	if (!chara.GetTalent("적"))
		Character::PassiveSkillList[chara.Name](MyHpDamage, chara, opponent);
	else
		Character::PassiveSkillList[opponent.Name](EnemyHpDamage, opponent, chara);
}

bool Run(Character& chara, Enemy& enemy)
{
	double chance = 1.0 / 2.0;

	cout << endl;
	cout << "도망가기는 " << chance * 100 << "% 확률로 성공할 수 있습니다." << endl;
	cout << "실패할 경우, 체력 차감등의 패널티가 적용 될 수 있습니다." << endl;
	cout << endl << "도망가시겠습니까?" << endl;
	cout << endl << "[0] 도망가기" << endl << "[1] 아니요" << endl;

	if (GetInput({ 0,1 })) return false;

	cout << chara.Name.WithPP("는") << " 이 전투에서 벗어나기로 했다" << endl;
	Wait;

	if (Random(chance))
	{
		cout << "다행히도 별 탈 없이 도망치는 데에 성공했다" << endl;
		Wait;
		return true;
	}
	else
	{
		cout << "하지만 얼마안가 " << enemy.Name.WithPP("에게") << " 뒤따라 잡히고 말았다.." << endl;
		Wait;

		chara.AddFlag("현재기력", -chara.GetFlag("최대기력") / 3.0);
		if (chara.GetFlag("현재기력") < 0) chara.SetFlag("현재기력", 0);

		chara.AddFlag("현재체력", -chara.GetFlag("최대체력") / 5.0);
		if (chara.GetFlag("현재체력") < 1) chara.SetFlag("현재체력", 1);

		ChangeTurn(chara, enemy);
		return false;
	}
}
void Win(Character& chara, Enemy& enemy)
{
	cout << chara.Name.WithPP("는") << " " << enemy.Name.WithPP("를") << " 쓰러뜨렸다!" << endl;
	Wait;

	cout << enemy.Name.WithPP("와") << "의 전투에서 승리 하였습니다" << endl;
	Wait;

	Local::Add("진행도", 1);
}

void PrintBattleInterface(Character& chara, Enemy& enemy, void (*passive)(passive, Character&, Character&))
{
	PrintLine();
	PrintHpBar(enemy); cout << endl;
	PrintEpBar(enemy); cout << endl;
	SetColor(7);
	cout << endl << "                                        " << enemy.Name << endl;

	cout << endl;
	// 상태 표시
	passive(Interface, chara, enemy);
	cout << endl;

	cout << endl << "                                        " << chara.Name << endl;
	PrintHpBar(chara); cout << endl;
	PrintEpBar(chara); cout << endl;
	SetColor(7);

	PrintLine();
}

void PrintHpEpChange(Character& chara)
{
	if (chara.GetFlag("체력변화") || chara.GetFlag("기력변화"))
	{
		int hp = chara.GetFlag("현재체력");
		int ep = chara.GetFlag("현재기력");

		cout << "  " << chara.Name << endl;
		if (chara.GetFlag("체력변화"))
			cout << "체력 : " << hp - chara.GetFlag("체력변화") << " → " << hp << endl;
		if (chara.GetFlag("기력변화"))
			cout << "기력 : " << ep - chara.GetFlag("기력변화") << " → " << ep << endl;

		chara.SetFlag("체력변화", 0);
		chara.SetFlag("기력변화", 0);
	}
}

void PrintHpBar(Character& chara)
{
	double ratio = (double)chara.GetFlag("현재체력") / (double)chara.GetFlag("최대체력");
	int color;
	if (ratio > 2.0 / 3.0) color = 10;
	else if (ratio > 1.0 / 3.0) color = 6;
	else color = 4;

	SetColor(color);
	cout << "   ";
	for (int i = 0; i < 75; ++i)
	{
		ratio -= 1.0 / 75.0;
		if (ratio <= 0) SetColor(14);
		cout << "■";
	}

	SetColor(color);
	cout << " ";
	cout << setw(4) << chara.GetFlag("현재체력") << " / ";
	cout << setw(4) << chara.GetFlag("최대체력") << " HP";
}
void PrintEpBar(Character& chara)
{
	double ratio = (double)chara.GetFlag("현재기력") / (double)chara.GetFlag("최대기력");

	SetColor(9);
	cout << "   ";
	for (int i = 0; i < 75; ++i)
	{
		ratio -= 1.0 / 75.0;
		if (ratio <= 0) SetColor(8);
		cout << "■";
	}

	if (chara.GetFlag("현재기력") > 0) SetColor(9);
	else SetColor(8);
	cout << " ";
	cout << setw(4) << chara.GetFlag("현재기력") << " / ";
	cout << setw(4) << chara.GetFlag("최대기력") << " EP";
}

#pragma endregion
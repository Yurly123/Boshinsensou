#include "Battle.h"

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

	default:
		//printf("-------------------------------------------------------------------------------------------------\n");
		printf("     <Error Map>                                                                                 \n");
		printf("                                                                                                 \n");
		printf("awiteg87fh98ajiudbjh,vnoij8u9ap29iOPKWEFNFMLROPW;IAJLHKRKHTJIKOPRLKhlafjiwo;ekflmndfbl[peewokjifa\n");
		printf("3h7r9iwojsdfn mkdsiowdjlhbe,jdkfopsefjuhnkerpodfjihbew,njkweopdfjwelpfsdkojidewm,klodfkjiwemkldif\n");
		printf("nby2fg8hawejiofzkmowI09ALHUSYKBRNJOIX90FJDULJno8gnujseamkirodbgnjsmkoiawe09xfjilkmweoix;gkelrowfe\n");
		printf("fewnhzju8ij;oamkllfwexdbjiunrem5t43koerxkdfjimn34kiexr9puej4na23kowezi9xeru8zwi9a23jonejifpuefwha\n");
		printf("hweafjuizrena3kwfopxrjine43mkwefopixerj.4ewkfrceqxwefiswrmjekopferwmzfkdjiowekfisodefkdiseijoiedj\n");
		printf("                                                                                                 \n");
		printf("index : %d\n", index);
		break;
	}
}

void BattleLoop(Character& chara, Enemy& enemy)
{
	Local::Set("턴", 0);
	chara.SetFlag("턴대기", 0);

	PrintLine();
	cout << endl << "전투를 시작합니다." << endl;
	Wait;

	while (true)
	{
		PrintBattleInterface(chara, enemy, Character::PassiveSkillList[chara.Name]);

		// 입력 커맨드들
		string space = "    ";
		vector<int> inputList;
		// 턴 소모 하는 커맨드
		AddInput(inputList, 0, "공격", space);

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
		AddInput(inputList, 101, "아군 정보", space);
		AddInput(inputList, 102, "적의 정보", space);
		cout << endl;

		cout << endl;
		int input = GetInput(inputList);


		switch (input)
		{
		case 0:	// 공격
			Attack(chara, enemy);
			ChangeTurn(chara, enemy);
			break;
		case 10:	// 턴스킬
			if (chara.GetFlag("턴대기") >= chara.GetFlag("턴스킬대기시간"))
			{
				cout << endl << chara.GetStr("턴스킬") << endl;
				Wait;
				Character::TurnSkillList[chara.Name](chara, enemy);
				ChangeTurn(chara, enemy);
				chara.SetFlag("턴대기", 0);
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
				ConsumeEp(chara, enemy, chara.GetFlag("기력스킬소모량"));
				cout << endl << chara.GetStr("기력스킬") << endl;
				Wait;
				Character::EpSkillList[chara.Name](chara, enemy);
				ChangeTurn(chara, enemy);
			}
			else
			{
				cout << endl << "기력이 부족합니다." << endl;
				Wait;
			}
			break;
		case 999:	// 도망가기
			Run(chara, enemy);
			return;
		case 101:	// 아군 정보
			ShowCharaInfo(chara);
			break;
		case 102:	// 적의 정보
			ShowCharaInfo(enemy);
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

	PrintLine();
	cout << endl << chara.Name.WithPP("의") << " 턴" << endl << endl;
	PrintLine();
	Wait;

	Local::Add("턴", 1);
	if (chara.GetFlag("턴대기") < chara.GetFlag("턴스킬대기시간"))
		chara.AddFlag("턴대기", 1);
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

void Attack(Character& attacker, Character& defender)
{
	int damage = 1000;
	int epRecover = attacker.GetFlag("최대기력") * 0.05;
	cout << endl << attacker.Name.WithPP("의") << " 공격" << endl;
	Wait;

	GetDamage(defender, attacker, damage);
	attacker.AddFlag("현재기력", epRecover);
	if (!attacker.GetTalent("적"))
		Character::PassiveSkillList[attacker.Name](DoneAttack, attacker, defender);
	else
		Character::PassiveSkillList[defender.Name](GotAttack, defender, attacker);

	cout << defender.Name.WithPP("에게") << " " << damage << "의 데미지" << endl;
	Wait;
	cout << attacker.Name.WithPP("의") << " 기력이 " << epRecover << "만큼 회복" << endl;
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
	chara.AddFlag("현재체력", -amount);
	if (!chara.GetTalent("적"))
		Character::PassiveSkillList[chara.Name](MyHpDamage, chara, opponent);
	else
		Character::PassiveSkillList[opponent.Name](EnemyHpDamage, opponent, chara);
}

void Run(Character& chara, Enemy& enemy)
{
	cout << endl << chara.Name.WithPP("는") << " 이 전투에서 벗어나기로 했다." << endl;
	Wait;
}

#pragma endregion
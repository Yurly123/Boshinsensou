#include "Battle.h"

#pragma region 전역 함수

void Battle(Character& currentChara)
{
	PrintLine();
	cout << endl << "전장으로 진입합니다." << endl;
	Wait;
	
	BattleMap(currentChara);

	Wait;
}

void BattleMap(Character& currentChara)
{
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
		switch (input)
		{
		case 100:	// 전투 개시
			BattleLoop(currentChara, currentEnemy);
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
}

void BattleLoop(Character& battleChara, Enemy& enemy)
{
	PrintLine();
	cout << endl << "전투를 시작합니다." << endl;
	Wait;
	while (true)
	{
		PrintLine();
		PrintHpBar(enemy); cout << endl;
		PrintEpBar(enemy); cout << endl;
		SetColor(7);
		cout << endl << "                                        " << enemy.Name << endl;

		cout << endl;
		// 상태 표시
		cout << endl;
		
		cout << endl << "                                        " << battleChara.Name << endl;
		PrintHpBar(battleChara); cout << endl;
		PrintEpBar(battleChara); cout << endl;
		SetColor(7);

		PrintLine();
		// 입력 커맨드들
		string space = "    ";
		vector<int> inputList;
		// 턴 소모 하는 커맨드
		AddInput(inputList, 0, "공격", space);
		AddInput(inputList, 999, "도망가기", space);
		cout << endl;

		PrintLine();
		// 턴 소모 하지 않는 커맨드
		AddInput(inputList, 101, "아군 정보", space);
		AddInput(inputList, 102, "적의 정보", space);
		cout << endl;

		cout << endl;
		int input = GetInput(inputList);

		enemy.SetFlag("체력변화", 0); battleChara.SetFlag("체력변화", 0);
		enemy.SetFlag("기력변화", 0); battleChara.SetFlag("기력변화", 0);
		switch (input)
		{
		case 0:	// 공격
			Attack(battleChara, enemy);
			ChangeTurn(battleChara, enemy);
			break;
		case 999:	// 도망가기
			return;
		case 101:	// 아군 정보
			ShowCharaInfo(battleChara);
			break;
		case 102:	// 적의 정보
			ShowCharaInfo(enemy);
			break;
		}
	}

	// 도망가기 처리
}

void ChangeTurn(Character& battleChara, Enemy& enemy)
{
	PrintLine();
	cout << endl;

	if (enemy.GetFlag("현재기력") < enemy.GetFlag("최대기력"))
		enemy.AddFlag("현재기력", 5);
	if (battleChara.GetFlag("현재기력") < battleChara.GetFlag("최대기력"))
		battleChara.AddFlag("현재기력", 5);

	if (enemy.GetFlag("체력변화") || battleChara.GetFlag("기력변화"))
	{
		int hp = enemy.GetFlag("현재체력");
		int ep = enemy.GetFlag("현재기력");

		cout << "  " << enemy.Name << endl;
		if (enemy.GetFlag("체력변화"))
			cout << "체력 : " << hp - enemy.GetFlag("체력변화") << " → " << hp << endl;
		if (enemy.GetFlag("기력변화"))
			cout << "기력 : " << ep - enemy.GetFlag("기력변화") << " → " << ep << endl;
	}
	cout << endl;

	if (battleChara.GetFlag("체력변화") || battleChara.GetFlag("기력변화"))
	{
		int hp = battleChara.GetFlag("현재체력");
		int ep = battleChara.GetFlag("현재기력");

		cout << "  " << battleChara.Name << endl;
		if (battleChara.GetFlag("체력변화"))
			cout << "체력 : " << hp - battleChara.GetFlag("체력변화") << " → " << hp << endl;
		if (battleChara.GetFlag("기력변화"))
			cout << "기력 : " << ep - battleChara.GetFlag("기력변화") << " → " << ep << endl;
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
	int damage = 10;
	int epRecover = attacker.GetFlag("최대기력") * 0.05;
	cout << endl << attacker.Name.WithPP("의") << " 공격!" << endl;
	Wait;

	GetDamage(defender, damage);
	cout << defender.Name.WithPP("에게") << " " << damage << " 만큼의 데미지!" << endl;
	Wait;

	ConsumeEp(attacker, -epRecover);
	cout << attacker.Name.WithPP("의") << " 기력이 " << epRecover << " 만큼 회복" << endl;
	Wait;
}

void ConsumeEp(Character& chara, int amount)
{
	chara.AddFlag("현재기력", -amount);
}
void GetDamage(Character& chara, int amount)
{
	chara.AddFlag("현재체력", -amount);
}

#pragma endregion
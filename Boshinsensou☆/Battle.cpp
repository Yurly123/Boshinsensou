#include "Battle.h"

#pragma region 전역 함수

void Battle(vector<Character>& ownCharaList)
{
	PrintLine();
	cout << endl << "전장으로 진입합니다." << endl;
	Wait;
	
	BattleMap(ownCharaList);
}

void BattleMap(vector<Character>& ownCharaList)
{
	while (true)
	{
		PrintLine();
		cout << endl;

		vector<int> inputLIst;
		PrintMap(Enemy::Progression);

		cout << endl;
		PrintLine();
		cout << endl;

		string space = "    ";
		AddInput(inputLIst, 100, "전투 개시", space);
		AddInput(inputLIst, 101, "아군 정보", space);
		AddInput(inputLIst, 200, "적의 정보", space);
		AddInput(inputLIst, 999, "나가기", space);
		cout << endl;

		int input = GetInput(inputLIst);
		if (input == 999) break;
		else switch (input)
		{
		case 100:
			Fight(ownCharaList, Enemy::EnemyList[Enemy::Progression]);
			break;
		case 101:
			while (true)
			{
				cout << endl << "정보를 보고싶은 캐릭터를 고르십시오" << endl << endl;
				Character selectChara = SelectCharactor(ownCharaList);	// 캐릭터 받기
				if (selectChara.ID == -1) break;	// 무효값이면 반복 종료
				ShowCharaInfo(selectChara);	// 캐릭터 정보 표시
			}
			break;
		case 200:
			ShowEnemyInfo(Enemy::EnemyList[Enemy::Progression]);
			break;
		}
	}
}

void PrintMap(int index)
{
	switch (index)
	{
	case 0:
	  //printf("-------------------------------------------------------------------------------------------------\n");
		printf("     <마을>                                                                                      \n");
		printf("                                                                                                 \n");
		printf("                                                                                                 \n");
		printf("                                                                                                 \n");
		printf("           %s 히데                                                                               \n", (index == 0 ? "▶" : "  "));
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

void Fight(vector<Character>& ownCharaList, Enemy& enemy)
{
	PrintLine();
	Wait;
	PrintLine();
}

#pragma endregion
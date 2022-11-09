#include "Battle.h"

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
		PrintMap(0, inputLIst, 0);

		cout << endl;
		PrintLine();
		cout << endl;

		string space = "    ";
		AddInput(inputLIst, 100, "전투 개시", space);
		AddInput(inputLIst, 101, "적의 정보", space);
		AddInput(inputLIst, 999, "나가기", space);
		cout << endl;

		int Input = GetInput(inputLIst);
		if (Input == 999) break;
	}
}


void PrintMap(int index, vector<int>& inputList, int select)
{
	switch (index)
	{
	case 0:
	  //printf("-------------------------------------------------------------------------------------------------\n");
		printf("     <마을>                                                                                      \n");
		printf("                                                                                                 \n");
		printf("                                                                                                 \n");
		printf("                                                                                                 \n");
		printf("           %3s 히데                                                                              \n", (select == 0 ? " ▶" : "[0]")); if (select != 0) inputList.push_back(0);
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
		printf("selection : %d\n", select);
		break;
	}
}
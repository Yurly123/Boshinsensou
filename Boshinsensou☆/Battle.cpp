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

		cout << "   - Map -" << endl;

		cout << endl;
		PrintLine();
		cout << endl;

		vector<int> InputLIst;
		string space = "    ";
		AddInput(InputLIst, 100, "전투 개시", space);
		AddInput(InputLIst, 101, "적의 정보", space);
		AddInput(InputLIst, 999, "나가기", space);
		cout << endl;

		int Input = GetInput(InputLIst);
		if (Input == 999) break;
	}
}
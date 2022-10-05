#include "com999.h"

void Loadcom999()
{
	Command::ComList.emplace(make_pair(999, Command()));
	Command::ComList[999].ID = 999;
	Command::ComList[999].Name = "훈련 종료";
	Command::ComList[999].Commit = Command999;
}

void Command999(Charactor& chara)
{
	cout << chara.Name.Text << "의 훈련을 마칩니다." << endl;
	Wait;
}
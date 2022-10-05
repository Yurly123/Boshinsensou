#include "com000.h"

void Loadcom000()
{
	Command::ComList.emplace(make_pair(0, Command()));
	Command::ComList[0].ID = 0;
	Command::ComList[0].Name = "스트레칭";
	Command::ComList[0].Commit = Command000;
}

void Command000(Charactor& chara)
{
	cout << "당신은 " << chara.Name.WithPP("과") << " 몸풀기 겸 스트레칭을 하기로 했다" << endl;
	Wait;
}
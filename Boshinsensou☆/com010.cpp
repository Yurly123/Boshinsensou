#include "com010.h"

void Loadcom010()
{
	Command::ComList.emplace(make_pair(10, Command()));
	Command::ComList[10].ID = 10;
	Command::ComList[10].Name = "샌드백 치기";
	Command::ComList[10].Commit = Command010;
}

void Command010(Character& chara, map<int, int>& param)
{
	cout << chara.Name.WithPP("는") << " 있는 힘껏 샌드백을 쳤다" << endl;
	param[Parameter::GetParam("의욕")] += 30;
	param[Parameter::GetParam("유산소")] += 15;
	AbstractEP(chara, 5);
	chara.AddCflag("현재체력", -5);
}
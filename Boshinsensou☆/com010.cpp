#include "com010.h"

void Loadcom010()
{
	Command::ComList.emplace(make_pair(10, Command()));
	Command::ComList[10].ID = 10;
	Command::ComList[10].Name = "샌드백 치기";
	Command::ComList[10].Commit = Command010;
}

void Command010(Charactor& chara, vector<int>& param)
{
	cout << chara.Name.WithPP("는") << " 샌드백을 친다" << endl;
	param[Parameter::GetParam("의욕")] += 15;
	AbstractEP(chara, 10);
	chara.AddCflag("현재체력", -10);
}
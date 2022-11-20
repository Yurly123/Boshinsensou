#include "com010.h"

void Loadcom010()
{
	Command::ComList[10] = Command(10, "샌드백 치기", Command010);
}

void Command010(Character& chara, map<int, int>& param)
{
	cout << chara.Name.WithPP("는") << " 있는 힘껏 샌드백을 쳤다" << endl;
	param[Parameter::Get("의욕")] += 30;
	param[Parameter::Get("유산소")] += 15;
	AbstractEP(chara, 5);
	chara.AddFlag("현재체력", -5);
}
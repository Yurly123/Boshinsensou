#include "com009.h"

void Loadcom009()
{
	Command::ComList[9] = Command(9, "뜀뛰기", Command009);
}

void Command009(Character& chara, map<int, int>& param)
{
	cout << chara.Name.WithPP("와") << " 함께 뛰기로 했다" << endl;
	param[Parameter::Get("의욕")] += 20;
	param[Parameter::Get("유산소")] += 40;
	AbstractEP(chara, 15);
}
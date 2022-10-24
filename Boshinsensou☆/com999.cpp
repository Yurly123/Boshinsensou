#include "com999.h"

void Loadcom999()
{
	Command::ComList[999] = Command(999, "훈련 종료", Command999);
}

void Command999(Character& chara, map<int, int>& param)
{
	cout << chara.Name << "의 훈련을 마칩니다." << endl;
}
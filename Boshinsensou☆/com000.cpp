#include "System.h"

void Loadcom000()
{
	Command::ComList[0] = Command(0, "스트레칭", Command000);
}

void Command000(Character& chara, map<int, int>& param)
{
	cout << "당신은 " << chara.Name.WithPP("와") << " 몸풀기 겸 스트레칭을 하기로 했다" << endl;
	Wait;
	cout << chara.Name.WithPP("는") << " 스트레칭으로 몸이 ";
	switch (rand() % 3)
	{
	case 0:
		cout << "잘 풀리지 않은것 같다..";
		param[Parameter::Get("피로")] -= 30;
		param[Parameter::Get("의욕")] += 10;
		break;
	case 1:
		cout << "그럭저럭 풀린것 같다.";
		param[Parameter::Get("피로")] -= 60;
		param[Parameter::Get("의욕")] += 20;
		break;
	case 2:
		cout << "잘 풀린것 같다.";
		param[Parameter::Get("피로")] -= 90;
		param[Parameter::Get("의욕")] += 30;
		break;
	}
	param[Parameter::Get("유산소")] += 5;
	AbstractEP(chara, 5);
}
#include "System.h"

void Initialize()
{
	system("mode con cols=100 lines=50");
	CData::LoadCDatas();
	Charactor::LoadCharaList();
	Command::LoadCommands();
}

int main()
{
	Initialize();
	Shop();
}
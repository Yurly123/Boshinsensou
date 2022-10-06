#include "System.h"

void Initialize()
{
	system("mode con cols=100 lines=50");
	srand((unsigned int)time(NULL));
	cout << "Loading CDatas..." << endl;
	CData::LoadCDatas();
	cout << "Loading Charactors..." << endl;
	Charactor::LoadCharaList();
	cout << "Loading Commands..." << endl;
	Command::LoadCommands();

	for (int i = 0; i < 100; ++i)
		cout << endl;
}

int main()
{
	Initialize();
	Shop();
}
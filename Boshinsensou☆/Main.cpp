#include "System.h"

void Initialize()
{
	SetConsoleTitle(TEXT("Boshinsensou☆"));
	system("mode con cols=100 lines=50");
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), { 100,250 });
	srand((unsigned int)time(NULL));

	SetColor(7);
	cout << "Loading CDatas..." << endl;
	CData::LoadCDatas();
	cout << "Loading Charactors..." << endl;
	Charactor::LoadCharaList();
	cout << "Loading Commands..." << endl;
	Command::LoadCommands();
	cout << "Loading Parameters..." << endl;
	Parameter::LoadParam();

	for (int i = 0; i < 100; ++i)
		cout << endl;
}

int main()
{
	Initialize();
	Shop();
}
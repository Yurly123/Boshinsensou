#include "Train.h"

void Train(Charactor TrainChara)
{
	PrintLine();
	cout << endl;
	Wait;

	TrainLoop(TrainChara);
	
	cout << endl;
	PrintLine();
	Wait;
}

void TrainLoop(Charactor TrainChara)
{
	while (true)
	{
		PrintLine();
		cout << endl;
		cout << "\t[200] ���� (�ӽ�)\t[999] �Ʒ�����" << endl;
		cout << endl;
		PrintLine();
		int Command = GetInput({ 200,999 });

		if (Command == 999) break;
		switch (Command)
		{
		case 200:
			ofstream OutStream("SAV\\01.sav");
			OutStream << "Hello World!" << endl;
			break;
		}
	}
}
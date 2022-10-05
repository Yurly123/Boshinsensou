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
		cout << "\t[999] 훈련종료" << endl;
		cout << endl;
		PrintLine();
		int Command = GetInput({ 999 });

		if (Command == 999) break;
		switch (Command)
		{

		}
	}
}
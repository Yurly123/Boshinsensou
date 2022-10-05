#include "Train.h"

void Train(Charactor& TrainChara)
{
	PrintLine();
	cout << endl << "훈련을 시작합니다." << endl;
	Wait;

	TrainLoop(TrainChara);
	
	PrintLine();
}

void TrainLoop(Charactor& TrainChara)
{
	while (true)
	{
		PrintLine();
		cout << endl;
		cout << "   " << TrainChara.Cstr[CData::GetStr("이름")] << endl;
		cout << "   체력 " << TrainChara.Cflag[CData::GetFlag("현재체력")]
			<< " / " << TrainChara.Cflag[CData::GetFlag("최대체력")] << endl;
		cout << endl;
		PrintLine();
		cout << endl;

		vector<int> inputList;
		for (auto& com : Command::ComList)
		{
			cout << "   [" << com.first << "] " << com.second.Name;
			inputList.push_back(com.first);
		}
		cout << endl << endl;
		PrintLine();

		int selectCom = GetInput(inputList);

		cout << endl << Command::ComList[selectCom].Name << endl << endl;
		Command::ComList[selectCom].Commit(TrainChara);

		if (selectCom == 999) break;
	}
}
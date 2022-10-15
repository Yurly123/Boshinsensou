#include "Train.h"

void Train(Charactor& TrainChara)
{
	PrintLine();
	cout << endl << "훈련을 시작합니다." << endl;
	Wait;

	TrainLoop(TrainChara);
	
	for (auto& chara : Charactor::CharaList)
	{
		if (chara.ID == TrainChara.ID)
		{
			chara = TrainChara;
			break;
		}
	}
}

void TrainLoop(Charactor& TrainChara)
{
	vector<int> parameter(Parameter::Param_Length);
	while (true)
	{
		PrintLine();
		cout << endl;
		cout << "   " << TrainChara.GetCstr("이름") << endl;
		PrintCharaHPEP(TrainChara);
		cout << endl;

		for (int i = 0; i < Parameter::Param_Length; ++i)
		{
			cout << "   " << Parameter::GetParam(i) << " " << parameter[i];
		}
		cout << endl << endl;
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

		vector<int> temp(parameter);
		int hp = TrainChara.GetCflag("현재체력");
		int ep = TrainChara.GetCflag("현재기력");
		Command::ComList[selectCom].Commit(TrainChara, parameter);
		if (selectCom == 999) break;
		cout << endl;
		Wait;
		
		cout << endl;
		if (TrainChara.GetCflag("현재체력") != hp)
			cout << "체력 : " << hp << " → " << TrainChara.GetCflag("현재체력") << endl;
		if (TrainChara.GetCflag("현재기력") != ep)
			cout << "기력 : " << ep << " → " << TrainChara.GetCflag("현재기력") << endl;
		cout << endl;
		for (int i = 0; i < Parameter::Param_Length; ++i)
		{
			if (parameter[i] != temp[i])
			{
				parameter[i] += (parameter[i] - temp[i]) * 1.1f;
				cout << Parameter::GetParam(i) << " : " << temp[i] << " → " << parameter[i] << endl;
			}
		}

		if (TrainChara.GetCflag("현재체력") <= 20)
		{
			cout << endl << "**" << TrainChara.Name.WithPP("가") << " 너무 지쳤으므로 훈련을 종료합니다**" << endl;
			Wait;
			break;
		}

		Wait;
	}
}
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
	map<int, int> parameter;
	for (auto& param : Parameter::ParamList)
	{
		parameter.emplace(make_pair(param.first, 0));
	}

	while (true)
	{
		PrintLine();
		cout << endl;
		cout << "   " << TrainChara.GetCstr("이름") << endl;
		PrintCharaHPEP(TrainChara);
		cout << endl;

		for (auto& param : Parameter::ParamList)
		{
			cout << "   " << param.second << " " << parameter[param.first];
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

		map<int, int> temp(parameter);
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

		for (auto& param : Parameter::ParamList)
		{
			if (parameter[param.first] != temp[param.first])
			{
				parameter[param.first] += (parameter[param.first] - temp[param.first]) * 1.1f;
				cout << param.second << " : " << temp[param.first] << " → " << parameter[param.first] << endl;
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
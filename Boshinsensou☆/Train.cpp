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
		cout << "\t" << TrainChara.GetCstr("이름") << endl;
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

		for (auto& param : Parameter::ParamList)
		{
			if (parameter[param.first] != temp[param.first])
			{
				if (param.second == "유산소" || param.second == "무산소")
					parameter[Parameter::GetParam("피로")] += (parameter[param.first] - temp[param.first]) / 2;

				if (param.second != "피로" && param.second != "의욕")
					parameter[param.first] += (parameter[param.first] - temp[param.first]) * parameter[Parameter::GetParam("의욕")] / 100;
			}

			if (parameter[param.first] < 0)
				parameter[param.first] = 0;
		}
		if (TrainChara.GetCflag("현재체력") != hp)
			TrainChara.AddCflag("현재체력", -(hp - TrainChara.GetCflag("현재체력")) * parameter[Parameter::GetParam("피로")] / 200);
		if (TrainChara.GetCflag("현재기력") != ep)
			TrainChara.AddCflag("현재기력", -(ep - TrainChara.GetCflag("현재기력")) * parameter[Parameter::GetParam("피로")] / 200);

		cout << endl;
		Wait;
		
		if (TrainChara.GetCflag("현재체력") != hp)
			cout << "체력 : " << hp << " → " << TrainChara.GetCflag("현재체력") << endl;
		if (TrainChara.GetCflag("현재기력") != ep)
			cout << "기력 : " << ep << " → " << TrainChara.GetCflag("현재기력") << endl;
		cout << endl;

		for (auto& param : Parameter::ParamList)
		{
			if (parameter[param.first] != temp[param.first])
			{
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
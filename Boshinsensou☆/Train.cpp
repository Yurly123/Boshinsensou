#include "Train.h"

void Train(Character& TrainChara)
{
	PrintLine();
	cout << endl << "훈련을 시작합니다." << endl;
	Wait;

	map<int, int> parameter = TrainLoop(TrainChara);
	Wait;

	PrintLine();
	cout << endl << "얻은 포인트 : " << endl;
	cout << endl;
	for (auto& param : Parameter::ParamList)
	{
		if (parameter[param.first] > 0)
			cout << " - " << param.second << " : " << parameter[param.first] << endl;
		else
			parameter[param.first] = 0;
	}
	Wait;

	if (parameter[Parameter::GetParam("피로")] > 0)
	{
		cout << "피로도 " << parameter[Parameter::GetParam("피로")] << "에서 감소한 포인트 : " << endl;
		cout << endl;
		for (auto& param : Parameter::ParamList)
		{
			if (param.second != "피로")
			{
				parameter[param.first] -= parameter[Parameter::GetParam("피로")];

				if (parameter[param.first] > 0)
					cout << " - " << param.second << " : " << parameter[param.first] << endl;
				else
					parameter[param.first] = 0;
			}
		}
		Wait;
	}

	ImproveCharaStat(TrainChara, parameter);
}

map<int, int> TrainLoop(Character& TrainChara)
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
			AddInput(inputList, com.first, com.second.Name, "   ");
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
		if (TrainChara.GetCflag("현재기력") < 0)
			TrainChara.SetCflag("현재기력", 0);

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
			break;
		}

		Wait;
	}

	for (auto& chara : Character::CharaList)
	{
		if (chara.ID == TrainChara.ID)
		{
			chara = TrainChara;
			break;
		}
	}
	return parameter;
}

void ImproveCharaStat(Character& chara, map<int, int>& parameter)
{
	while (true)
	{
		PrintLine();
		cout << endl;

		for (auto& param : Parameter::ParamList)
		{
			if (param.second != "피로")
				cout << "   " << param.second << " : " << parameter[param.first];
		}
		cout << endl << endl;
		PrintLine();
		cout << endl;

		cout << "  상승시킬 능력을 골라주세요." << endl << endl;

		vector<int> inputList;
		for (auto& flag : CData::CFlagList)
		{
			if (20 <= flag.first && flag.first < 30)
			{
				bool isSatisfied;
				StatRequirement(flag.first - 20, chara, parameter, isSatisfied);
				if (!isSatisfied) SetColor(8);
				AddInput(inputList, flag.first - 20,
					flag.second + " " + to_string(chara.Cflag[flag.first] + 1) + "\n",
					"   ");
				SetColor(7);
			}
		}
		AddInput(inputList, 100, "능력상승 종료\n", "   ");

		cout << endl;
		PrintLine();
		int input = GetInput(inputList);
		if (input == 100) break;
		UpCStat(chara, parameter, input);
	}
}

void UpCStat(Character& chara, map<int, int>& parameter, int index)
{
	bool isSatisfied;
	map<int, int> require = StatRequirement(index, chara, parameter, isSatisfied);
	while (true)
	{
		PrintLine();
		cout << endl;

		cout << "   [0] " << CData::GetFlag(index + 20) << chara.Cflag[index + 20] + 1;
		for (auto& req : require)
		{
			cout << "\t" << Parameter::GetParam(req.first) << " 포인트 " << req.second;
		}
		cout << " 필요" << endl;
		cout << "   [1] 돌아가기" << endl;

		cout << endl;

		if (GetInput({ 0,1 })) break;
		else
		{
			if (isSatisfied)
			{
				for (auto& req : require)
					parameter[req.first] -= req.second;
				++chara.Cflag[index + 20];
				return;
			}
			else
			{
				cout << endl << "포인트가 부족합니다." << endl;
				Wait;
				return;
			}
		}
	}
}

map<int, int> StatRequirement(int index, Character& chara, map<int, int>& parameter, bool& isSatisfied)
{
	map<int, int> require;

	switch (index)
	{
	case 0: // 지구력
		require[Parameter::GetParam("유산소")] = 500 * (chara.GetCflag("지구력") + 1);
		break;
	case 1: // 근력
		require[Parameter::GetParam("무산소")] = 500 * (chara.GetCflag("근력") + 1);
		break;
	}

	for (auto& req : require)
	{
		if (parameter[req.first] <= req.second)
		{
			isSatisfied = false;
			return require;
		}
	}

	isSatisfied = true;
	return require;
}
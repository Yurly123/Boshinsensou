#include "Character.h"

vector<Character> Character::CharaList = vector<Character>();

void Character::LoadCData()
{
	string filepath = "CSV\\Chara\\";
	filepath.append(to_string(ID));
	filepath.append(" ");
	filepath.append(Name);
	filepath.append(".csv");
	LoadDefaultCData(filepath, *this);
}
int Character::GetCflag(string name)
{
	return Cflag[CData::GetFlag(name)];
}
bool Character::GetCtalent(string name)
{
	return Ctalent[CData::GetTalent(name)];
}
string Character::GetCstr(string name)
{
	return Cstr[CData::GetStr(name)];
}
void Character::SetCflag(string name, int value)
{
	Cflag[CData::GetFlag(name)] = value;
}
void Character::SetCtalent(string name, bool value)
{
	Ctalent[CData::GetTalent(name)] = value;
}
void Character::SetCstr(string name, string value)
{
	Cstr[CData::GetStr(name)] = value;
}
void Character::AddCflag(string name, int value)
{
	Cflag[CData::GetFlag(name)] += value;
}
void Character::LoadCharaList()
{
	ifstream FileStream("CSV\\Character.csv");
	while (!FileStream.eof())
	{
		string Buffer;

		getline(FileStream, Buffer, ',');
		int id = stoi(Buffer);

		getline(FileStream, Buffer, ',');
		string name = Buffer;

		getline(FileStream, Buffer);
		bool IsAlt = Buffer == "true";

		Character chara = Character(name, IsAlt, id);
		CharaList.push_back(chara);
	}
	FileStream.close();
}
Character::Character(string name, bool IsAlt, int ID)
{
	this->Name = ::Name(name, IsAlt);
	this->ID = ID;
	Cflag = map<int, int>();
	Ctalent = map<int, bool>();
	Cstr = map<int, string>();
	LoadCData();
}

Name::Name(string text, bool isalt)
{
	Text = text;
	IsAlt = isalt;
}
string Name::GetPP(string PP)
{
	//original 는 가 를 로   와 나   로서   로써
	//alternat 은 이 을 으로 과 이나 으로서 으로써
	if (IsAlt)
	{
		if (PP == "는") PP = "은";
		else if (PP == "가") PP = "이";
		else if (PP == "를") PP = "을";
		else if (PP == "로") PP = "으로";
		else if (PP == "와") PP = "과";
		else if (PP == "나") PP = "이나";
		else if (PP == "로서") PP = "으로서";
		else if (PP == "로써") PP = "으로써";
	}
	else
	{
		if (PP == "은") PP = "는";
		else if (PP == "이") PP = "가";
		else if (PP == "을") PP = "를";
		else if (PP == "으로") PP = "로";
		else if (PP == "과") PP = "와";
		else if (PP == "이나") PP = "나";
		else if (PP == "으로서") PP = "로서";
		else if (PP == "으로써") PP = "로써";
	}
	return PP;
}
string Name::WithPP(string PP)
{
	string text = Text;
	return text.append(GetPP(PP));
}
string GetCharaDescription(Character& chara)
{
	string Description;
	switch (chara.ID)
	{
	case 1:
		Description.append("쿠키☆의 초창기 멤버로써, 인터넷에서 평생동안 떠드는 누님이다. 별명은 마리나\n");
		Description.append("RU누님과 사이가 좋다, 하지만 서로는 싫지는 않지만 좋아하지도 않다는 애매한 관계라고 얼버무린다.\n");
		Description.append("UDK누님은 특히나 목소리가 인기가 많아서 많은 팬을 거느린다고 한다.\n");
		Description.append("쿠키☆를 호모들로부터 지키기 위해 기꺼히 이 전쟁의 중심에서 활약하고 있다.\n");
		Description.append("좋아하는 음식은 토로로소바.\n");
		break;
	case 2:
		Description.append("쿠키☆의 시작을 연 초창기 멤버로써, 살이 조금 찐게 매력적인 누님이다.\n");
		Description.append("UDK누님과 사이가 좋다, 하지만 서로는 싫지는 않지만 좋아하지도 않다는 애매한 관계라고 얼버무린다.\n");
		Description.append("차를 마시면서 \"푸하! 오늘도 좋은 날씨☆\" 라고 말하는 특이한 습관을 가졌다.\n");
		Description.append("이번 전쟁에서 본인의 숨겨진 전투력으로 큰 성과를 이룰것으로 기대된다.\n");
		Description.append("옛날에 RU누님의 유전자를 무와 결합한 생명체가 개발되었다 한다.\n");
		break;
	case 3:
		Description.append("쿠키☆ 초대의 두번째 실질적 주인공인 ALC역을 맡고 있는 누님이다.\n");
		Description.append("항상 웃는 얼굴로 남들을 대하며 좌절한 동료에게 격려를 잘 해주기까지도 하는 성우의 귀감이다.\n");
		Description.append("평소에는 얌전한 성격이지만, 한번 화가 나면 친한 UDK에게 밭다리 후리기를 걸 정도로 폭력적이게 변한다.\n");;
		Description.append("HNS의 팔에서 뻗어나오는 거대한 일체형 낫은 HNS의 전투력을 매우 큰 폭으로 상승시킬 것으로 보인다.\n");
		Description.append("은근한 변태적인 면모가 있다고 한다.\n");
		break;
	case 4:
		Description.append("쿠키☆1기를 포함한 여러 작품에서 SIK역을 맡고 있는 누님이다.\n");
		Description.append("전쟁이 벌어지기 전부터 음몽에 대한 관심이 높아, 스스로 관장까지 하는 적극성을 보여주었다.\n");
		Description.append("하지만 전쟁이 벌어지자 쿠키☆의 편에 붙으며 성우의 본분을 잊지 않는 모습을 보여주었다.\n");
		Description.append("KNN누님에게 검술을 전수 받았으며, 淫夢之一太刀[음몽지일태도] 라는 전용검을 다룰 수 있다.\n");
		Description.append("실은 적장인 야수선배의 여동생이라는 속설이 떠돌고 있다.\n");
		break;
	default:
		Description.append("ERROR 누님\n\n");
		Description.append("쿠키☆0기에 출연 신청을 했지만 1:114514의 경쟁률을 뚫지 못하고 결국 떨어지게 되었다.\n");
		Description.append("그후 COAT사의 호모비디오에도 출연 신청을 했으나 이 또한 1:110약의 경쟁률을 뚫지 못하고 떨어졌다.\n");
		Description.append("쿠키☆와 음몽 모두에게 버려진 그녀는 결국 어디에도 속하지 못하고 이 사태에 휘말리게 되었다.\n");
		Description.append("하지만 그녀는 지금도 게임에 출연하지 못하고 데이터 상으로만 존재하게 되었다.\n");
		Description.append("슬프구나.. (제행무상)\n");
		break;
	}
	return Description;
}

void PrintCharaHPEP(Character& chara)
{
	double ratio = (double)chara.GetCflag("현재체력") / (double)chara.GetCflag("최대체력");
	if (ratio > 2.0 / 3.0) SetColor(10);
	else if (ratio > 1.0 / 3.0) SetColor(6);
	else SetColor(4);
	cout << "   체력 " << chara.GetCflag("현재체력") << " / " << chara.GetCflag("최대체력");

	if (chara.GetCflag("현재기력") > 0) SetColor(9);
	else SetColor(8);
	cout << "   기력 " << chara.GetCflag("현재기력") << " / " << chara.GetCflag("최대기력");
	SetColor(7);
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
				cout << "   [ " << flag.first - 20 << "] " << flag.second << chara.Cflag[flag.first] + 1 << endl;
				inputList.push_back(flag.first - 20);
			}
		}
		cout << endl << "   [100] 능력상승 종료" << endl;
		inputList.push_back(100);

		cout << endl;
		PrintLine();
		int input = GetInput(inputList);
		if (input == 100) break;
		UpCStat(chara, parameter, input);
	}
}

void UpCStat(Character& chara, map<int, int>& parameter, int index)
{
	while (true)
	{
		PrintLine();
		cout << endl;
		
		cout << "   [0] " << CData::GetFlag(index + 20) << chara.Cflag[index + 20] + 1;
		switch (index)
		{
		case 0:	// 지구력
			cout << "\t유산소 포인트 500 필요";
			break;
		case 1:	// 근력
			cout << "\t무산소 포인트 500 필요";
			break;
		}
		cout << endl;
		cout << "   [1] 돌아가기" << endl;

		cout << endl;

		if (GetInput({ 0,1 })) break;
		else
		{
			try
			{
				switch (index)
				{
				case 0:	// 지구력
					if (parameter[Parameter::GetParam("유산소")] < 500)
						throw 0;
					else
					{
						parameter[Parameter::GetParam("유산소")] -= 500;
						++chara.Cflag[CData::GetFlag("지구력")];
						return;
					}
					break;
				case 1:	// 근력
					if (parameter[Parameter::GetParam("무산소")] < 500)
						throw 0;
					else
					{
						parameter[Parameter::GetParam("유산소")] -= 500;
						++chara.Cflag[CData::GetFlag("근력")];
						return;
					}
					break;
				}
			}
			catch (int type)
			{
				cout << endl;
				if (type == 0)
					cout << "포인트가 부족합니다." << endl;

				Wait;
				return;
			}
		}
	}
}
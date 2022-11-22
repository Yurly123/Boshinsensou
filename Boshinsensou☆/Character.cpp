#include "Character.h"

#pragma region 클래스 멤버

#pragma region Character
vector<Character> Character::CharaList = vector<Character>();
map<string, void (*)(Character&, Character&)> Character::TurnSkillList = map<string, void (*)(Character&, Character&)>();
map<string, void (*)(Character&, Character&)> Character::EpSkillList = map<string, void (*)(Character&, Character&)>();
map<string, void (*)(passive, Character&, Character&)> Character::PassiveSkillList = map<string, void (*)(passive, Character&, Character&)>();

void Character::InitChara()
{
	string filepath = "CSV\\Chara\\";
	filepath.append(to_string(ID));
	filepath.append(" ");
	filepath.append(Name);
	filepath.append(".csv");
	LoadDefaultCData(filepath, *this);
}
int Character::GetFlag(string name)
{
	return Cflag[CData::Flag(name)];
}
bool Character::GetTalent(string name)
{
	return Ctalent[CData::Talent(name)];
}
string Character::GetStr(string name)
{
	return Cstr[CData::Str(name)];
}
void Character::SetFlag(string name, int value)
{
	if (name == "현재체력") AddFlag("체력변화", value - Cflag[CData::Flag(name)]);
	if (name == "현재기력") AddFlag("기력변화", value - Cflag[CData::Flag(name)]);
	Cflag[CData::Flag(name)] = value;
}
void Character::SetTalent(string name, bool value)
{
	Ctalent[CData::Talent(name)] = value;
}
void Character::SetStr(string name, string value)
{
	Cstr[CData::Str(name)] = value;
}
void Character::AddFlag(string name, int value)
{
	SetFlag(name, Cflag[CData::Flag(name)] + value);
}
void Character::LoadCharaList()
{
	ifstream FileStream("CSV\\Character.csv");
	while (!FileStream.eof())
	{
		string buffer;

		getline(FileStream, buffer, ',');
		int id = stoi(buffer);

		getline(FileStream, buffer, ',');
		string name = buffer;

		getline(FileStream, buffer);
		bool IsAlt = buffer == "true";

		Character chara = Character(name, IsAlt, id);
		if (!chara.GetTalent("적"))
			CharaList.push_back(chara);
		else
			Enemy::EnemyList.push_back(chara);
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
	InitChara();
}
void Character::LoadSkillList()
{
	UDK_Load();
	히데_Load();
}
#pragma endregion

#pragma region Name
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
#pragma endregion

#pragma endregion

#pragma region 전역 함수

string GetCharaDescription(int id)
{
	string description;
	switch (id)
	{
	case 1:
		description += "쿠키☆의 초창기 멤버로써, 인터넷에서 평생동안 떠드는 누님이다. 별명은 마리나\n";
		description += "RU누님과 사이가 좋다, 하지만 서로는 싫지는 않지만 좋아하지도 않다는 애매한 관계라고 얼버무린다.\n";
		description += "UDK누님은 특히나 목소리가 인기가 많아서 많은 팬을 거느린다고 한다.\n";
		description += "쿠키☆를 호모들로부터 지키기 위해 기꺼히 이 전쟁의 중심에서 활약하고 있다.\n";
		description += "좋아하는 음식은 토로로소바.\n";
		break;
	case 2:
		description += "쿠키☆의 시작을 연 초창기 멤버로써, 살이 조금 찐게 매력적인 누님이다.\n";
		description += "UDK누님과 사이가 좋다, 하지만 서로는 싫지는 않지만 좋아하지도 않다는 애매한 관계라고 얼버무린다.\n";
		description += "차를 마시면서 \"푸하! 오늘도 좋은 날씨☆\" 라고 말하는 특이한 습관을 가졌다.\n";
		description += "이번 전쟁에서 본인의 숨겨진 전투력으로 큰 성과를 이룰것으로 기대된다.\n";
		description += "옛날에 RU누님의 유전자를 무와 결합한 생명체가 개발되었다 한다.\n";
		break;
	case 3:
		description += "쿠키☆ 초대의 두번째 실질적 주인공인 ALC역을 맡고 있는 누님이다.\n";
		description += "항상 웃는 얼굴로 남들을 대하며 좌절한 동료에게 격려를 잘 해주기까지도 하는 성우의 귀감이다.\n";
		description += "평소에는 얌전한 성격이지만, 한번 화가 나면 친한 UDK에게 밭다리 후리기를 걸 정도로 폭력적이게 변한다.\n";
		description += "HNS의 팔에서 뻗어나오는 거대한 일체형 낫은 HNS의 전투력을 매우 큰 폭으로 상승시킬 것으로 보인다.\n";
		description += "은근한 변태적인 면모가 있다고 한다.\n";
		break;
	case 4:
		description += "쿠키☆1기를 포함한 여러 작품에서 SIK역을 맡고 있는 누님이다.\n";
		description += "전쟁이 벌어지기 전부터 음몽에 대한 관심이 높아, 스스로 관장까지 하는 적극성을 보여주었다.\n";
		description += "하지만 전쟁이 벌어지자 쿠키☆의 편에 붙으며 성우의 본분을 잊지 않는 모습을 보여주었다.\n";
		description += "KNN누님에게 검술을 전수 받았으며, 淫夢之一太刀[음몽지일태도] 라는 전용검을 다룰 수 있다.\n";
		description += "실은 적장인 야수선배의 여동생이라는 속설이 떠돌고 있다.\n";
		break;
	default:
		description += "쿠키☆0기에 출연 신청을 했지만 1:114514의 경쟁률을 뚫지 못하고 결국 떨어지게 되었다.\n";
		description += "그후 COAT사의 호모비디오에도 출연 신청을 했으나 이 또한 1:110약의 경쟁률을 뚫지 못하고 떨어졌다.\n";
		description += "쿠키☆와 음몽 모두에게 버려진 그녀는 결국 어디에도 속하지 못하고 이 사태에 휘말리게 되었다.\n";
		description += "하지만 그녀는 지금도 게임에 출연하지 못하고 데이터 상으로만 존재하게 되었다.\n";
		description += "슬프구나.. (제행무상)\n";
		break;
	}
	return description;
}

void PrintCharaHPEP(Character& chara)
{
	double ratio = (double)chara.GetFlag("현재체력") / (double)chara.GetFlag("최대체력");
	if (ratio > 2.0 / 3.0) SetColor(10);
	else if (ratio > 1.0 / 3.0) SetColor(6);
	else SetColor(4);
	cout << "   체력 " << chara.GetFlag("현재체력") << " / " << chara.GetFlag("최대체력");

	if (chara.GetFlag("현재기력") > 0) SetColor(9);
	else SetColor(8);
	cout << "   기력 " << chara.GetFlag("현재기력") << " / " << chara.GetFlag("최대기력");
	SetColor(7);
}

void ShowCharaInfo(Character& chara)
{
	int index = 0;
	while (true)
	{
		cout << endl;
		PrintLine();
		cout << endl;

		switch (index)
		{
		case 0:
		{
			// 소질 표시
			cout << "  소질 : ";
			for (auto& talent : CData::CTalentList)
			{
				if (talent.first == 0) continue;
				if (chara.Ctalent[talent.first])
					cout << "[" << talent.second << "] ";
			}
			cout << endl << endl;

			PrintLine();
			cout << endl;

			// 이름 표시
			cout << "   -" << chara.ID << "-\t" << chara.Name << "   ";
			PrintCharaHPEP(chara);
			cout << endl << endl;

			// 능력 표시
			cout << "  능력 : " << endl;
			for (auto& flag : CData::CFlagList)
			{
				if (20 <= flag.first && flag.first < 30)
				{
					cout << "   " << flag.second << " : " << chara.Cflag[flag.first];
				}
			}
			cout << endl << endl;
		} break;
		case 1:
		{
			// 이름 표시
			cout << endl << " " << chara.GetStr("이름") << endl;

			// 캐릭터 설명 표시
			cout << endl << GetCharaDescription(chara.ID) << endl;
		} break;
		}

		PrintLine();
		vector<int> inputList;
		cout << endl;
		if (index > 0)
			AddInput(inputList, 101, "이전 페이지", "\t");
		else
			cout << "\t\t";
		AddInput(inputList, 1000, "돌아가기", "\t");
		if (index < 1)
			AddInput(inputList, 109, "다음 페이지", "\t");
		cout << endl;

		int input = GetInput(inputList);

		if (input == 1000) break;
		else if (input == 101) --index;
		else if (input == 109) ++index;
	}
}

#pragma endregion
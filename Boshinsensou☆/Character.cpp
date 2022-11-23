#include "System.h"

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

		getline(FileStream, buffer, ',');
		bool IsAlt = buffer == "true";

		Character chara = Character(name, IsAlt, id);
		if (!chara.GetTalent("적"))
			CharaList.push_back(chara);
		else
			Enemy::EnemyList.push_back(chara);

		getline(FileStream, buffer);
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
	TurnSkillList[name] = [](Character&, Character&) {};
	EpSkillList[name] = [](Character&, Character&) {};
	PassiveSkillList[name] = [](passive, Character&, Character&) {};
	InitChara();
}
void Character::LoadSkillList()
{
	YMN_Load();
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

string GetCharaDescription(string name)
{
	string description;
	if (name == "YMN")
	{
		description += "보신전쟁의 주인공\n";
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
					cout << "   " << flag.second << ":" << chara.Cflag[flag.first];
				}
			}
			cout << endl << endl;
		} break;
		case 1:
		{
			cout << "  보유 스킬 : ";

			cout << "[" << chara.GetStr("턴스킬") << "]:" << chara.GetFlag("턴스킬대기시간") << "턴 ";
			cout << "[" << chara.GetStr("기력스킬") << "]:" << chara.GetFlag("기력스킬소모량") << "EP ";
			cout << "[" << chara.GetStr("패시브스킬") << "]:패시브" << endl;

			cout << endl;
			PrintLine();

			// 이름 표시
			cout << endl << " " << chara.GetStr("이름") << endl;

			// 캐릭터 설명 표시
			cout << endl << GetCharaDescription(chara.Name) << endl;
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

void CharaDeath(Character& chara)
{
	Wait;

	cout << ".";
	Wait;

	cout << "..";
	Wait;

	cout << "...";
	Wait;

	if (chara.GetTalent("이어지는의지"))
	{
		chara.SetTalent("이어지는의지", false);
		chara.SetFlag("현재체력", chara.GetFlag("최대체력"));
		chara.SetFlag("현재기력", 0);
		
		cout << "!";
		Wait;

		cout << endl << chara.Name.WithPP("은") << " 죽음 속에서 살아 돌아왔다!" << endl;
		Wait;

		cout << "*이어지는의지가 일시 소멸했습니다*" << endl;
		Wait;
		return;
	}

	cout << chara.Name.WithPP("는") << " 명을 다했습니다.." << endl;
	Wait;

	while (true)
	{
		vector<int> inputList;
		string space = "   ";
		cout << endl << "어떻게 하시겠습니까?" << endl << endl;
		AddInput(inputList, 0, "로드하기", space);
		AddInput(inputList, 1, "타이틀로", space);
		AddInput(inputList, 2, "게임 종료", space);
		if (chara.ID != 0) AddInput(inputList, 3, "무시하고 진행", space);
		cout << endl << endl;
		int input = GetInput(inputList);

		string exitCode;
		switch (input)
		{
		case 0:
		{
			Character temp;
			ShopLoad(&temp);
			if (temp.ID == -1)
				break;

			exitCode = "Load";
			throw exitCode;
		}
		case 1:
			cout << endl;
			cout << "정말로 타이틀로 돌아 가시겠습니까?" << endl;
			cout << "[0] 예" << endl;
			cout << "[1] 아니요" << endl << endl;
			if (!GetInput({ 0,1 }))
			{
				exitCode = "Title";
				throw exitCode;
			}
			break;
		case 2:
			cout << endl;
			cout << "정말로 종료 하시겠습니까?" << endl;
			cout << "[0] 예" << endl;
			cout << "[1] 아니요" << endl << endl;
			if (!GetInput({ 0,1 }))
				exit(0);
			break;
		case 3:
			cout << endl;
			cout << "정말로 무시하고 진행 하시겠습니까?" << endl;
			cout << chara.Name.WithPP("는");
			SetColor(4);
			cout << " 다시 돌아오지 못합니다" << endl;
			cout << "[0] 예" << endl;
			SetColor(7);
			cout << "[1] 아니요" << endl << endl;

			if (!GetInput({ 0,1 }))
			{
				chara.SetTalent("사망", true);
				Character::CharaList[Local::Get("선택 캐릭터")] = chara;
				cout << "***" << chara.Name.WithPP("는") << " 저세상으로 사라졌습니다***" << endl;
				Wait;
				exitCode = "Death";
				throw exitCode;
			}
			break;
		}

	}
}

#pragma endregion
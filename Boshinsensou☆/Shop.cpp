#include "Shop.h"

#pragma region 전역 함수

void Shop()
{
	Local::Set("선택 캐릭터", 0);

	// 반복
	while (true)
	{
		Character currentChara = Character::CharaList[Local::Get("선택 캐릭터")];
		int currentTime = Local::Get("현재 시간");

		cout << endl;
		PrintLine();
		cout << endl;

		// Shop 정보 출력
		if (currentTime % 2) SetColor(9);
		else SetColor(14);
		cout << "\t" << currentTime / 2 + 1 << "일째 " << (currentTime % 2 ? "밤" : "낮") << endl;	// 밤낮일수
		SetColor(7);
		cout << "\t- " << currentChara.Name << " - " << endl;	// 캐릭터 이름
		PrintCharaHPEP(currentChara);	// 체력 기력
		cout << endl;

		cout << endl;
		PrintLine();
		cout << endl;

		//	Shop 커맨드 출력
		vector<int> inputList;
		string space = "    ";
		AddInput(inputList, 100, "훈련하기", space);
		AddInput(inputList, 101, "캐릭터 정보", space);
		AddInput(inputList, 109, "캐릭터 변경", space);
		AddInput(inputList, 200, "저장하기", space);
		AddInput(inputList, 300, "불러오기", space);
		AddInput(inputList, 500, "전장으로", space);
		AddInput(inputList, 999, "게임 종료", space);
		inputList.push_back(114514);
		cout << endl;

		cout << endl;
		PrintLine();

		try
		{
			// Shop 커맨드 입력 받기
			int Input = GetInput(inputList);
			cout << endl;
			switch (Input)
			{
			case 100:	// 훈련
				Train(currentChara);
				ProgressTime();
				break;

			case 101:	// 캐릭터 정보 확인
				while (true)
				{
					cout << "정보를 보고싶은 캐릭터를 고르십시오" << endl << endl;
					Character selectChara = SelectCharactor(Character::CharaList);	// 캐릭터 받기
					if (selectChara.ID == -1) break;	// 무효값이면 반복 종료
					ShowCharaInfo(selectChara);	// 캐릭터 정보 표시
				}
				break;

			case 109:	// 캐릭터 변경
				ShopCharaChange(&currentChara);
				break;

			case 200:	// 저장
				ShopSave();
				break;

			case 300:	// 불러오기
				ShopLoad(&currentChara);
				break;

			case 500:	// 전투
				Battle(currentChara);
				break;

			case 999:	// 게임종료
				cout << "정말로 종료 하시겠습니까?" << endl;
				cout << "[0] 예" << endl;
				cout << "[1] 아니요" << endl << endl;
				if (!GetInput({ 0,1 }))
					exit(0);
				break;

			case 114514:	// ???
				for (int i = 0; i < 114514; ++i)
					cout << "GO IS GOD";
				Restart();
				break;
			}
		}
		catch (string code)
		{
			if (code == "Death")
			{
				while (true)
				{
					ShopCharaChange(&currentChara);

					if (!currentChara.GetTalent("사망"))
						break;
					else
					{
						cout << endl <<"돌아갈 수 있었으면 진작에 돌아갔겠지" << endl;
						Wait;
					}
				}
			}
			else if (code == "Load")
			{
				currentChara = Character::CharaList[Local::Get("선택 캐릭터")];
			}
			else throw code;
		}

		Character::CharaList[Local::Get("선택 캐릭터")] = currentChara;
	}
}

void ProgressTime()
{
	Local::Add("현재 시간", 1);	// 시간 가감

	// 캐릭터들 체력/기력 회복
	for (auto& chara : Character::CharaList)
	{
		int maxHp = chara.GetFlag("최대체력");
		int maxEp = chara.GetFlag("최대기력");
		chara.AddFlag("현재체력", maxHp * 0.25);
		chara.AddFlag("현재기력", maxEp * 0.375);
		// 최대치 넘은값 평탄화
		if (chara.GetFlag("현재체력") > maxHp)
			chara.SetFlag("현재체력", maxHp);
		if (chara.GetFlag("현재기력") > maxEp)
			chara.SetFlag("현재기력", maxEp);

		if (chara.ID == 0)
			chara.SetTalent("이어지는의지", true);
	}

	AutoSave();
	GlobalLoad();

	PrintLine();
	cout << endl;
	// 밤낮 표시
	if (Local::Get("현재 시간") % 2)
		cout << "밤이 되었습니다." << endl;
	else
		cout << "아침이 밝았습니다." << endl;
	Wait;
	PrintLine();
}

Character SelectCharactor(vector<Character>& charaList)
{
	PrintLine();
	cout << endl;

	vector<int> IDList;	// 입력 받을 캐릭터(ID) 리스트

	for (Character& chara : charaList)
	{
		if (chara.GetTalent("보유중") && !chara.GetTalent("사망"))
		{
			// 캐릭터 정보 간략히 표시
			cout << "  [" << setw(2) << chara.ID << "] " << chara.Name << "\t";
			PrintCharaHPEP(chara);
			cout << endl;
			IDList.push_back(chara.ID);
		}
	}
	cout << endl;
	PrintLine();

	cout << endl;
	AddInput(IDList, 1000, "돌아가기", "     ");
	cout << endl;

	int SelectID = GetInput(IDList);	// 입력 받기
	if (SelectID == 1000) return Character();	// 돌아가기면 무효값 반환

	// 캐릭터 찾아서 반환
	for (Character& chara : charaList)
	{
		if (chara.ID == SelectID) return chara;
	}

	return Character();	// 맞는거 없으면 무효값 반환
}

void ShopCharaChange(Character* currentChara)
{
	while (true)
	{
		cout << endl << "선택하려는 캐릭터를 고르십시오" << endl << endl;
		Character selectChara = SelectCharactor(Character::CharaList);	// 캐릭터 받기
		if (selectChara.ID == -1) break;	// 무효값이면 반복 종료

		// 선택 재확인
		cout << endl << selectChara.Name.WithPP("를") << " 선택하시겠습니까?" << endl;
		cout << "[0] 예\t[1] 아니오" << endl;
		if (!GetInput({ 0,1 }))
		{
			Character::CharaList[Local::Get("현재 캐릭터")] = *currentChara;

			int index = 0;
			for (auto& chara : Character::CharaList)
			{
				if (chara.ID == selectChara.ID)
				{
					Local::Set("현재 캐릭터", index);
					break;
				}
				else index++;
			}

			*currentChara = selectChara;
			break;
		}
	}
}

void ShopSave()
{
	int index = 0;	// 저장 슬롯 인덱스 (10개 단위)
	while (true)
	{
		cout << endl << "몇번 슬롯에 저장하시겠습니까?" << endl << endl;
		int select = SelectSaveSlot(index);	// 선택 받기
		if (select == 100) break;	// 종료
		else if (select == 101)	// 이전 슬롯
		{
			if (--index < 0) index += 10;
		}
		else if (select == 109)	// 다음 슬롯
		{
			if (++index > 9) index -= 10;
		}
		else if (select >= 90)
		{
			cout << endl << "자동 저장 슬롯입니다." << endl;
			Wait;
		}
		else	// 저장
		{
			bool IsExisting = GetSlotStream(select).good();	// 저장 슬롯에 이미 파일이 존재하는가

			cout << endl << "정말로 ";
			if (IsExisting)
				SetColor(11);
			else
				SetColor(8);
			cout << "[" << select << "]번 슬롯";
			SetColor(7);

			cout << "에 저장하시겠습니까?" << endl;

			// 파일 존재시 경고
			if (IsExisting)
			{
				cout << "이미 저장되어 있는 슬롯의 경우, ";
				SetColor(11);
				cout << "기존 저장내용";
				SetColor(7);
				cout << "은 사라지게 됩니다." << endl;
			}

			// 선택 재확인
			cout << "[0] 예" << endl;
			cout << "[1] 아니요" << endl;
			if (!GetInput({ 0,1 }))
			{
				Save(select);	// 저장
				break;
			}
		}
	}
}

void ShopLoad(Character* chara)
{
	int index = 0;	// 저장 슬롯 인덱스 (10개 단위)
	while (true)
	{
		cout << endl << "몇번 슬롯에서 불러오시겠습니까?" << endl << endl;
		int select = SelectSaveSlot(index);	// 선택 받기
		if (select == 100) break;	// 종료
		else if (select == 101)	// 이전 슬롯
		{
			if (--index < 0) index += 10;
		}
		else if (select == 109)	// 다음 슬롯
		{
			if (++index > 9) index -= 10;
		}
		else	// 불러오기
		{
			if (!GetSlotStream(select).good()) continue;	// 파일이 없으면 다시 선택

			cout << endl << "정말로 ";
			SetColor(11);
			cout << "[" << select << "]번 슬롯";
			SetColor(7);

			cout << "에서 불러오시겠습니까?" << endl;

			// 선택 재확인
			cout << "[0] 예" << endl;
			cout << "[1] 아니요" << endl;
			if (!GetInput({ 0,1 }))
			{
				Load(select);	// 불러오기
				*chara = Character::CharaList[Local::Get("현재 캐릭터")];
				break;
			}
		}
	}
}

#pragma endregion
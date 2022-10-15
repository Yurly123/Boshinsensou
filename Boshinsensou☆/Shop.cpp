#include "Shop.h"

void Shop()
{
	Charactor CurrentChara;
	while (true)
	{
		vector<Charactor> OwnCharaList;
		vector<Charactor> AllChara = Charactor::GetAllChara();
		for (auto& ownChara : AllChara)
		{
			if (ownChara.ID == CurrentChara.ID)
				ownChara = CurrentChara;
			if (ownChara.GetCtalent("보유중"))
				OwnCharaList.push_back(ownChara);
		}
		Charactor::UpdateCharaList(AllChara);
		if (CurrentChara.ID == -1)
			CurrentChara = OwnCharaList.front();

		cout << endl;
		PrintLine();
		cout << endl;
		cout << "   현재 캐릭터 : " << CurrentChara.Name << endl;
		PrintCharaHPEP(CurrentChara);
		cout << endl << endl;

		PrintLine();
		cout << endl;
		cout << "   " << "[100] 훈련하기";
		cout << "   " << "[101] 캐릭터 정보";
		cout << "   " << "[109] 캐릭터 변경";
		cout << "   " << "[200] 저장하기";
		cout << "   " << "[300] 불러오기";
		cout << endl << endl;
		PrintLine();
		int Input = GetInput({ 100,101,109,200,300 });
		switch (Input)
		{
		case 100:
			Train(CurrentChara);
			break;
		case 101:
			while (true)
			{
				cout << endl << "정보를 보고싶은 캐릭터를 고르십시오" << endl << endl;
				Charactor selectChara = SelectCharactor(OwnCharaList);
				if (selectChara.ID == -1) break;
				ShowCharaInfo(selectChara);
			}
			break;
		case 109:
			while (true)
			{
				cout << endl << "선택하려는 캐릭터를 고르십시오" << endl << endl;
				Charactor selectChara = SelectCharactor(OwnCharaList);
				if (selectChara.ID == -1) break;

				cout << endl << selectChara.Name.WithPP("를") << " 선택하시겠습니까?" << endl;
				cout << "[0] 예\t[1] 아니오" << endl;
				if (!GetInput({ 0,1 }))
				{
					CurrentChara = selectChara;
					break;
				}
			}
			break;
		case 200:
		{
			int index = 0;
			while (true)
			{
				cout << endl << "몇번 슬롯에 저장하시겠습니까?" << endl << endl;
				int select = SelectSaveSlot(index);
				if (select == 100) break;
				else if (select == 101)
				{
					if (--index < 0) index += 10;
				}
				else if (select == 109)
				{
					if (++index > 9) index -= 10;
				}
				else
				{
					bool IsExisting = GetSlotStream(select).good();
					cout << endl << "정말로 ";
					if (IsExisting)
						SetColor(11);
					else
						SetColor(8);
					cout << "[" << select << "]번 슬롯";
					SetColor(7);

					cout << "에 저장하시겠습니까?" << endl;

					if (IsExisting)
					{
						cout << "이미 저장되어 있는 슬롯의 경우, ";
						SetColor(11);
						cout << "기존 저장내용";
						SetColor(7);
						cout << "은 사라지게 됩니다." << endl;
					}

					cout << "[0] 예" << endl;
					cout << "[1] 아니요" << endl;
					if (!GetInput({ 0,1 }))
					{
						Save(select, CurrentChara);
						break;
					}
				}
			}
		}
		break;
		case 300:
		{
			int index = 0;
			while (true)
			{
				cout << endl << "몇번 슬롯에서 불러오시겠습니까?" << endl << endl;
				int select = SelectSaveSlot(index);
				if (select == 100) break;
				else if (select == 101)
				{
					if (--index < 0) index += 10;
				}
				else if (select == 109)
				{
					if (++index > 9) index -= 10;
				}
				else
				{
					if (!GetSlotStream(select).good()) continue;
					cout << endl << "정말로 ";
					SetColor(11);
					cout << "[" << select << "]번 슬롯";
					SetColor(7);

					cout << "에서 불러오시겠습니까?" << endl;

					cout << "[0] 예" << endl;
					cout << "[1] 아니요" << endl;
					if (!GetInput({ 0,1 }))
					{
						Load(select, CurrentChara);
						break;
					}
				}
			}
		}
		break;
		}
	}
}

Charactor SelectCharactor(vector<Charactor>& charaList)
{
	PrintLine();
	cout << endl;
	vector<int> IDList;

	for (Charactor& chara : charaList)
	{
		cout << "  [" << setw(3) << chara.ID << "] " << chara.Name << endl;
		IDList.push_back(chara.ID);
	}
	cout << endl;
	PrintLine();
	cout << endl << "\t[1000] 돌아가기" << endl;
	IDList.push_back(1000);
	int SelectID = GetInput(IDList);
	if (SelectID == 1000) return Charactor();
	for (Charactor& chara : charaList)
	{
		if (chara.ID == SelectID) return chara;
	}
	return Charactor();
}

void ShowCharaInfo(Charactor& Chara)
{
	cout << endl;
	PrintLine();
	cout << endl;
	cout << "  소질 : ";
	for (int i = 1; i < CData::Talent_Length; ++i)
	{
		if (Chara.Ctalent[i])
			cout << "[" << CData::GetTalent(i) << "] ";
	}
	cout << endl << endl;

	PrintLine();
	cout << endl << "   -" << Chara.ID << "-\t" << Chara.Name << endl;
	cout << endl << " " << Chara.GetCstr("이름") << endl << endl << GetCharaDescription(Chara) << endl;

	PrintLine();
	cout << endl << "\t[1000] 돌아가기" << endl;

	GetInput({ 1000 });
}
#include "Shop.h"

void Shop()
{
	vector<Charactor> OwnCharaList;
	for (auto ownChara : Charactor::GetAllChara())
	{
		if (ownChara.cData.cflag[CData::CFlag("보유중")])
			OwnCharaList.push_back(ownChara);
	}
	Charactor CurrentChara = OwnCharaList.front();
	while (true)
	{
		cout << endl << "현재 캐릭터 : " << CurrentChara.Name.Text << endl;
		PrintLine();
		printf("\n     [100] 훈련하기     [101] 캐릭터 정보     [109] 캐릭터 변경     [200] 저장하기\n\n");
		PrintLine();
		int Input = GetInput({ 100,101,109,200 });
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

					cout <<"에 저장하시겠습니까?" << endl;

					if (IsExisting)
					{
						cout << "이미 저장되어 있는 슬롯의 경우, ";
						SetColor(11);
						cout << "기존 저장내용";
						SetColor(7);
						cout <<"은 사라지게 됩니다." << endl;
					}
						
					cout << "[0] 예" << endl;
					cout << "[1] 아니요" << endl;
					if (!GetInput({ 0,1 }))
					{
						Save(select);
						break;
					}
				}
			}
			break;
		}
	}
}

Charactor SelectCharactor(vector<Charactor> charaList)
{
	PrintLine();
	cout << endl;
	vector<int> IDList;

	for (Charactor chara : charaList)
	{
		cout << "  [" << setw(3) << chara.ID << "] " << chara.Name.Text << endl;
		IDList.push_back(chara.ID);
	}
	cout << endl;
	PrintLine();
	cout << endl << "\t[1000] 돌아가기" << endl;
	IDList.push_back(1000);
	int SelectID = GetInput(IDList);
	if (SelectID == 1000) return Charactor();
	for (Charactor chara : charaList)
	{
		if (chara.ID == SelectID) return chara;
	}
}

void ShowCharaInfo(Charactor Chara)
{
	cout << endl;
	PrintLine();
	cout << endl;
	cout << "  소질 : ";
	for (int i = 1; i < CData::CTalent_Length; ++i)
	{
		if (Chara.cData.ctalent[i])
			cout << "[" << CData::CTalent(i) << "] ";
	}
	cout << endl << endl;

	PrintLine();
	cout << endl << "   -" << Chara.ID << "-\t" << Chara.cData.cstr[CData::CStr("이름")] << endl << endl;
	cout << "  체력 : " << Chara.cData.cflag[CData::CFlag("현재체력")] << " / " << Chara.cData.cflag[CData::CFlag("최대체력")] << endl;

	cout << endl << GetCharaDescription(Chara) << endl;

	PrintLine();
	cout << endl << "\t[1000] 돌아가기" << endl;

	GetInput({ 1000 });
}
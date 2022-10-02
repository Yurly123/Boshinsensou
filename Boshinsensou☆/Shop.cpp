#include "Shop.h"

void Shop()
{
	vector<Charactor> OwnCharaList;
	for (auto ownChara : Charactor::GetAllChara())
	{
		if (ownChara.cData.cflag[CData::CFlag("������")])
			OwnCharaList.push_back(ownChara);
	}
	Charactor CurrentChara = OwnCharaList.front();
	while (true)
	{
		cout << endl << "���� ĳ���� : " << CurrentChara.Name.Text << endl;
		PrintLine();
		printf("\n     [100] �Ʒ��ϱ�     [101] ĳ���� ����     [109] ĳ���� ����     [200] �����ϱ�\n\n");
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
				cout << endl << "������ ������� ĳ���͸� ���ʽÿ�" << endl << endl;
				Charactor selectChara = SelectCharactor(OwnCharaList);
				if (selectChara.ID == -1) break;
				ShowCharaInfo(selectChara);
			}
			break;
		case 109:
			while (true)
			{
				cout << endl << "�����Ϸ��� ĳ���͸� ���ʽÿ�" << endl << endl;
				Charactor selectChara = SelectCharactor(OwnCharaList);
				if (selectChara.ID == -1) break;

				cout << endl << selectChara.Name.WithPP("��") << " �����Ͻðڽ��ϱ�?" << endl;
				cout << "[0] ��\t[1] �ƴϿ�" << endl;
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
				cout << endl << "��� ���Կ� �����Ͻðڽ��ϱ�?" << endl << endl;
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
					cout << endl << "������ ";
					if (IsExisting)
						SetColor(11);
					else
						SetColor(8);
					cout << "[" << select << "]�� ����";
					SetColor(7);

					cout <<"�� �����Ͻðڽ��ϱ�?" << endl;

					if (IsExisting)
					{
						cout << "�̹� ����Ǿ� �ִ� ������ ���, ";
						SetColor(11);
						cout << "���� ���峻��";
						SetColor(7);
						cout <<"�� ������� �˴ϴ�." << endl;
					}
						
					cout << "[0] ��" << endl;
					cout << "[1] �ƴϿ�" << endl;
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
	cout << endl << "\t[1000] ���ư���" << endl;
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
	cout << "  ���� : ";
	for (int i = 1; i < CData::CTalent_Length; ++i)
	{
		if (Chara.cData.ctalent[i])
			cout << "[" << CData::CTalent(i) << "] ";
	}
	cout << endl << endl;

	PrintLine();
	cout << endl << "   -" << Chara.ID << "-\t" << Chara.cData.cstr[CData::CStr("�̸�")] << endl << endl;
	cout << "  ü�� : " << Chara.cData.cflag[CData::CFlag("����ü��")] << " / " << Chara.cData.cflag[CData::CFlag("�ִ�ü��")] << endl;

	cout << endl << GetCharaDescription(Chara) << endl;

	PrintLine();
	cout << endl << "\t[1000] ���ư���" << endl;

	GetInput({ 1000 });
}
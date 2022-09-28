#include "Shop.h"

void Shop()
{
	Charactor CurrentChara = GetAllChara().front();
	while (true)
	{
		cout << endl << "���� ĳ���� : " << CurrentChara.name.Text << endl;
		PrintLine();
		printf("\n       �Ʒ��ϱ�[100]    ĳ���� ����[101]     ĳ���� ����[109]\n\n");
	//  printf("\n+=+=+=+=+=+=+=+=+=+_+=+=+=+=+=+=+=+=+=+_+=+=+=+=+=+=+=+=+=+_\n\n");
		PrintLine();
		int Input = GetInput({ 100,101,109 });
		switch (Input)
		{
		case 100:
			Train(CurrentChara);
			break;
		case 101:
			ShowCharaInfo(CurrentChara);
			Wait;
			break;
		case 109:
			CurrentChara = ChangeCharactor(CurrentChara);
			break;
		}
	}
}

Charactor ChangeCharactor(Charactor CurrentChara)
{
	while (true)
	{
		PrintLine();
		cout << endl;
		vector<int> IDList;
		vector<Charactor> CharaList = GetAllChara();

		for (Charactor Chara : CharaList)
		{
			cout <<  "\t" << Chara.name.Text << "\t[" << Chara.ID << "]" << endl;
			IDList.push_back(Chara.ID);
		}
		cout << endl << "\t���ư���[1000]" << endl;
		IDList.push_back(1000);
		PrintLine();
		int SelectID = GetInput(IDList);
		if (SelectID == 1000) return CurrentChara;

		Charactor SelectChara;
		for (Charactor Chara : CharaList)
		{
			if (Chara.ID == SelectID) SelectChara = Chara;
		}

		cout << endl << SelectChara.name.Text << SelectChara.name.GetPP("����") << " �ٲٽðڽ��ϱ�?" << endl;
		cout << "��[0]\t�ƴϿ�[1]" << endl;

		if (!GetInput({ 0,1 })) return SelectChara;
	}
}
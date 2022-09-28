#include "Shop.h"

void Shop()
{
	Charactor CurrentChara = GetAllChara().front();
	while (true)
	{
		cout << endl << "현재 캐릭터 : " << CurrentChara.name.Text << endl;
		PrintLine();
		printf("\n       훈련하기[100]    캐릭터 정보[101]     캐릭터 변경[109]\n\n");
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
		cout << endl << "\t돌아가기[1000]" << endl;
		IDList.push_back(1000);
		PrintLine();
		int SelectID = GetInput(IDList);
		if (SelectID == 1000) return CurrentChara;

		Charactor SelectChara;
		for (Charactor Chara : CharaList)
		{
			if (Chara.ID == SelectID) SelectChara = Chara;
		}

		cout << endl << SelectChara.name.Text << SelectChara.name.GetPP("으로") << " 바꾸시겠습니까?" << endl;
		cout << "예[0]\t아니오[1]" << endl;

		if (!GetInput({ 0,1 })) return SelectChara;
	}
}
#include "Shop.h"

void Shop()
{
	Charactor CurrentChara = Charactor("UDK", 1, 100);
	while (true)
	{
		PrintLine();
		printf("\n �Ʒ��ϱ�[100]\tĳ���� ����[101]\n\n");
		PrintLine();
		int Input = GetInput({ 100,101 });
		switch (Input)
		{
		case 100:
			Train(CurrentChara);
			break;
		case 101:
			ShowCharaInfo(CurrentChara);
			break;
		}
	}
}
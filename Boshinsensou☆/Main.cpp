#include "System.h"

void Initialize()
{
	system("mode con cols=100 lines=50");
	CData::LoadCDatas();
	Charactor::LoadCharaList();
}

int main()
{
	Initialize();
	Shop();
	int arr[10][10];
	int k = 0;
	for (int i = 0; i < 10; ++i)
	{
		if (i % 2 == 0)
		{
			for (int j = 0; j < 10; ++j)
			{
				arr[i][j] = ++k;
			}
		}
		else
		{
			for (int j = 9; j >= 0; --j)
			{
				arr[i][j] = ++k;
			}
		}
	}

	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}
}
#include "System.h"

void PrintLine()
{
	for (int i = 0; i < 97; ++i)
	{
		printf("─");
	}
	printf("\n");
}

int GetInput(vector<int> InputList)
{
	int Input;	// 입력 버퍼
	bool IsAvailable = false;	// 유효한 입력을 받았는가

	// 입력 반복
	while (!IsAvailable)
	{
		while (!(cin >> Input))	// 이상한 입력 거르기 (예: asdfasdf1234 -> false, 100 -> true)
		{
			// 콘솔 입력 버퍼 초기화
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}

		// InputList에서 입력값 거르기
		for (auto AvailableInput : InputList)
		{
			// InputList중에 하나면 입력 반복 나감
			if (Input == AvailableInput)
			{
				IsAvailable = true;
				break;
			}
		}

		// 잔여 버퍼 지우기
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}

	return Input;
}

extern char* programPath;
void Restart()
{
	system(programPath);
}
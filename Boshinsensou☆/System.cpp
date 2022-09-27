#include "system.h"

void PrintLine()
{
	for (int i = 0; i < 99; ++i)
	{
		printf("¦¡");
	}
	printf("\n");
}

int GetInput(vector<int> InputList)
{
	int Input;
	bool IsAvailable = false;
	while (!IsAvailable)
	{
		while (!(cin >> Input))
		{
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		for (auto AvailableInput : InputList)
		{
			if (Input == AvailableInput)
			{
				IsAvailable = true;
				break;
			}
		}
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}
	return Input;
}
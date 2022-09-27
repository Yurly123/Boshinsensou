#include "system.h"

void Print(string Text)
{
	cout << Text;
}

void PrintL(string Text)
{
	Print(Text + "\n");
}

void PrintLine()
{
	for (int i = 0; i < 99; ++i)
	{
		Print("¦¡");
	}
	Print("\n");
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
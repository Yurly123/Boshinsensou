#include "System.h"

void Title()
{
	while (true)
	{
		try
		{
			for (int i = 0; i < 100; ++i)
				cout << endl;

			PrintLine();
			cout << endl;

			cout << setw(56) << "Boshinsensou☆" << endl;

			cout << endl;
			PrintLine();
			Wait;

			for (int i = 0; i < 50; ++i)
				cout << endl;
			Shop();
		}
		catch (string code)
		{
			if (code != "Title") throw code;
		}
	}
}
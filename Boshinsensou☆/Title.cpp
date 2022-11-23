#include "Title.h"

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

			cout << setw(55) << "Boshinsou☆" << endl;

			cout << endl;
			PrintLine();
			Wait;

			for (int i = 0; i < 50; ++i)
				cout << endl;
			Shop();
		}
		catch (string type)
		{
			if (type != "Title") throw type;
		}
	}
}
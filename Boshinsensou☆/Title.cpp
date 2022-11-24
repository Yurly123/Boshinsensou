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
			cout << endl;

			cout << setw(58) << "[0] 시작하기" << endl;
			cout << setw(58) << "[1] 로드하기" << endl;

			if (GetInput({ 0,1 }))
			{
				Character temp;
				ShopLoad(&temp);
				if (temp.ID != -1) Shop();
			}
			else
			{
				for (int i = 0; i < 50; ++i)
					cout << endl;
				Shop();
			}
		}
		catch (string code)
		{
			if (code != "Title") throw code;
		}
	}
}
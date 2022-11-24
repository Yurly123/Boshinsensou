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
				cout << endl << "조작법 : " << endl;
				cout << endl << "대괄호 [] 안에 있는 숫자를 입력창에 입력하고 Enter키를 입력하면 그 옆에있는 명령이 실행됩니다." << endl;
				cout << endl << "지금과 같이 출력이 정지한 상태에서는 그냥 Enter키를 입력하면 다음으로 진행됩니다." << endl;
				Wait;
				cout << "주어진 캐릭터를 훈련시키고 적들과 전투하여 보세요!" << endl;
				Wait;
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
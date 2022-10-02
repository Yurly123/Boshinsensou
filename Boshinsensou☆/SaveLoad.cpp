#include "SaveLoad.h"

int SelectSaveSlot(int index)
{
	vector<int> InputLIst;

	PrintLine();
	cout << endl;

	for (int i = index * 10; i < (index * 10) + 10; ++i)
	{
		ifstream slot = GetSlotStream(i);
		if (slot.good())
		{
			SetColor(11);
			cout << "  [" << i << "]\t";
			string buff;
			getline(slot, buff);
			cout << buff;
		}
		else
		{
			SetColor(8);
			cout << "  [" << i << "]\t";
			cout << "없음";
		}
		cout << endl;
		SetColor(7);
	}

	cout << endl << "\t-" << index + 1 << "-" << endl << endl;
	PrintLine();
	cout << endl << "     [101] 이전 페이지     [100] 돌아가기     [109] 다음 페이지" << endl;

	for (int i = 0; i < 100; ++i)
		InputLIst.push_back(i);
	InputLIst.push_back(100);
	InputLIst.push_back(101);
	InputLIst.push_back(109);

	return GetInput(InputLIst);
}

ifstream GetSlotStream(int index)
{
	string path = "sav\\";
	if (index / 10 == 0) path.append("0");
	path.append(to_string(index));
	path.append(".sav");
	ifstream slot(path);
	return slot;
}

void Save(int index)
{
	string path = "sav\\";
	if (!(index / 10)) path.append("0");
	path.append(to_string(index));
	path.append(".sav");
	ofstream out(path);

	time_t timer = time(NULL);
	struct tm* t = localtime(&timer);
	out << t->tm_year + 1900 << "-";
	out << setfill('0') << setw(2) << t->tm_mon + 1 << "-";
	out << setfill('0') << setw(2) << t->tm_wday << "_";
	out << setfill('0') << setw(2) << t->tm_hour << ":";
	out << setfill('0') << setw(2) << t->tm_min << ":";
	out << setfill('0') << setw(2) << t->tm_sec << endl;

	out.close();
}
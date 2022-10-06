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
	return ifstream(path);
}

void Save(int index, Charactor& selectChara)
{
	string path = "sav\\";
	if (!(index / 10)) path.append("0");
	path.append(to_string(index));
	path.append(".sav");
	ofstream out(path);

	// 날짜 저장
	time_t timer = time(NULL);
	struct tm* t = localtime(&timer);
	out << t->tm_year + 1900 << "-";
	out << setfill('0') << setw(2) << t->tm_mon + 1 << "-";
	out << setfill('0') << setw(2) << t->tm_wday << "_";
	out << setfill('0') << setw(2) << t->tm_hour << ":";
	out << setfill('0') << setw(2) << t->tm_min << ":";
	out << setfill('0') << setw(2) << t->tm_sec << endl;

	// CData 저장
	out << Charactor::GetAllChara().size() << endl;
	for (auto chara : Charactor::GetAllChara())
	{
		out << chara.ID << endl;
		for (int i = 0; i < CData::Flag_Length; ++i)
			out << "flag," << i << "," << chara.Cflag[i] << "," << endl;
		for (int i = 0; i < CData::Talent_Length; ++i)
			out << "talent," << i << "," << chara.Ctalent[i] << "," << endl;
		for (int i = 0; i < CData::Str_Length; ++i)
			out << "str," << i << "," << chara.Cstr[i] << "," << endl;
		out << "," << endl;
	}

	// 선택 캐릭터 저장
	out << selectChara.ID << endl;

	out.close();
}

void Load(int index, Charactor& selectChara)
{
	string path = "sav\\";
	if (!(index / 10)) path.append("0");
	path.append(to_string(index));
	path.append(".sav");
	ifstream in(path);

	string Buffer;
	getline(in, Buffer);

	getline(in, Buffer);
	int charaCount = stoi(Buffer);
	vector<Charactor> charaList = Charactor::GetAllChara();

	for (int i = 0; i < charaCount; ++i)
	{
		getline(in, Buffer);
		int charaID = stoi(Buffer);

		Charactor loadChara;
		for (auto chara : charaList)
			if (chara.ID == charaID)
			{
				loadChara = chara;
				break;
			}
		
		while (true)
		{
			getline(in, Buffer, ',');
			if (Buffer == "flag")
			{
				getline(in, Buffer, ',');
				int index = stoi(Buffer);

				getline(in, Buffer, ',');
				int value = stoi(Buffer);

				loadChara.Cflag[index] = value;
			}
			else if (Buffer == "talent")
			{
				getline(in, Buffer, ',');
				int index = stoi(Buffer);

				getline(in, Buffer, ',');
				bool value = stoi(Buffer);

				loadChara.Ctalent[index] = value;
			}
			else if (Buffer == "str")
			{
				getline(in, Buffer, ',');
				int index = stoi(Buffer);

				getline(in, Buffer, ',');
				string value = Buffer;

				loadChara.Cstr[index] = value;
			}
			else
			{
				getline(in, Buffer);
				break;
			}

			getline(in, Buffer);
		}

		for (auto& chara : charaList)
			if (chara.ID == charaID)
			{
				chara = loadChara;
				break;
			}
	}

	getline(in, Buffer);
	int id = stoi(Buffer);
	for (auto& chara : charaList)
		if (chara.ID == id)
		{
			selectChara = chara;
			break;
		}

	Charactor::UpdateCharaList(charaList);
}
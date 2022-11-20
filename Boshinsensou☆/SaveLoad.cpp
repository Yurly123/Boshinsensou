#include "SaveLoad.h"

#pragma region 전역 함수

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

			stringstream readStream;
			for(int i = 0; i < 50; ++i)
				readStream << (char)slot.get();
			readStream = Decode(readStream);

			string buff;
			getline(readStream, buff);
			cout << buff << "   ";

			getline(readStream, buff);
			int dayTime = stoi(buff);
			cout << dayTime / 2 + 1 << "일째 " << (dayTime % 2 ? "밤" : "낮");

			getline(readStream, buff);
			cout << "   " << buff << " 선택";
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

void Save(int index)
{
	stringstream out;

	// 날짜 저장
	time_t timer = time(NULL);
	struct tm* t = localtime(&timer);
	out << t->tm_year + 1900 << "-";
	out << setfill('0') << setw(2) << t->tm_mon + 1 << "-";
	out << setfill('0') << setw(2) << t->tm_wday << "_";
	out << setfill('0') << setw(2) << t->tm_hour << ":";
	out << setfill('0') << setw(2) << t->tm_min << ":";
	out << setfill('0') << setw(2) << t->tm_sec << endl;
	
	out << Local::Get("현재 시간") << endl;
	int count = 0;
	for (auto& chara : Character::CharaList)
		if (chara.GetTalent("보유중"))
			if (Local::Get("선택 캐릭터") == count)
			{
				out << chara.Name << endl;
				break;
			}
			else count++;

	// CData 저장
	out << Character::CharaList.size() << endl;
	for (auto& chara : Character::CharaList)
	{
		out << chara.ID << endl;
		for (auto& flag : CData::CFlagList)
			out << "flag," << flag.first << "," << chara.Cflag[flag.first] << "," << endl;
		for (auto& talent : CData::CTalentList)
			out << "talent," << talent.first << "," << chara.Ctalent[talent.first] << "," << endl;
		for (auto& str : CData::CStrList)
			out << "str," << str.first << "," << chara.Cstr[str.first] << "," << endl;
		out << "," << endl;
	}

	for (auto& local : Local::LocalList)
	{
		out << local.first << "," << local.second << "," << endl;
	}

	out = Encode(out);
	string path = "sav\\";
	if (!(index / 10)) path.append("0");
	path.append(to_string(index));
	path.append(".sav");
	ofstream saveStream(path);
	while (!out.eof())
	{
		saveStream << (char)out.get();
	}
	saveStream.close();
}

void Load(int index)
{
	string path = "sav\\";
	if (!(index / 10)) path.append("0");
	path.append(to_string(index));
	path.append(".sav");
	ifstream loadStream(path);
	stringstream in;
	while (!loadStream.eof())
	{
		in << (char)loadStream.get();
	}
	in = Decode(in);

	string buffer;
	getline(in, buffer);
	getline(in, buffer);
	getline(in, buffer);

	getline(in, buffer);
	int charaCount = stoi(buffer);

	for (int i = 0; i < charaCount; ++i)
	{
		getline(in, buffer);
		int charaID = stoi(buffer);

		Character loadChara;
		for (auto& chara : Character::CharaList)
			if (chara.ID == charaID)
			{
				loadChara = chara;
				break;
			}
		
		while (true)
		{
			getline(in, buffer, ',');
			if (buffer == "flag")
			{
				getline(in, buffer, ',');
				int index = stoi(buffer);

				getline(in, buffer, ',');
				int value = stoi(buffer);

				loadChara.Cflag[index] = value;
			}
			else if (buffer == "talent")
			{
				getline(in, buffer, ',');
				int index = stoi(buffer);

				getline(in, buffer, ',');
				bool value = stoi(buffer);

				loadChara.Ctalent[index] = value;
			}
			else if (buffer == "str")
			{
				getline(in, buffer, ',');
				int index = stoi(buffer);

				getline(in, buffer, ',');
				string value = buffer;

				loadChara.Cstr[index] = value;
			}
			else
			{
				getline(in, buffer);
				break;
			}

			getline(in, buffer);
		}

		for (auto& chara : Character::CharaList)
			if (chara.ID == charaID)
			{
				chara = loadChara;
				break;
			}
	}

	for (auto& local : Local::LocalList)
	{
		getline(in, buffer, ',');
		int id = stoi(buffer);

		getline(in, buffer, ',');
		int value = stoi(buffer);

		Local::LocalList[id] = value;

		getline(in, buffer);
	}
}

stringstream Encode(stringstream& stream)
{
	stringstream code;
	int singleCode;
	int temp;
	while (!stream.eof())
	{
		singleCode = stream.get();

		singleCode += 127;
		temp = singleCode & 0b1111;
		singleCode >>= 4;
		singleCode += temp << 4;

		code << (char)singleCode;
	}
	return code;
}
stringstream Decode(stringstream& stream)
{
	stringstream code;
	int singleCode;
	int temp;
	while (!stream.eof())
	{
		singleCode = stream.get();
		
		temp = singleCode & 0b1111;
		singleCode >>= 4;
		singleCode += temp << 4;
		singleCode -= 127;

		code << (char)singleCode;
	}
	return code;
}

void AutoSave()
{
	for (int i = 0; i < 10; ++i)
	{
		auto slot = GetSlotStream(90 + i);
		if (slot.fail())
		{
			Save(90 + i);
			string path = "sav\\";
			path.append(to_string(i < 9 ? 90 + i + 1 : 90));
			path.append(".sav");
			remove(path.c_str());
			slot.close();
			break;
		}
		slot.close();
	}
}

#pragma endregion
#include "Charactor.h"

void ShowCharaInfo(Charactor Chara)
{
	PrintLine();
	cout << endl << "   -" << Chara.ID << "-\t" << Chara.name.Text << endl;
	cout << "   ü�� : " << Chara.HP << endl;
	cout << endl << endl << GetCharaDescription(Chara) << endl;
	PrintLine();
}

string GetCharaDescription(Charactor Chara)
{
	string Description;
	switch (Chara.ID)
	{
	case 1:
		Description.append("����Ű �ڿ켼��\n\n");
		Description.append("��Ű���� ��â�� ����ν�, ���ͳݿ��� ������� ����� �����̴�. ������ ������\n");
		Description.append("RU���԰� ���̰� ����, ������ ���δ� ������ ������ ���������� �ʴٴ� �ָ��� ������ ���������.\n");
		Description.append("UDK������ Ư���� ��Ҹ��� �αⰡ ���Ƽ� ���� ���� �Ŵ����ٰ� �Ѵ�.\n");
		Description.append("��Ű�ٸ� ȣ���κ��� ��Ű�� ���� �Ⲩ�� �� ������ �߽ɿ��� Ȱ���ϰ� �ִ�.\n");
		Description.append("�����ϴ� ������ ��ημҹ�.\n");
		break;
	case 2:
		Description.append("����\n\n");
		Description.append("��Ű���� ������ �� ��â�� ����ν�, ���� ���� ��� �ŷ����� �����̴�.\n");
		Description.append("UDK���԰� ���̰� ����, ������ ���δ� ������ ������ ���������� �ʴٴ� �ָ��� ������ ���������.\n");
		Description.append("���� ���ø鼭 \"Ǫ��! ���õ� ���� ������\" ��� ���ϴ� Ư���� ������ ������.\n");
		Description.append("�̹� ���￡�� ������ ������ ���������� ū ������ �̷������ ���ȴ�.\n");
		Description.append("������ RU������ �����ڸ� ���� ������ ����ü�� ���ߵƾ���.\n");
		break;
	case 3:
		Description.append("������ �Ϸ�ī\n\n");
		Description.append("��Ű�� �ʴ��� �ι�° ������ ���ΰ��� ALC���� �ð� �ִ� �����̴�.\n");
		Description.append("�׻� ���� �󱼷� ������ ���ϸ� ������ ���ῡ�� �ݷ��� �� ���ֱ������ �ϴ� ������ �Ͱ��̴�.\n");
		Description.append("��ҿ��� ������ ����������, �ѹ� ȭ�� ���� ģ�� UDK���� ��ٸ� �ĸ��⸦ �� ������ �������̰� ���Ѵ�.\n");;
		Description.append("HNS�� �ȿ��� ������� �Ŵ��� ��ü�� ���� HNS�� �������� �ſ� ū ������ ��½�ų ������ ���δ�.\n");
		Description.append("������ �������� ��� �ִٰ� �Ѵ�.\n");
		break;
	case 4:
		Description.append("�߹�\n\n");
		Description.append("��Ű��1�⸦ ������ ���� ��ǰ���� SIK���� �ð� �ִ� �����̴�.\n");
		Description.append("������ �������� ������ ������ ���� ������ ����, ������ ������� �ϴ� ���ؼ��� �����־���.\n");
		Description.append("������ ������ �������� ��Ű���� �� ������ ������ ������ ���� �ʴ� ����� �����־���.\n");
		Description.append("KNN���Կ��� �˼��� ���� �޾�����, ������������[���������µ�] ��� ������� �ٷ� �� �ִ�.\n");
		Description.append("���� ������ �߼������� �������̶�� �Ӽ��� ������ �ִ�.\n");
		break;
	default:
		Description.append("ERROR ����\n\n");
		Description.append("��Ű��0�⿡ �⿬ ��û�� ������ 1:114514�� ������� ���� ���ϰ� �ᱹ �������� �Ǿ���.\n");
		Description.append("���� COAT���� ȣ��������� �⿬ ��û�� ������ �� ���� 1:110���� ������� ���� ���ϰ� ��������.\n");
		Description.append("��Ű�ٿ� ���� ��ο��� ������ �׳�� �ᱹ ��𿡵� ������ ���ϰ� �� ���¿� �ָ����� �Ǿ���.\n");
		Description.append("������ �׳�� ���ݵ� ���ӿ� �⿬���� ���ϰ� ������ �����θ� �����ϰ� �Ǿ���.\n");
		Description.append("��������.. (���๫��)\n");
		break;
	}
	return Description;
}

vector<Charactor> GetAllChara()
{
	ifstream FileStream("Charactors.csv");
	vector<Charactor> CharaList;
	while (!FileStream.eof())
	{
		string Buffer;

		getline(FileStream, Buffer, ',');
		int id = stoi(Buffer);

		getline(FileStream, Buffer, ',');
		string name = Buffer;

		getline(FileStream, Buffer, ',');
		bool IsAlt = Buffer == "true";

		getline(FileStream, Buffer, ',');
		int hp = stoi(Buffer);

		CharaList.push_back(Charactor(name, IsAlt, id, hp));
	}
	FileStream.close();

	return CharaList;
}
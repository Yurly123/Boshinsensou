#include "Charactor.h"

vector<Charactor> Charactor::CharaList = vector<Charactor>();

void Charactor::LoadCData()
{
	string filepath;
	filepath.append(to_string(ID));
	filepath.append(" ");
	filepath.append(Name.Text);
	filepath.append(".csv");
	this->cData = LoadCharaData(filepath);
}
void Charactor::LoadCharaList()
{
	ifstream FileStream("Charactors.csv");
	while (!FileStream.eof())
	{
		string Buffer;

		getline(FileStream, Buffer, ',');
		int id = stoi(Buffer);

		getline(FileStream, Buffer, ',');
		string name = Buffer;

		getline(FileStream, Buffer);
		bool IsAlt = Buffer == "true";

		Charactor chara = Charactor(name, IsAlt, id);
		CharaList.push_back(chara);
	}
	FileStream.close();
}
vector<Charactor> Charactor::GetAllChara()
{
	return CharaList;
}
Charactor::Charactor(string name, bool IsAlt, int ID)
{
	this->Name = ::Name(name, IsAlt);
	this->ID = ID;
	LoadCData();
}

Name::Name(string text, bool isalt)
{
	Text = text;
	IsAlt = isalt;
}
string Name::GetPP(string PP)
{
	//ori �� �� �� ��   �� ��   �μ�   �ν�
	//alt �� �� �� ���� �� �̳� ���μ� ���ν�
	if (IsAlt)
	{
		if (PP == "��") PP = "��";
		else if (PP == "��") PP = "��";
		else if (PP == "��") PP = "��";
		else if (PP == "��") PP = "����";
		else if (PP == "��") PP = "��";
		else if (PP == "��") PP = "�̳�";
		else if (PP == "�μ�") PP = "���μ�";
		else if (PP == "�ν�") PP = "���ν�";
	}
	else
	{
		if (PP == "��") PP = "��";
		else if (PP == "��") PP = "��";
		else if (PP == "��") PP = "��";
		else if (PP == "����") PP = "��";
		else if (PP == "��") PP = "��";
		else if (PP == "�̳�") PP = "��";
		else if (PP == "���μ�") PP = "�μ�";
		else if (PP == "���ν�") PP = "�ν�";
	}
	return PP;
}
string Name::WithPP(string PP)
{
	string text = Text;
	return text.append(GetPP(PP));
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
		Description.append("������ RU������ �����ڸ� ���� ������ ����ü�� ���ߵǾ��� �Ѵ�.\n");
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

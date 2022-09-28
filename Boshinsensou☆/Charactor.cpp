#include "Charactor.h"

void ShowCharaInfo(Charactor Chara)
{
	PrintLine();
	cout << endl << "   -" << Chara.ID << "-\t" << Chara.name.Text << endl;
	cout << "   체력 : " << Chara.HP << endl;
	cout << endl << endl << GetCharaDescription(Chara) << endl;
	PrintLine();
}

string GetCharaDescription(Charactor Chara)
{
	string Description;
	switch (Chara.ID)
	{
	case 1:
		Description.append("우즈키 코우세이\n\n");
		Description.append("쿠키☆의 초창기 멤버로써, 인터넷에서 평생동안 떠드는 누님이다. 별명은 마리나\n");
		Description.append("RU누님과 사이가 좋다, 하지만 서로는 싫지는 않지만 좋아하지도 않다는 애매한 관계라고 얼버무린다.\n");
		Description.append("UDK누님은 특히나 목소리가 인기가 많아서 많은 팬을 거느린다고 한다.\n");
		Description.append("쿠키☆를 호모들로부터 지키기 위해 기꺼히 이 전쟁의 중심에서 활약하고 있다.\n");
		Description.append("좋아하는 음식은 토로로소바.\n");
		break;
	case 2:
		Description.append("레우\n\n");
		Description.append("쿠키☆의 시작을 연 초창기 멤버로써, 살이 조금 찐게 매력적인 누님이다.\n");
		Description.append("UDK누님과 사이가 좋다, 하지만 서로는 싫지는 않지만 좋아하지도 않다는 애매한 관계라고 얼버무린다.\n");
		Description.append("차를 마시면서 \"푸하! 오늘도 좋은 날씨☆\" 라고 말하는 특이한 습관을 가졌다.\n");
		Description.append("이번 전쟁에서 본인의 숨겨진 전투력으로 큰 성과를 이룰것으로 기대된다.\n");
		Description.append("옛날에 RU누님의 유전자를 무와 결합한 생명체가 개발됐었다.\n");
		break;
	case 3:
		Description.append("히나세 하루카\n\n");
		Description.append("쿠키☆ 초대의 두번째 실질적 주인공인 ALC역을 맡고 있는 누님이다.\n");
		Description.append("항상 웃는 얼굴로 남들을 대하며 좌절한 동료에게 격려를 잘 해주기까지도 하는 성우의 귀감이다.\n");
		Description.append("평소에는 얌전한 성격이지만, 한번 화가 나면 친한 UDK에게 밭다리 후리기를 걸 정도로 폭력적이게 변한다.\n");;
		Description.append("HNS의 팔에서 뻗어나오는 거대한 일체형 낫은 HNS의 전투력을 매우 큰 폭으로 상승시킬 것으로 보인다.\n");
		Description.append("은근한 변태적인 면모가 있다고 한다.\n");
		break;
	case 4:
		Description.append("야밍\n\n");
		Description.append("쿠키☆1기를 포함한 여러 작품에서 SIK역을 맡고 있는 누님이다.\n");
		Description.append("전쟁이 벌어지기 전부터 음몽에 대한 관심이 높아, 스스로 관장까지 하는 적극성을 보여주었다.\n");
		Description.append("하지만 전쟁이 벌어지자 쿠키☆의 편에 붙으며 성우의 본분을 잊지 않는 모습을 보여주었다.\n");
		Description.append("KNN누님에게 검술을 전수 받았으며, 淫夢之一太刀[음몽지일태도] 라는 전용검을 다룰 수 있다.\n");
		Description.append("실은 적장인 야수선배의 여동생이라는 속설이 떠돌고 있다.\n");
		break;
	default:
		Description.append("ERROR 누님\n\n");
		Description.append("쿠키☆0기에 출연 신청을 했지만 1:114514의 경쟁률을 뚫지 못하고 결국 떨어지게 되었다.\n");
		Description.append("그후 COAT사의 호모비디오에도 출연 신청을 했으나 이 또한 1:110약의 경쟁률을 뚫지 못하고 떨어졌다.\n");
		Description.append("쿠키☆와 음몽 모두에게 버려진 그녀는 결국 어디에도 속하지 못하고 이 사태에 휘말리게 되었다.\n");
		Description.append("하지만 그녀는 지금도 게임에 출연하지 못하고 데이터 상으로만 존재하게 되었다.\n");
		Description.append("슬프구나.. (제행무상)\n");
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
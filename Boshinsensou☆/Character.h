// 캐릭터 관련 클래스/함수 들
#pragma once

#include "System.h"

#include "UDK.h"

// 캐릭터 데이터 처리 클래스
static class CData
{
private:
	static map<string, int> CFlag_ID;	// Flag ID
	static map<string, int> CTalent_ID;	// Talent ID
	static map<string, int> CStr_ID;	// Str ID

public:
	
	// Flag ID 받기
	// name : 받을 Flag의 이름
	static int Flag(string);
	
	// Talent ID 받기
	// name : 받을 Talent의 이름 
	static int Talent(string);

	// Str ID 받기
	// name : 받을 tStr의 이름
	static int Str(string);
	
	// Flag 이름 받기
	// id : 받을 Flag의 ID
	static string Flag(int);

	// Talent 이름 받기
	// id : 받을 Talent의 ID
	static string Talent(int);

	// Str 이름 받기
	// id : 받을 Str의 ID
	static string Str(int);

	static map<int, string> CFlagList;	// Flag 이름
	static map<int, string> CTalentList;	// Talent 이름
	static map<int, string> CStrList;	// Str 이름

	// CFlag, CTalent, CStr 정보 로딩
	static void Load();
};

// 캐릭터 이름 처리(조사) 클래스
class Name
{
private:
	string Text;	// 이름
public:
	bool IsAlt;	// 조사가 alternative인가

	// 생성자
	// text : 이름
	// IsAlt 조사가 은,이,을... 쓰는가
	Name(string = "", bool = false);

	// 조사 받기
	// PP : 처리할 조사
	string GetPP(string);

	// 이름에 조사 붙여서 받기
	// PP : 처리할 조사
	string WithPP(string);

	// 객체 문자열 반환
	operator string() const
	{
		return Text;
	}

	// << 출력 연산자 재정의
	friend ostream& operator <<(ostream& out, const Name& name)
	{
		out << name.Text;
		return out;
	}
};

// 캐릭터 클래스
class Character
{
private:
	// 각 캐릭터의 데이터 로딩
	void InitChara();

public:
	Name Name;	// 캐릭터 이름
	int ID;	// 캐릭터 ID
	map<int, int> Cflag;	// Flag
	map<int, bool> Ctalent;	// Talent
	map<int, string> Cstr;	// Str
	
	// Flag 받기
	// name : 받을 Flag의 이름
	int GetFlag(string);
	
	// Talent 받기
	// name : 받을 Talent의 이름
	bool GetTalent(string);
	
	// Str 받기
	// name : 받을 Str의 이름
	string GetStr(string);
	
	// Flag 설정하기
	// name : 설정할 Flag의 이름
	// value : 설정할 값
	void SetFlag(string, int);
	
	// Talent 설정하기
	// name : 설정할 Talent의 이름
	// value : 설정할 값
	void SetTalent(string, bool);
	
	// Str 설정하기
	// name : 설정할 Str의 이름
	// value : 설정할 값
	void SetStr(string, string);

	// Flag 가감
	// name : 조정할 Flag의 이름
	// value : 가감할 값
	void AddFlag(string, int);

	static vector<Character> CharaList;	// 모든 캐릭터

	// Charactor.csv에서 캐릭터들 로딩
	static void LoadCharaList();

	// 생성자
	// name : 캐릭터 이름
	// IsAlt : 캐릭터 이름뒤에 은,이,을... 쓰는가
	// ID : 캐릭터 ID
	Character(string = "", bool = false, int = -1);

	static map<string, void (*)(Character&, Character&)> TurnSkillList;
	static map<string, void (*)(Character&, Character&)> EpSkillList;
	static map<string, void (*)(passive, Character&, Character&)> PassiveSkillList;

	static void LoadSkillList();
};

class Enemy : public Character
{
public:
	static vector<Enemy> EnemyList;
	Enemy(Character&);
};

// 캐릭터 설명 받기
string GetCharaDescription(int);

// 캐릭터 체력/기력 표시
// chara : 표시할 캐릭터
void PrintCharaHPEP(Character&);

// 캐릭터 정보 표시
// Chara : 정보를 표시할 캐릭터
void ShowCharaInfo(Character&);
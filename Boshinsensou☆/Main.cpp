#include "System.h"

// 초기설정, 데이터 로딩등 처리 함수
void Initialize()
{
	SetConsoleTitle(TEXT("Boshinsensou☆"));	// 콘솔창 이름 바꾸기
	system("mode con cols=100 lines=50");	// 콘솔창 크기 조절
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), { 100,250 });	// 콘솔창 버퍼 조정 (스크롤 띄우기)
	srand((unsigned int)time(NULL));	// 랜덤 시드 생성

	// 데이터 로딩
	SetColor(7);
	cout << "Loading CDatas..." << endl;
	CData::LoadCDatas();	// 캐릭터 데이터 로딩
	cout << "Loading Charactors..." << endl;
	Charactor::LoadCharaList();	// 캐릭터 로딩
	cout << "Loading Commands..." << endl;
	Command::LoadCommands();	// 커맨드 내용 로딩
	cout << "Loading Parameters..." << endl;
	Parameter::LoadParam();	// 패러미터 정보 로딩

	// 맨 밑으로 내리기
	for (int i = 0; i < 100; ++i)
		cout << endl;
}

// 프로그램 진입점
int main()
{
	Initialize();	// 기본 세팅
	Shop();	// 메인 루프
}
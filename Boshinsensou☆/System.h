// 통합 헤더파일
#pragma once

// 기본 라이브러리 사용
#include <iostream>	// 기본 입출력
#include <iomanip>	// 입출력 지원
#include <vector>	// vector 컨테이너
#include <array>	// array 컨테이너
#include <map>	// map 컨테이너
#include <Windows.h>	// windows api
#include <ctime>	// 랜덤 사용 + 시간 표현
#include <cstdlib>	// 랜덤 사용

// 매크로 정의

// 플레이어 입력(Enter) 대기
#define Wait getchar();	

// 출력 색상 변경-
//검정:0   어두운파랑:1   어두운초록:2   어두운청록:3   어두운빨강:4   어두운자홍:5   어두운노랑:6 
//하양:7   회색:8   파랑:9   초록:10   청록:11   빨강:12   자홍:13   노랑:14   밝은하양:15
#define SetColor(color) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color)	

using namespace std;	// 국룰

// 클래스 정의
class CData;
class Name;
class Charactor;
class Command;

// 사용자 정의 헤더파일 사용
#include "CData.h"
#include "Shop.h"
#include "Train.h"
#include "Charactor.h"
#include "SaveLoad.h"
#include "Command.h"

// 공용 함수 정의

// 한줄 선 출력
void PrintLine();

// 입력 받기
// InputList : 입력 받기 가능한 값들의 리스트
int GetInput(vector<int>);
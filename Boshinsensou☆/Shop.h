// Shop관련 함수들
#pragma once

#include "System.h"

// Shop 메인 루프
void Shop();

// 낮밤 바뀔때 처리
void ProgressTime(int);

// 캐릭터 리스트중 캐릭터 하나 선택
// charaList : 선택할 캐릭터들의 리스트
Character SelectCharactor(vector<Character>&);

// 캐릭터 정보 표시
// Chara : 정보를 표시할 캐릭터
void ShowCharaInfo(Character&);
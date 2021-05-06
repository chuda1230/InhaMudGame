#pragma once
void ScreenInit();									//스크린 초기화
void ScreenFlipping();								//스크린 변환
void ScreenClear();									//스크린 지우기
void ScreenRelease();								//스크린 반환
void ScreenPrint(int x, int y,const char* string);	//스크린 출력
void SetColor(unsigned short color);				//색 설정
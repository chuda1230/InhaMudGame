#pragma once
void ScreenInit();									//��ũ�� �ʱ�ȭ
void ScreenFlipping();								//��ũ�� ��ȯ
void ScreenClear();									//��ũ�� �����
void ScreenRelease();								//��ũ�� ��ȯ
void ScreenPrint(int x, int y,const char* string);	//��ũ�� ���
void SetColor(unsigned short color);				//�� ����
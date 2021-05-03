#include<iostream>
#include<time.h>
#include<conio.h>
#include<string.h>
#include "Screen.h"
#define MAP_COL 70
#define MAP_ROW 30
#define BULLET_MOVE_TIME 80
#define BULLET_MAX 100

typedef enum _DIRECT { UP, DOWN,LEFT,RIGHT } DIRECT;
const char *pState[4] = { "위쪽", "아래쪽", "왼쪽", "오른쪽" };
typedef struct _Player
{
	int x, y;
	int FireTime;
	int OldFireTime;
	DIRECT direct;
} Player;

typedef struct _Bullet
{
	int x,y;
	int Life;
	DIRECT Direct;
	int MoveTime;
}BULLET;

Player player;
BULLET PlayerBullet[BULLET_MAX];

void Init()
{
	player.x = 5;
	player.y = 10;
}
void Update()
{
	int i;
	clock_t curtime = clock();
	for (i = 0; i < BULLET_MAX; ++i)
	{
		if (PlayerBullet[i].Life == 1)
		{
			if (curtime - PlayerBullet[i].MoveTime >= BULLET_MOVE_TIME)
			{
				switch (PlayerBullet[i].Direct)
				{
				case LEFT:
					PlayerBullet[i].x -= 1;
					break;
				case RIGHT:
					PlayerBullet[i].x += 1;
					break;
				}
				PlayerBullet[i].MoveTime = curtime;
			}
			if (PlayerBullet[i].x<0 || PlayerBullet[i].x>MAP_COL - 1 ||
				PlayerBullet[i].y > MAP_ROW - 1 || PlayerBullet[i].y < 0)
			{
				PlayerBullet[i].Life = 0;
			}
		}
	}
}
void Render()
{
	char str[100];
	ScreenClear();

	ScreenPrint(player.x * 2, player.y, "◆");
	
	for (int i = 0; i < BULLET_MAX; ++i)
	{
		if (PlayerBullet[i].Life == 1)
		{
			ScreenPrint(PlayerBullet[i].x * 2, PlayerBullet[i].y, "-");
		}
	}
	sprintf_s(str, "%s 상태 %d %d", pState[player.direct], player.x, player.y);
	ScreenPrint(10, 20, str);
	ScreenFlipping();

}

int main(void)
{
	int key;
	clock_t curtime;

	ScreenInit();
	Init();
	
	while (1)
	{
		if (_kbhit())
		{
			key = _getch();
			curtime = clock();

			switch (key)
			{
			case 72:
				player.direct = UP;
				player.y--;
				break;
			case 80:
				player.direct = DOWN;
				player.y++;
				break;
			case 32:
				if (curtime - player.OldFireTime >= player.FireTime)
				{
					for (int i = 0; i < BULLET_MAX; ++i)
					{
						if (PlayerBullet[i].Life == 0)
						{
							PlayerBullet[i].Life = 1;
							PlayerBullet[i].Direct = RIGHT;
							PlayerBullet[i].x = player.x;
							PlayerBullet[i].y = player.y;

							switch (PlayerBullet[i].Direct)
							{
							case RIGHT:
								PlayerBullet[i].x += 1;
								break;
							}
							player.OldFireTime = PlayerBullet[i].MoveTime = curtime;
							break;
						}
					}
				}
				break;
			}
		}
		Update();
		Render();
	}
	//Release();
	ScreenRelease();
	return 0;
}
#include<iostream>
#include<time.h>
#include<conio.h>
#include<string.h>
#include "Screen.h"
#define MAP_COL 120
#define MAP_ROW 30
#define BULLET_MOVE_TIME 10
#define BULLET_MAX 100
int WallLife = 1000;
int Round = 1;
int RoundTime = 60;
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

typedef struct _ENEMY
{
	int x;
	int y;
	int Life;
	int Direct;
	int MoveTime;
	int ApperTime;
	int OldTime;
}ENEMY;

typedef struct _BOMBENEMY
{
	int x;
	int y;
	int Life;
	int MoveTime;
	int AppearTime;
	int OldTime;
} BOMB_ENEMY;

Player player;
BULLET PlayerBullet[BULLET_MAX];
int EnemyIndex = 0;
int BombEnemyIndex = 0;
unsigned int StartTime;
ENEMY Enemy[30];
BOMB_ENEMY Bomb_Enemy[15];

void Init()
{
	player.x = 1;
	player.y = 10;

	for (int i = 0; i < 30; ++i)
	{
		Enemy[i].ApperTime = 3600 * (i + 1);
		Enemy[i].Direct = LEFT;
		Enemy[i].MoveTime = 600;
		Enemy[i].x = MAP_COL - 3;
		Enemy[i].y = (rand() + 1) % 19 + 6;
		Enemy[i].Life = 1;
	}
	for (int i = 0; i < 15; ++i)
	{
		Bomb_Enemy[i].AppearTime = 4600 * (i + 1);
		Bomb_Enemy[i].MoveTime = 200;
		Bomb_Enemy[i].x = MAP_COL - 5;
		Bomb_Enemy[i].y = (rand()+1) % 19 + 6;
		Bomb_Enemy[i].Life = 1;
	}
}

void GamePhase()
{

}
void RepairPhase()
{

}
void EnemySpawn(int passtime)
{
	for (int i = EnemyIndex; i < 30; ++i)
	{
		if (Enemy[i].ApperTime <= passtime)
		{
			EnemyIndex++;
		}
		else
		{
			break;
		}
	}
	for (int i = BombEnemyIndex; i < 15; ++i)
	{
		if (Bomb_Enemy[i].AppearTime <= passtime)
		{
			BombEnemyIndex++;
		}
		else
		{
			break;
		}
	}
}



void EnemyMove(int curtime)
{
	for (int i = 0; i < EnemyIndex; ++i)
	{
		if (Enemy[i].Life == 1)
		{
			if (curtime - Enemy[i].OldTime > Enemy[i].MoveTime && Enemy[i].x>6)
			{
				Enemy[i].x--;
				Enemy[i].OldTime = curtime;
			}
		}
	}
	for (int i = 0; i < BombEnemyIndex; ++i)
	{
		if (Bomb_Enemy[i].Life == 1)
		{
			if (curtime - Bomb_Enemy[i].OldTime > Bomb_Enemy[i].MoveTime && Bomb_Enemy[i].x>6)
			{
				Bomb_Enemy[i].x--;
				Bomb_Enemy[i].OldTime = curtime;
			}
			else if(Bomb_Enemy[i].x==6)
			{
				Bomb_Enemy[i].Life = 0;
			}
		}
	}

}
void Update()
{
	int curtime = clock();
	int passtime=curtime-StartTime;
	int temp;
	

	EnemySpawn(passtime);
	EnemyMove(curtime);

	for (int i = 0; i < BULLET_MAX; ++i)
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
			if (PlayerBullet[i].x<0 || PlayerBullet[i].x*2>MAP_COL - 1 ||
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
	char Time[100];
	ScreenClear();
	int curtime = clock();
	sprintf_s(Time, "TIME : %.0lf", (double)60-(curtime*0.001));
	ScreenPrint(50, 3, Time);
	ScreenPrint(player.x, player.y - 1, " o");
	ScreenPrint(player.x , player.y, "()┏");
	ScreenPrint(player.x, player.y + 1, "|_");
	for (int i = 0; i < MAP_COL; ++i)
	{
		ScreenPrint(i, 5, "=");
	}
	for (int i = 0; i < MAP_COL; ++i)
	{
		ScreenPrint(i, 25, "=");
	}
	for (int i = 0; i < BULLET_MAX; ++i)
	{
		if (PlayerBullet[i].Life == 1)
		{
			ScreenPrint(PlayerBullet[i].x*2, PlayerBullet[i].y, "-");
		}
	}
	for (int i = 0; i < EnemyIndex; ++i)
	{
		ScreenPrint(Enemy[i].x, Enemy[i].y, "└ 0┐");
		ScreenPrint(Enemy[i].x, Enemy[i].y + 1,"┌ ㄴ");
	}

	for (int i = 0; i < BombEnemyIndex; ++i)
	{
		if (Bomb_Enemy[i].Life == 1)
		{
			ScreenPrint(Bomb_Enemy[i].x, Bomb_Enemy[i].y, "＼B/ ");
			ScreenPrint(Bomb_Enemy[i].x, Bomb_Enemy[i].y+1," ┌ ㄴ=3");
		}
	}
	for (int i = 6; i < 25; ++i)
	{
		ScreenPrint(4, i, "||");
	}
	sprintf_s(str, "%s 상태 %d %d", pState[player.direct], player.x, player.y);
	ScreenPrint(10, 20, str);
	ScreenFlipping();

}

void Release()
{

}

int main(void)
{
	srand(unsigned int(time(NULL)));
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
				if (player.y > 6)
				{
					player.direct = UP;
					player.y--;
				}
				break;
			case 80:
				if (player.y < 24)
				{
					player.direct = DOWN;
					player.y++;
				}
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
	Release();
	ScreenRelease();
	return 0;
}
﻿#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<time.h>
#include<conio.h>
#include<string.h>
#include "Screen.h"
#define MAP_COL 120
#define MAP_ROW 30
#define BULLET_MOVE_TIME 0.1
#define ROUND_TIME 60
int WallLife = 1000;
int Round;
double RoundTime = 0;
typedef enum _DIRECT { UP, DOWN,LEFT,RIGHT } DIRECT;
typedef enum _STATE {RUN,HIT,DEAD } STATE;
const char *pState[4] = { "위쪽", "아래쪽", "왼쪽", "오른쪽" };
typedef enum _PHASE {GAME,REPAIR,END} PHASE;
PHASE phase;
typedef struct _Player
{
	int x, y;
	int FireTime;
	int OldFireTime;
	DIRECT direct;
	int GunPower;
} Player;
Player player;
int MenuSelect = 0;
int TurretSelect = 0;
int UpgradeSelect = 0;
int TurretUpgradeSelect = 0;
int FirstTurretSelect = 0;
int FirstTurretUpgradeSelect = 0;

typedef struct _Bullet
{
	int x,y;
	int Life;
	DIRECT Direct;
	int MoveTime;
	int Power;

}BULLET;

BULLET *PlayerBullet;
int Bulletarrsize = 1;
int BulletSize = 0;
int lastofBullet = -1;
void Bullet_Full()
{
	PlayerBullet = (BULLET*)realloc(PlayerBullet, 2 * (Bulletarrsize) * sizeof(BULLET));
	Bulletarrsize *= 2;
}
void Bullet_push_back(BULLET item)
{
	if (lastofBullet >= Bulletarrsize - 1)
		Bullet_Full();
	PlayerBullet[++lastofBullet] = item;
	++BulletSize;
}
void Bullet_Delete(int index)
{
	for (int i = index; i < BulletSize; ++i)
	{
		PlayerBullet[i] = PlayerBullet[i + 1];	
	}
	--BulletSize;
	--lastofBullet;
}

typedef struct _ENEMY
{
	int x;
	int y;
	int Life;
	int Direct;
	int MoveTime;
	int ApperTime;
	int OldTime;
	STATE State;
}ENEMY;
ENEMY *Enemy_list;
int EnemyIndex = 0;
int Enemyarrsize = 1;
int lastofEnemy = -1;
clock_t EnemySpawnTime;
void Enemy_Full()
{
	Enemy_list = (ENEMY*)realloc(Enemy_list, 2 * (Enemyarrsize) * sizeof(ENEMY));
	Enemyarrsize *= 2;
}
void Enemy_push_back(ENEMY item)
{
	if (lastofEnemy >= Enemyarrsize - 1)
		Enemy_Full();
	Enemy_list[++lastofEnemy] = item;
	++EnemyIndex;
}
void Enemy_Delete(int index)
{
	for (int i = index; i < EnemyIndex; ++i)
	{
		Enemy_list[i] = Enemy_list[i + 1];
	}
	--EnemyIndex;
	--lastofEnemy;
}

typedef struct _BOMBENEMY
{
	int x;
	int y;
	int Life;
	int MoveTime;
	int AppearTime;
	int OldTime;
	STATE State;
} BOMB_ENEMY;

BOMB_ENEMY *BombEnemy_list;
int BombEnemyIndex = 0;
int BombEnemyarrsize = 1;
int lastofBombEnemy = -1;
clock_t BombEnemySpawnTime;
void BombEnemy_Full()
{
	BombEnemy_list = (BOMB_ENEMY*)realloc(BombEnemy_list, 2 * (BombEnemyarrsize) * sizeof(BOMB_ENEMY));
	BombEnemyarrsize *= 2;
}
void BombEnemy_push_back(BOMB_ENEMY item)
{
	if (lastofBombEnemy >= BombEnemyarrsize - 1)
		BombEnemy_Full();
	BombEnemy_list[++lastofBombEnemy] = item;
	++BombEnemyIndex;
}
void BombEnemy_Delete(int index)
{
	for (int i = index; i < BombEnemyIndex; ++i)
	{
		BombEnemy_list[i] = BombEnemy_list[i + 1];
	}
	--BombEnemyIndex;
	--lastofBombEnemy;
}

typedef struct _SHOOTENEMY
{
	int x;
	int y;
	int Life;
	int MoveTime;
	int AppearTime;
	int MoveOldTime;
	int FireTime;
	int OldFireTime;
	STATE State;

} SHOOT_ENEMY;
SHOOT_ENEMY *ShootEnemy_list;
int ShootEnemyIndex = 0;
int ShootEnemyarrsize = 1;
int lastofShootEnemy = -1;
clock_t ShootEnemySpawnTime;
void ShootEnemy_Full()
{
	ShootEnemy_list = (SHOOT_ENEMY*)realloc(ShootEnemy_list, 2 * (ShootEnemyarrsize) * sizeof(SHOOT_ENEMY));
	ShootEnemyarrsize *= 2;
}
void BombEnemy_push_back(SHOOT_ENEMY item)
{
	if (lastofShootEnemy >= ShootEnemyarrsize - 1)
		ShootEnemy_Full();
	ShootEnemy_list[++lastofShootEnemy] = item;
	++ShootEnemyIndex;
}
void ShootEnemy_Delete(int index)
{
	for (int i = index; i < ShootEnemyIndex; ++i)
	{
		ShootEnemy_list[i] = ShootEnemy_list[i + 1];
	}
	--ShootEnemyIndex;
	--lastofShootEnemy;
}


typedef struct _TURRET
{
	int x;
	int y;
	int FireTime;
	int OldFireTime;
	int Status;
	int TurretPower;
	int TurretSpeed;

} TURRET;
TURRET Turret_arr[10];

void TurretInstall(int index)
{
	if(Turret_arr[index].Status!=1)
		Turret_arr[index].Status = 1;
}

void TurretShoot(int passtime)
{
	//clock_t curtime = clock();
	for (int i = 0; i < 10; ++i)
	{
		if (Turret_arr[i].Status != 1) continue;
		if (passtime - Turret_arr[i].OldFireTime >= Turret_arr[i].FireTime)
		{
			BULLET temp;
			temp.Direct = RIGHT;
			temp.x = Turret_arr[i].x;
			temp.y = Turret_arr[i].y;
			temp.Life = 1;
			Turret_arr[i].OldFireTime = temp.MoveTime = passtime;
			temp.Power = Turret_arr[i].TurretPower;
			Bullet_push_back(temp);
		}
	}
}

unsigned int StartTime;
int Score;
bool TurretUI;
bool UpgradeUI;
bool IsTurretUpGradeUI;

void UpgradeTurret(int n,int index)
{
	IsTurretUpGradeUI = true;
	if (n == 1)
	{
		Turret_arr[index].TurretPower += 1;
	}
	else if (n == 2)
	{
		Turret_arr[index].FireTime -= 500;
	}
}
void Upgrade(int index)
{
	switch (index)
	{
	case 0:
		player.GunPower++;
		break;
	case 1:
		UpgradeTurret(index,TurretUpgradeSelect);
		break;
	case 2:
		UpgradeTurret(index,TurretUpgradeSelect);
		break;
	}
}
void Init()
{
	player.x = 1;
	player.y = 10;
	PlayerBullet = (BULLET*)malloc(sizeof(BULLET));
	Enemy_list = (ENEMY*)malloc(sizeof(ENEMY));
	BombEnemy_list = (BOMB_ENEMY*)malloc(sizeof(BOMB_ENEMY));
	ShootEnemy_list = (SHOOT_ENEMY*)malloc(sizeof(SHOOT_ENEMY));
}

void PlayerMove()
{
	int key;
	clock_t curtime;
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
				BULLET temp;
				temp.Direct = RIGHT;
				temp.x = player.x;
				temp.y = player.y;
				temp.Life = 1;
				player.OldFireTime = temp.MoveTime = curtime;
				temp.Power = player.GunPower;
				Bullet_push_back(temp);
			}
			break;
		}
	}
}

void EnemySpawn(int passtime)
{
	if (EnemySpawnTime + 3600 <= passtime)
	{
		ENEMY temp;
		temp.ApperTime = passtime;
		temp.Direct = LEFT;
		temp.MoveTime = 300;
		temp.x = MAP_COL - 3;
		temp.y = (rand()) % 19 + 5;
		temp.Life = 3+(Round-1);
		temp.State = RUN;
		Enemy_push_back(temp);
		EnemySpawnTime = passtime;
	}

	
	if (BombEnemySpawnTime + 7200 <= passtime)
	{
		BOMB_ENEMY temp;
		temp.AppearTime = passtime;
		temp.MoveTime = 20;
		temp.x = MAP_COL - 5;
		temp.y = (rand()) % 19 + 5;
		temp.Life = 1+(Round-1);
		temp.State = RUN;
		BombEnemy_push_back(temp);
		BombEnemySpawnTime = passtime;
	}
}

void EnemyMove(int curtime)
{
	for (int i = 0; i < EnemyIndex; ++i)
	{
		if (Enemy_list[i].Life >= 1)
		{
			if (curtime - Enemy_list[i].OldTime > Enemy_list[i].MoveTime && Enemy_list[i].x>7)
			{
				Enemy_list[i].x--;
				Enemy_list[i].OldTime = curtime;
			}
			else if(Enemy_list[i].x==7)
			{
				WallLife -= 10;
			}
		}
	}
	for (int i = 0; i < BombEnemyIndex; ++i)
	{
		if (BombEnemy_list[i].State == RUN)
		{
			if (curtime - BombEnemy_list[i].OldTime > BombEnemy_list[i].MoveTime && BombEnemy_list[i].x>7)
			{
				BombEnemy_list[i].x--;
				BombEnemy_list[i].OldTime = curtime;
			}
			else if(BombEnemy_list[i].x==7)
			{
				BombEnemy_list[i].Life = 0;
				BombEnemy_list[i].State = DEAD;
				WallLife -= 100;
			}
		}
	}
}

void EnemyCollision()
{
	for (int i = 0; i < EnemyIndex; ++i)
	{
		if (Enemy_list[i].Life < 1) continue;
		for (int j = 0; j < BulletSize; ++j)
		{
			if (PlayerBullet[j].Life == 1)
			{
				if ((Enemy_list[i].x == PlayerBullet[j].x*2 || Enemy_list[i].x+1 == PlayerBullet[j].x*2 || Enemy_list[i].x+2 == PlayerBullet[j].x*2) &&
					(Enemy_list[i].y == PlayerBullet[j].y || Enemy_list[i].y + 1 == PlayerBullet[j].y))
				{
					Enemy_list[i].Life -= PlayerBullet[j].Power;
					Enemy_list[i].x++;
					Enemy_list[i].State = HIT;
					if (Enemy_list[i].Life < 1)
					{
						//PlayerBullet[j].Life = 0;
						Enemy_list[i].State = DEAD;
					}
					Bullet_Delete(j);
					break;
				}
			}
		}
	}
	for (int i = 0; i < BombEnemyIndex; ++i)
	{
		if (BombEnemy_list[i].State != RUN) continue;
		for (int j = 0; j < BulletSize; ++j)
		{
			if (PlayerBullet[j].Life == 1)
			{
				if ((BombEnemy_list[i].x == PlayerBullet[j].x * 2 || BombEnemy_list[i].x+1 == PlayerBullet[j].x * 2 || BombEnemy_list[i].x+2 == PlayerBullet[j].x * 2) &&
					(BombEnemy_list[i].y == PlayerBullet[j].y || BombEnemy_list[i].y+1 == PlayerBullet[j].y))
				{
					BombEnemy_list[i].Life -= PlayerBullet[j].Power;
					BombEnemy_list[i].x++;
					if (BombEnemy_list[i].Life < 1)
					{
						//PlayerBullet[j].Life = 0;
						BombEnemy_list[i].State = DEAD;
					}
					Bullet_Delete(j);
					break;
				}
			}
		}
	}
}

void Update()
{
	int curtime = clock();
	int passtime=curtime;

	EnemySpawn(passtime);
	EnemyMove(curtime);
	TurretShoot(passtime);
	for (int i = 0; i < BulletSize; ++i)
	{
		if (PlayerBullet[i].Life >= 1)
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
				Bullet_Delete(i);
			}
		}
	}
}
void RenderBasicUI()
{
	char str[100];
	char Time[20];
	char strLife[20];
	char strScore[50];
	char strRound[40];
	sprintf_s(strScore, "SCORE : %d", Score);
	sprintf_s(strLife, "LIFE : %d", WallLife);
	sprintf_s(Time, "TIME : %.0lf", RoundTime);
	sprintf_s(strRound, "ROUND : %d", Round);
	ScreenPrint(50, 1, strScore);
	ScreenPrint(10, 3, strLife);
	ScreenPrint(50, 3, Time);
	ScreenPrint(90, 3, strRound);
	sprintf_s(str, "%s 상태 %d %d", pState[player.direct], player.x, player.y);
	ScreenPrint(10, 20, str);
}

void RenderGameUI()
{
	char strEnemy[10];
	char strBombEnemy[10];
	ScreenPrint(player.x, player.y - 1, " o");
	ScreenPrint(player.x, player.y, "()┏");
	ScreenPrint(player.x, player.y + 1, "|_");

	for (int i = 0; i < BulletSize; ++i)
	{
		if (PlayerBullet[i].Life == 1)
		{
			ScreenPrint(PlayerBullet[i].x * 2, PlayerBullet[i].y, "-");
		}
	}
	for (int i = 0; i < EnemyIndex; ++i)
	{
		if (Enemy_list[i].State == RUN)
		{
			sprintf_s(strEnemy, "└ 0┐ %d", Enemy_list[i].Life);
			ScreenPrint(Enemy_list[i].x, Enemy_list[i].y, strEnemy);
			ScreenPrint(Enemy_list[i].x, Enemy_list[i].y + 1, "┌ ㄴ");
		}
		else if (Enemy_list[i].State == HIT)
		{
			sprintf_s(strEnemy, "!└ 0┘ %d", Enemy_list[i].Life);
			ScreenPrint(Enemy_list[i].x, Enemy_list[i].y, strEnemy);
			ScreenPrint(Enemy_list[i].x, Enemy_list[i].y + 1, "┌ ㄴ");
		}
		else if (Enemy_list[i].State == DEAD)
		{
			ScreenPrint(Enemy_list[i].x, Enemy_list[i].y, "O T L");
		}
	}

	for (int i = 0; i < BombEnemyIndex; ++i)
	{
		if (BombEnemy_list[i].State == RUN)
		{
			sprintf_s(strBombEnemy, "＼B/ %d", BombEnemy_list[i].Life);
			ScreenPrint(BombEnemy_list[i].x, BombEnemy_list[i].y, strBombEnemy);
			ScreenPrint(BombEnemy_list[i].x, BombEnemy_list[i].y + 1, " ┌ ㄴ=3");
		}
		else if (BombEnemy_list[i].State == DEAD)
		{
			ScreenPrint(BombEnemy_list[i].x, BombEnemy_list[i].y, "★★");
			ScreenPrint(BombEnemy_list[i].x, BombEnemy_list[i].y + 1, "★★");
		}
	}
}

void TurretInstallUI()
{
	char strTurret[50];
	sprintf_s(strTurret, "터렛을 설치할 위치를 선택해주세요 : %d", TurretSelect);
	ScreenPrint(20, 28, strTurret);
}

void TurretUpgradeUI()
{
	char strTurret[50];
	sprintf_s(strTurret, "업그레이드 할 터렛 위치를 선택해주세요 : %d", TurretUpgradeSelect);
	ScreenPrint(20, 28, strTurret);
}


void UpgradeRenderUI()
{
	char strUpgrade[100];
	if (UpgradeSelect == 0)
	{
		sprintf_s(strUpgrade, "[1.플레이어 위력 : 100] 2.터렛 위력 3.터렛 발사 시간");
	}
	if (UpgradeSelect == 1)
	{
		sprintf_s(strUpgrade, "1.플레이어 위력 [2.터렛 위력 : 200] 3.터렛 발사 시간");
	}
	if (UpgradeSelect == 2)
	{
		sprintf_s(strUpgrade, "1.플레이어 위력 2.터렛 위력 [3.터렛 발사 시간 : 200]");
	}
	ScreenPrint(20, 28, strUpgrade);
}
void RenderRepairUI()
{
	if (!TurretUI && !UpgradeUI && !IsTurretUpGradeUI)
	{
		if (MenuSelect == 0)
		{
			ScreenPrint(20, 28, "[1.벽 수리 : 100] 2.터렛 설치 3.업그레이드 4.디펜스 시작");
		}
		else if (MenuSelect == 1)
		{
			ScreenPrint(20, 28, "1.벽 수리 [2.터렛 설치 : 200] 3.업그레이드 4.디펜스 시작");
		}
		else if (MenuSelect == 2)
		{
			ScreenPrint(20, 28, "1.벽 수리 2.터렛 설치 [3.업그레이드] 4.디펜스 시작");
		}
		else if (MenuSelect == 3)
		{
			ScreenPrint(20, 28, "1.벽 수리 2.터렛 설치 3.업그레이드 [4.디펜스 시작]");
		}
	}
	else if (TurretUI)
	{
		TurretInstallUI();
	}
	else if (UpgradeUI)
	{
		UpgradeRenderUI();
	}
	else if (IsTurretUpGradeUI)
	{
		TurretUpgradeUI();
	}
}
void Render()
{
	ScreenClear();
	RenderBasicUI();
	
	for (int i = 0; i < MAP_COL; ++i)
	{
		ScreenPrint(i, 5, "=");
	}
	for (int i = 0; i < MAP_COL; ++i)
	{
		ScreenPrint(i, 25, "=");
	}
	if (phase == GAME)
	{
		RenderGameUI();
	}
	if (phase == REPAIR)
	{
		RenderRepairUI();
	}
	for (int i = 6; i < 25; ++i)
	{
		ScreenPrint(4, i, "| |");
	}
	for (int i = 6; i < 25; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			if (Turret_arr[j].Status == 1)
			{
				ScreenPrint(Turret_arr[j].x, Turret_arr[j].y, ">");
			}
		}
	}
	ScreenFlipping();
}

void EndRender()
{

}

void DeadErase()
{
	for (int i = 0; i < EnemyIndex; ++i)
	{
		if (Enemy_list[i].State == DEAD)
		{
			Enemy_Delete(i);
			Score += 10;
		}
		else if (Enemy_list[i].State == HIT)
			Enemy_list[i].State = RUN;
	}
	for (int i = 0; i < BombEnemyIndex; ++i)
	{
		if (BombEnemy_list[i].State == DEAD)
		{
			BombEnemy_Delete(i);
			Score += 20;
		}
	}
}

void Release()
{
	free(Enemy_list);
	EnemyIndex = 0;
	lastofEnemy = -1;
	Enemyarrsize = 1;

	free(BombEnemy_list);
	BombEnemyIndex = 0;
	lastofBombEnemy = -1;
	BombEnemyarrsize = 1;

	free(PlayerBullet);
	Bulletarrsize = 1;
	BulletSize = 0;
	lastofBullet = -1;

	free(ShootEnemy_list);
	ShootEnemyIndex = 0;
	lastofShootEnemy = -1;
	ShootEnemyarrsize = 1;

}
void GamePhase()
{
	StartTime = clock();
	Round++;
	while (1)
	{
		int curtime = clock();
		RoundTime = ROUND_TIME - ((curtime-StartTime)*0.001);
		if (RoundTime < 0)
		{
			phase = REPAIR;
			break;
		}
		PlayerMove();
		EnemyCollision();
		Update();
		Render();
		DeadErase();
	}
}

void ExcuteMenu(int select)
{
	switch (select)
	{
	case 0:
		if (WallLife != 1000)
		{
			WallLife += 200;
			if (WallLife > 1000)
				WallLife = 1000;
		}
		break;
	case 1:
		TurretUI = true;
		break;
	case 2:
		UpgradeUI = true;
		break;
	case 3:
		phase = GAME;
		break;
	}
}

void RepairMenuMover()
{
	int key;
	clock_t curtime;
	if (_kbhit())
	{
		key = _getch();
		curtime = clock();

		switch (key)
		{
		case 77:
			if (TurretUI)
			{
				if (++TurretSelect > 9)
					TurretSelect = 0;
				if (Turret_arr[TurretSelect].Status == 1)
				{
					for (int i = TurretSelect+1; i < 10; ++i)
					{
						if (Turret_arr[i].Status == 0)
						{
							TurretSelect = i;
							break;
						}
						if (i == 9)
							i = 0;
					}
				}
			}
			else if (UpgradeUI)
			{
				UpgradeSelect++;
				if (UpgradeSelect > 2)
				{
					UpgradeSelect = 0;
				}
			}
			else if (IsTurretUpGradeUI)
			{
				if (++TurretUpgradeSelect > 9)
					TurretUpgradeSelect = 0;
				if (Turret_arr[TurretUpgradeSelect].Status != 1)
				{
					for (int i = TurretUpgradeSelect+1; i < 10; ++i)
					{
						if (Turret_arr[i].Status == 1)
						{
							TurretUpgradeSelect = i;
							break;
						}
						if (i == 9)
							i = -1;
					}
				}
			}
			else
			{
				MenuSelect++;
				if (MenuSelect > 3)
					MenuSelect = 0;
			}
			break;

		case 75:
			if (TurretUI)
			{
				if (--TurretSelect < 0)
					TurretSelect = 9;
				if (Turret_arr[TurretSelect].Status == 1)
				{
					for (int i = TurretSelect; i >=0 ; --i)
					{
						if (Turret_arr[i].Status == 0)
						{
							TurretSelect = i;
							break;
						}
						if (i == 0)
							i = 10;
					}
				}
			}
			else if (UpgradeUI)
			{
				UpgradeSelect--;
				if (UpgradeSelect < 0)
				{
					UpgradeSelect = 2;
				}
			}
			else if (IsTurretUpGradeUI)
			{
				if (--TurretUpgradeSelect < 0)
					TurretUpgradeSelect = 9;
				if (Turret_arr[TurretUpgradeSelect].Status != 1)
				{
					for (int i = TurretUpgradeSelect; i >= 0; --i)
					{
						if (Turret_arr[i].Status == 1)
						{
							TurretUpgradeSelect = i;
							break;
						}
						if (i == 0)
							i = 10;
					}
				}
			}
			else
			{
				MenuSelect--;
				if (MenuSelect < 0)
					MenuSelect = 3;
			}
			break;
		case 32:
			if (TurretUI)
			{
				TurretInstall(TurretSelect);
				TurretUI = false;
				for (int i = 0; i < 10; ++i)
				{
					if (Turret_arr[i].Status == 0)
					{
						TurretSelect = FirstTurretSelect = i;
						break;
					}
				}
				for (int i = 0; i < 10; ++i)
				{
					if (Turret_arr[i].Status == 1)
					{
						TurretUpgradeSelect = FirstTurretUpgradeSelect = i;
						break;
					}
				}
				break;
			}
			else if (UpgradeUI)
			{
				Upgrade(UpgradeSelect);
				UpgradeUI = false;
				break;
			}
			else if (IsTurretUpGradeUI)
			{
				//UpgradeTurret(UpgradeSelect);
				IsTurretUpGradeUI = false;
				break;
			}
			else 
			{
				ExcuteMenu(MenuSelect);
				break;
			}
		case 27:
			TurretUI = false;
			UpgradeUI = false;
			IsTurretUpGradeUI = false;
			break;
		}
	}
}
void RepairPhase()
{
	while (phase == REPAIR)
	{
		Render();
		RepairMenuMover();
	}
}

void EndPhase()
{
	EndRender();
}
int main(void)
{
	srand(unsigned int(time(NULL)));
	ScreenInit();
	Init();
	player.GunPower = 1;
	int j = 0;
	for (int i = 0; i < 10; i++,j+=2)
	{
		Turret_arr[i].x = 5;
		Turret_arr[i].y = 6+j;
		Turret_arr[i].Status = 0;
		Turret_arr[i].FireTime = 5000;
		Turret_arr[i].TurretPower = 1;
	}
	while (1)
	{
		if (phase == GAME)
		{
			GamePhase();
		}
 		Release();
		Init();
		if (phase == REPAIR)
		{
			RepairPhase();
		}
		if (phase == END)
		{
			EndPhase();
			break;
		}
 	}
	ScreenRelease();
	Release();
	return 0;
}
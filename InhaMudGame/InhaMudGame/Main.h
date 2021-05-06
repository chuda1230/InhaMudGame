#pragma once
int WallLife = 1000;
int Round;
double RoundTime = 0;
typedef enum _DIRECT { UP, DOWN, LEFT, RIGHT } DIRECT;
typedef enum _STATE { RUN, HIT, DEAD } STATE;
typedef enum _PHASE { TITLE,GAME, REPAIR, END } PHASE;
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


typedef struct _Bullet
{
	int x, y;
	int Life;
	DIRECT Direct;
	int MoveTime;
	int Power;

}BULLET;

BULLET *PlayerBullet;
int Bulletarrsize = 1;
int BulletSize = 0;
int lastofBullet = -1;

typedef struct _EnemyBullet
{
	int x, y;
	int Life;
	DIRECT Direct;
	int MoveTime;
	int Power;

}ENEMY_BULLET;

ENEMY_BULLET *EnemyBullet;
int EnemyBulletarrsize = 1;
int EnemyBulletSize = 0;
int lastofEnemyBullet = -1;


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

typedef struct _SHOOTENEMY
{
	int x;
	int y;
	int Life;
	int MoveTime;
	int AppearTime;
	int OldTime;
	int FireTime;
	int OldFireTime;
	int GunPower;
	STATE State;

} SHOOT_ENEMY;
SHOOT_ENEMY *ShootEnemy_list;
int ShootEnemyIndex = 0;
int ShootEnemyarrsize = 1;
int lastofShootEnemy = -1;
clock_t ShootEnemySpawnTime;



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


unsigned int StartTime;
int Score;

//UI°ü·Ã
bool TurretUI;
bool UpgradeUI;
bool IsTurretUpGradeUI;
int MenuSelect = 0;
int TurretSelect = 0;
int UpgradeSelect = 0;
int TurretUpgradeSelect = 0;
int FirstTurretSelect = 0;
int FirstTurretUpgradeSelect = 0;

int PGPrice=50;
int TurPrice=100;
int TGPrice=150;
int TSPirce=150;

void Init();

void EnemySpawn(int passtime);
void EnemyMove(int curtime);
void EnemyCollision();

void EnemyShoot(int passtime);

void Render();
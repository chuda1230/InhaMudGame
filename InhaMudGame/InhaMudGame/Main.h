#pragma once
int WallLife = 1000;	//���� �����
int Round;				//���� ����
double RoundTime = 0;	//���� �����ð�
typedef enum _DIRECT { UP, DOWN, LEFT, RIGHT } DIRECT;	//������Ʈ���� ����
typedef enum _STATE { RUN, HIT, DEAD } STATE;	//������ ����
typedef enum _PHASE { TITLE,GAME, REPAIR, END } PHASE;	//������ ������
PHASE phase;			//������ �ܰ�
unsigned int StartTime;	//���۽ð�
int Score;				//����
bool IsReload;			//������ ����
clock_t ReloadStartTime;	//������ ���۽ð�

//UI����
bool TurretUI;
bool UpgradeUI;
bool IsTurretUpGradeUI;
bool IsScoreLessUI;
int MenuSelect = 0;
int TurretSelect = 0;
int UpgradeSelect = 0;
int TurretUpgradeSelect = 0;
int FirstTurretSelect = 0;
int FirstTurretUpgradeSelect = 0;

int PGPrice = 50;
int PMPrice = 50;
int TurPrice = 100;
int TUPrice;
//�÷��̾�
typedef struct _Player	
{
	int x, y;			//��ġ
	int FireTime;		//�߻� �ð�
	int OldFireTime;	//���߻� �ð�
	DIRECT direct;		
	int GunPower;		//�ѱ�����
	int Magazine;		//��ź ��
	int FireCount;		//�߻�Ƚ��
} Player;
Player player;

//�÷��̾��Ѿ�
typedef struct _Bullet	
{
	int x, y;			//��ġ
	int Life;			//�Ѿ��� ���翩��
	DIRECT Direct;		
	int MoveTime;		//�̵��ð�
	int Power;			//������

}BULLET;

typedef struct _EnemyBullet	//���� �Ѿ�
{
	int x, y;				//��ġ
	int Life;				//���� �Ѿ� ���翩��
	int MoveTime;			//�̵��ð�
	int Power;				//������

}ENEMY_BULLET;

typedef struct _ENEMY	//�Ϲ� ����
{
	int x, y;			//��ġ
	int Life;			//����
	int Direct;			//����
	int MoveTime;		//�̵��� �ɸ��� �ð�
	int ApperTime;		//������ �ð�
	int OldTime;		//���� �̵��ߴ� �ð�
	STATE State;		//����
}ENEMY;

typedef struct _BOMBENEMY	//��ź ����
{
	int x,y;			//��ġ
	int Life;			//����
	int MoveTime;		//�̵��� �ɸ��� �ð�
	int AppearTime;		//������ �ð�
	int OldTime;		//���� �̵��ߴ� �ð�
	STATE State;		//����
} BOMB_ENEMY;

typedef struct _SHOOTENEMY	//���� ����
{
	int x,y;			//��ġ
	int Life;			//����
	int MoveTime;		//�̵��� �ɸ��� �ð�
	int AppearTime;		//������ �ð�
	int OldTime;		//���� �̵��ߴ� �ð�
	int FireTime;		//�߻�ð�
	int OldFireTime;	//���� �߻��� �ð�
	int GunPower;		//�ѱ� ����
	STATE State;		//����

} SHOOT_ENEMY;
BULLET *PlayerBullet;	
int Bulletarrsize = 1;	//�÷��̾��Ѿ� ����Ʈũ��
int BulletSize = 0;		//�÷��̾��Ѿ� ����
int lastofBullet = -1;	//�÷��̾��Ѿ� �� TOP();

ENEMY_BULLET *EnemyBullet;	//�����Ѿ� ����Ʈ
int EnemyBulletarrsize = 1;	//�����Ѿ� ����Ʈ ũ��
int EnemyBulletSize = 0;	//�����Ѿ� ����
int lastofEnemyBullet = -1;	//�����Ѿ��� TOP();

ENEMY *Enemy_list;		//�Ϲ� ��������Ʈ
int EnemyIndex = 0;		//�Ϲ����� ������
int Enemyarrsize = 1;	//�Ϲ����� ����Ʈ ũ��
int lastofEnemy = -1;	//�Ϲ������� TOP()
clock_t EnemySpawnTime;	//�Ϲ����� ��ȯ�ð�

BOMB_ENEMY *BombEnemy_list;
int BombEnemyIndex = 0;
int BombEnemyarrsize = 1;
int lastofBombEnemy = -1;
clock_t BombEnemySpawnTime;

SHOOT_ENEMY *ShootEnemy_list;
int ShootEnemyIndex = 0;
int ShootEnemyarrsize = 1;
int lastofShootEnemy = -1;
clock_t ShootEnemySpawnTime;

//�ͷ�
typedef struct _TURRET
{
	int x,y;			//��ġ
	int FireTime;		//�߽ýð�
	int OldFireTime;	//�����߻�ð�
	int Status;			//����
	int TurretPower;	//�ͷ����¾��׷��̵�
	int TurretSpeed;	//�ͷ����ǵ���׷��̵�
	int TGPrice;
	int TSPrice;

} TURRET;
TURRET Turret_arr[10];	//�ͷ� �迭

//����
void Init();	//���� �ʱ�ȭ
void Release();	//����Ʈ ������
void Render();	//�ܼ�â ����
void RenderBasicUI(); //�⺻���� UI����
void Update();	//���ӻ��� ������Ʈ

//������Ʈ ����
//Full : ����Ʈ�� �� ������ �˻��ϰ� realloc�� ����Ʈ����
//push_back : ����Ʈ�� ������ �߰�
//Delete : ����Ʈ���� ������ ����
void Bullet_Full();					
void Bullet_push_back(BULLET item);
void Bullet_Delete(int index);
void EnemyBullet_Full();
void EnemyBullet_push_back(ENEMY_BULLET item);
void EnemyBullet_Delete(int index);
void Enemy_Full();
void Enemy_push_back(ENEMY item);
void Enemy_Delete(int index);
void BombEnemy_Full();
void BombEnemy_push_back(BOMB_ENEMY item);
void BombEnemy_Delete(int index);
void ShootEnemy_Full();
void ShootEnemy_push_back(SHOOT_ENEMY item);
void ShootEnemy_Delete(int index);

//Ÿ��Ʋ ������
void TitlePhase();
void TitleRender();				//Ÿ��Ʋ ����

//����������
void EndPhase();
void EndRender();	//���ӿ���ȭ�� ����

//����������
void GamePhase();
void PlayerMove();				//�÷��̾� ������
void EnemySpawn(int passtime);	//���� ��ȯ
void EnemyMove(int curtime);	//���� �̵�
void EnemyCollision();			//���� �浹ó��
void EnemyShoot(int passtime);	//���Ÿ� ���� ���
void DeadErase();				//DEADó���� ���� ����� �����߰�
void TurretShoot(int passtime);	//�ͷ� ���
void RenderGameUI();			//��������� �ʿ��� ������ƮƲ ����

//������������
void RepairPhase();
void RepairMenuMover();				//������ �޴� �̵�
void ExcuteMenu(int index);					//�޴� ����
void TurretInstall(int index);		//index��ġ�� �ͷ� ��ġ
void RenderRepairUI();				//������������ �޴��� ����
void UpgradeRenderUI();				//���׷��̵� �޴� ����
void Upgrade(int index);			//���׷��̵� �� ������
void TurretUpgradeUI();				//�ͷ����׷��̵� �޴� ����
void UpgradeTurret(int n,int index);//n�� ���׷��̵带 index�ͷ��� ����	
void TurretInstallUI();				//�ͷ��ν��� �޴� ����


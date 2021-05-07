#pragma once
int WallLife = 1000;	//벽의 생명력
int Round;				//현재 라운드
double RoundTime = 0;	//라운드 남은시간
typedef enum _DIRECT { UP, DOWN, LEFT, RIGHT } DIRECT;	//오브젝트들의 방향
typedef enum _STATE { RUN, HIT, DEAD } STATE;	//적들의 상태
typedef enum _PHASE { TITLE,GAME, REPAIR, END } PHASE;	//게임의 페이즈
PHASE phase;			//게임의 단계
unsigned int StartTime;	//시작시간
int Score;				//점수
bool IsReload;			//재장전 여부
clock_t ReloadStartTime;	//재장전 시작시간

//UI관련
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
//플레이어
typedef struct _Player	
{
	int x, y;			//위치
	int FireTime;		//발사 시간
	int OldFireTime;	//전발사 시간
	DIRECT direct;		
	int GunPower;		//총기위력
	int Magazine;		//장탄 수
	int FireCount;		//발사횟수
} Player;
Player player;

//플레이어총알
typedef struct _Bullet	
{
	int x, y;			//위치
	int Life;			//총알의 존재여부
	DIRECT Direct;		
	int MoveTime;		//이동시간
	int Power;			//데미지

}BULLET;

typedef struct _EnemyBullet	//적군 총알
{
	int x, y;				//위치
	int Life;				//적군 총알 존재여부
	int MoveTime;			//이동시간
	int Power;				//데미지

}ENEMY_BULLET;

typedef struct _ENEMY	//일반 적군
{
	int x, y;			//위치
	int Life;			//생명
	int Direct;			//방향
	int MoveTime;		//이동에 걸리는 시간
	int ApperTime;		//스폰된 시간
	int OldTime;		//전에 이동했던 시간
	STATE State;		//상태
}ENEMY;

typedef struct _BOMBENEMY	//폭탄 적군
{
	int x,y;			//위치
	int Life;			//생명
	int MoveTime;		//이동에 걸리는 시간
	int AppearTime;		//스폰된 시간
	int OldTime;		//전에 이동했던 시간
	STATE State;		//상태
} BOMB_ENEMY;

typedef struct _SHOOTENEMY	//슈팅 적군
{
	int x,y;			//위치
	int Life;			//생명
	int MoveTime;		//이동에 걸리는 시간
	int AppearTime;		//스폰된 시간
	int OldTime;		//전에 이동했던 시간
	int FireTime;		//발사시간
	int OldFireTime;	//전에 발사한 시간
	int GunPower;		//총기 위력
	STATE State;		//상태

} SHOOT_ENEMY;
BULLET *PlayerBullet;	
int Bulletarrsize = 1;	//플레이어총알 리스트크기
int BulletSize = 0;		//플레이어총알 갯수
int lastofBullet = -1;	//플레이어총알 의 TOP();

ENEMY_BULLET *EnemyBullet;	//적군총알 리스트
int EnemyBulletarrsize = 1;	//적군총알 리스트 크기
int EnemyBulletSize = 0;	//적군총알 갯수
int lastofEnemyBullet = -1;	//적군총알의 TOP();

ENEMY *Enemy_list;		//일반 적군리스트
int EnemyIndex = 0;		//일반적군 사이즈
int Enemyarrsize = 1;	//일반적군 리스트 크기
int lastofEnemy = -1;	//일반적군의 TOP()
clock_t EnemySpawnTime;	//일반적군 소환시간

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

//터렛
typedef struct _TURRET
{
	int x,y;			//위치
	int FireTime;		//발시시간
	int OldFireTime;	//이전발사시간
	int Status;			//상태
	int TurretPower;	//터렛위력업그레이드
	int TurretSpeed;	//터렛스피드업그레이드
	int TGPrice;
	int TSPrice;

} TURRET;
TURRET Turret_arr[10];	//터렛 배열

//메인
void Init();	//변수 초기화
void Release();	//리스트 릴리즈
void Render();	//콘솔창 렌더
void RenderBasicUI(); //기본적인 UI렌더
void Update();	//게임상태 업데이트

//오브젝트 관리
//Full : 리스트가 다 찻는지 검사하고 realloc로 리스트증가
//push_back : 리스트에 아이템 추가
//Delete : 리스트에서 아이템 삭제
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

//타이틀 페이즈
void TitlePhase();
void TitleRender();				//타이틀 렌더

//엔드페이즈
void EndPhase();
void EndRender();	//게임오버화면 렌더

//게임페이즈
void GamePhase();
void PlayerMove();				//플레이어 움직임
void EnemySpawn(int passtime);	//적군 소환
void EnemyMove(int curtime);	//적군 이동
void EnemyCollision();			//적군 충돌처리
void EnemyShoot(int passtime);	//원거리 적군 사격
void DeadErase();				//DEAD처리된 적군 지우고 점수추가
void TurretShoot(int passtime);	//터렛 사격
void RenderGameUI();			//게임페이즈에 필요한 오브젝트틀 렌더

//재정비페이즈
void RepairPhase();
void RepairMenuMover();				//재정비 메뉴 이동
void ExcuteMenu(int index);					//메뉴 실행
void TurretInstall(int index);		//index위치에 터렛 설치
void RenderRepairUI();				//재정비페이즈 메뉴들 렌더
void UpgradeRenderUI();				//업그레이드 메뉴 렌더
void Upgrade(int index);			//업그레이드 및 벽수리
void TurretUpgradeUI();				//터렛업그레이드 메뉴 렌더
void UpgradeTurret(int n,int index);//n번 업그레이드를 index터렛에 시행	
void TurretInstallUI();				//터렛인스톨 메뉴 렌더


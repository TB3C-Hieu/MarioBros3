#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#include "debug.h"

#define MARIO_WALKING_SPEED		0.1f
#define MARIO_RUNNING_SPEED		0.2f

#define MARIO_ACCEL_WALK_X	0.0005f
#define MARIO_ACCEL_RUN_X	0.0007f

#define MARIO_JUMP_SPEED_Y		0.5f
#define MARIO_JUMP_RUN_SPEED_Y	0.6f

#define MARIO_GRAVITY			0.002f

#define MARIO_JUMP_DEFLECT_SPEED  0.4f

#define MARIO_STATE_DIE				-10
#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200

#define MARIO_STATE_JUMP			300
#define MARIO_STATE_RELEASE_JUMP    301

#define MARIO_STATE_RUNNING_RIGHT	400
#define MARIO_STATE_RUNNING_LEFT	500

#define MARIO_STATE_SIT				600
#define MARIO_STATE_SIT_RELEASE		601

#define MARIO_STATE_SHOOT 602

#pragma region ANIMATION_ID


//RACOON
#define ID_ANI_RACOONMARIO_IDLE_RIGHT 65000
#define ID_ANI_RACOONMARIO_IDLE_LEFT 65100
			   
#define ID_ANI_RACOONMARIO_WALKING_RIGHT 65200
#define ID_ANI_RACOONMARIO_WALKING_LEFT 65300
			   
#define ID_ANI_RACOONMARIO_RUNNING_RIGHT 65400
#define ID_ANI_RACOONMARIO_RUNNING_LEFT 65500
			   
#define ID_ANI_RACOONMARIO_JUMP_WALK_RIGHT 65600
#define ID_ANI_RACOONMARIO_JUMP_WALK_LEFT 65700
			   
#define ID_ANI_RACOONMARIO_JUMP_RUN_RIGHT	65800
#define ID_ANI_RACOONMARIO_JUMP_RUN_LEFT 65900
			   
#define ID_ANI_RACOONMARIO_SIT_RIGHT 66000
#define ID_ANI_RACOONMARIO_SIT_LEFT 66100
			   
#define ID_ANI_RACOONMARIO_BRACE_RIGHT 66200
#define ID_ANI_RACOONMARIO_BRACE_LEFT 66300

#define ID_ANI_RACOONMARIO_SLOWFALL_RIGHT 66400
#define ID_ANI_RACOONMARIO_SLOWFALL_LEFT 66500

#define ID_ANI_RACOONMARIO_TAILATTACK_RIGHT 66600
			   
#define ID_ANI_RACOONMARIO_DIE 999

//FIRE
#define ID_ANI_FIREMARIO_IDLE_RIGHT 62100
#define ID_ANI_FIREMARIO_IDLE_LEFT 62200

#define ID_ANI_FIREMARIO_WALKING_RIGHT 62300
#define ID_ANI_FIREMARIO_WALKING_LEFT 62400
			   
#define ID_ANI_FIREMARIO_RUNNING_RIGHT 62500
#define ID_ANI_FIREMARIO_RUNNING_LEFT 62600
			   
#define ID_ANI_FIREMARIO_JUMP_WALK_RIGHT 62700
#define ID_ANI_FIREMARIO_JUMP_WALK_LEFT 62800
			   
#define ID_ANI_FIREMARIO_JUMP_RUN_RIGHT	62900
#define ID_ANI_FIREMARIO_JUMP_RUN_LEFT 63000
			   
#define ID_ANI_FIREMARIO_SIT_RIGHT 63100
#define ID_ANI_FIREMARIO_SIT_LEFT 63200
			   
#define ID_ANI_FIREMARIO_BRACE_RIGHT 63300
#define ID_ANI_FIREMARIO_BRACE_LEFT 63400
#define ID_ANI_FIREMARIO_SHOOT_LEFT 63500
#define ID_ANI_FIREMARIO_SHOOT_RIGHT 63600
			   
#define ID_ANI_FIREMARIO_DIE 999
//BIG
#define ID_ANI_MARIO_IDLE_RIGHT 400
#define ID_ANI_MARIO_IDLE_LEFT 401

#define ID_ANI_MARIO_WALKING_RIGHT 500
#define ID_ANI_MARIO_WALKING_LEFT 501

#define ID_ANI_MARIO_RUNNING_RIGHT 600
#define ID_ANI_MARIO_RUNNING_LEFT 601

#define ID_ANI_MARIO_JUMP_WALK_RIGHT 700
#define ID_ANI_MARIO_JUMP_WALK_LEFT 701

#define ID_ANI_MARIO_JUMP_RUN_RIGHT 800
#define ID_ANI_MARIO_JUMP_RUN_LEFT 801

#define ID_ANI_MARIO_SIT_RIGHT 900
#define ID_ANI_MARIO_SIT_LEFT 901

#define ID_ANI_MARIO_BRACE_RIGHT 1000
#define ID_ANI_MARIO_BRACE_LEFT 1001

#define ID_ANI_MARIO_DIE 999

// SMALL MARIO
#define ID_ANI_MARIO_SMALL_IDLE_RIGHT 1100
#define ID_ANI_MARIO_SMALL_IDLE_LEFT 1102

#define ID_ANI_MARIO_SMALL_WALKING_RIGHT 1200
#define ID_ANI_MARIO_SMALL_WALKING_LEFT 1201

#define ID_ANI_MARIO_SMALL_RUNNING_RIGHT 1300
#define ID_ANI_MARIO_SMALL_RUNNING_LEFT 1301

#define ID_ANI_MARIO_SMALL_BRACE_RIGHT 1400
#define ID_ANI_MARIO_SMALL_BRACE_LEFT 1401

#define ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT 1500
#define ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT 1501

#define ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT 1600
#define ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT 1601

#pragma endregion

#define GROUND_Y 160.0f




#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define	MARIO_LEVEL_FIRE	3
#define	MARIO_LEVEL_RACOON	4

#define MARIO_BIG_BBOX_WIDTH  14
#define MARIO_BIG_BBOX_HEIGHT 24
#define MARIO_BIG_SITTING_BBOX_WIDTH  14
#define MARIO_BIG_SITTING_BBOX_HEIGHT 16

#define MARIO_SIT_HEIGHT_ADJUST ((MARIO_BIG_BBOX_HEIGHT-MARIO_BIG_SITTING_BBOX_HEIGHT)/2)

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 12

#define MARIO_LIMIT_LEFT 0
#define MARIO_LIMIT_TOP -50
#define MARIO_UNTOUCHABLE_TIME 2500
#define MARIO_SLOW_TIME 300
#define MARIO_TAILATTACK_TIME 300
#define MARIO_MAX_FLY_DURATION 3000

class CMario : public CGameObject
{
	BOOLEAN isSitting;
	float maxVx;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 
	float height = 0;
	int level; 
	int untouchable; 
	int slow_falling;
	int flying;
	bool tail_attacking;
	bool attacked;
	ULONGLONG slow_timer;
	ULONGLONG fly_timer;
	ULONGLONG total_fly_timer;
	ULONGLONG tail_attack_timer;
	ULONGLONG untouchable_start;
	BOOLEAN isOnPlatform;
	int coin; 

	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopa(LPCOLLISIONEVENT e);
	void OnCollisionWithPlant(LPCOLLISIONEVENT e);
	void OnCollisionWithQBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithPButton(LPCOLLISIONEVENT e);
	void OnCollisionWithGPlatform(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);
	void OnCollisionWithPowerUp(LPCOLLISIONEVENT e);

	int GetAniIdBig();
	int GetAniIdSmall();
	int GetAniIdFire();
	int GetAniIdRacoon();

public:
	CMario(float x, float y) : CGameObject(x, y)
	{
		isSitting = false;
		maxVx = 0.0f;
		ax = 0.0f;
		ay = MARIO_GRAVITY; 
		slow_falling = false;
		flying = false;
		EntityTag = Tag::player;
		level = MARIO_LEVEL_BIG;
		untouchable = 0;
		untouchable_start = -1;
		slow_timer = -1;
		fly_timer = -1;
		tail_attack_timer = -1;
		total_fly_timer = 0;
		tail_attacking = false;
		attacked = false;
		isOnPlatform = false;
		coin = 0;
	}
	int GetDirection() { return nx; }
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);
	void SlowFall();
	int IsCollidable()
	{ 
		return (state != MARIO_STATE_DIE); 
	}
	void Shoot();
	int IsBlocking() { return (state != MARIO_STATE_DIE && untouchable==0); }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void LevelUp();
	void LevelDown();
	void SetLevel(int l);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};
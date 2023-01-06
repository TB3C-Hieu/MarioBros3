#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#include "debug.h"

#define TAIL_SPEED	0.2f
#define FIREBALL_BBOX_WIDTH  8
#define FIREBALL_BBOX_HEIGHT 8
#define TAIL_DISTANCE 16

class CRacoonTail : public CGameObject
{
	float ay;				// acceleration on y 
	float dir;
	float travel_dis;
	ULONGLONG destroy_timer;

public:
	CRacoonTail(float x, float y, float direction) : CGameObject(x, y)
	{
		dir = direction;
		ay = 0;
		travel_dis = 0;
		EntityTag = Tag::Damager;
		destroy_timer = GetTickCount64();
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();

	int IsCollidable()
	{
		return 1;
	}

	int IsBlocking() { return 0; }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnCollisionWithPlant(LPCOLLISIONEVENT e);
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopa(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithEatingPlant(LPCOLLISIONEVENT e);

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};
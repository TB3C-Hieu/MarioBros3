#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#include "debug.h"

#define FIREBALL_SPEED	0.2f
#define FIREBALL_DEFLECT_FORCE  0.3f
#define FIREBALL_BOUNCES 3
#define FIREBALL_GRAVITY 0.002f
#define FIREBALL_BBOX_WIDTH  8
#define FIREBALL_BBOX_HEIGHT 8
#define ID_ANI_FIREBALL 13000


class CFireball : public CGameObject
{
	float ay;				// acceleration on y 
	int bounces;
	float dir;

public:
	CFireball(float x, float y, float direction) : CGameObject(x, y)
	{
		ay = FIREBALL_GRAVITY;
		dir = direction;
		bounces = FIREBALL_BOUNCES;
		EntityTag = Tag::Damager;
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
	void OnCollisionWithEatingPlant(LPCOLLISIONEVENT e);
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopa(LPCOLLISIONEVENT e);

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};
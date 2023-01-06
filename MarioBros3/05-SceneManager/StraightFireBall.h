#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#include "debug.h"

#define FIREBALL_SPEED		0.05f
#define FIREBALL_FLY_TIME	2000f
#define FIREBALL_GRAVITY 0.002f
#define FIREBALL_BBOX_WIDTH  8
#define FIREBALL_BBOX_HEIGHT 8
#define ID_ANI_FIREBALL 13500


class CStraightFireball : public CGameObject
{
	float ay;				// acceleration on y 
	float direction;
	float aim = 1;

public:
	CStraightFireball(float x, float y, float dir, float aim_at) : CGameObject(x, y)
	{
		ay = FIREBALL_GRAVITY;
		direction = dir;
		aim = aim_at;
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

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};
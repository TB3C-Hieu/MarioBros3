#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_BRICK 10000

#define BRICK_WIDTH 16
#define BRICK_BBOX_WIDTH 16
#define BRICK_BBOX_HEIGHT 16

#define BRICK_STATE_BROKEN 100
#define BRICK_STATE_NORMAL 200

#define BRICK_BREAK_TIME 500
#define BRICK_MOVE_DISTANCE 16
class CBrick : public CGameObject {
protected:
	int is_blocking = 1;
	float distance_moved = 0;
	int is_collidable = 1;
	ULONGLONG break_start;
public:
	CBrick(float x, float y);
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	virtual int IsBlocking() { return is_blocking; }
	virtual int IsCollidable() { return is_collidable; }
	virtual void SetBlocking(int value) { this->is_blocking = value;}
	virtual void SetState(int state);
	void SwapWithCoin();
};
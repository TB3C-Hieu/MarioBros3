#pragma once
#include "GameObject.h"

#define KOOPA_GRAVITY 0.002f
#define KOOPA_WALKING_SPEED 0.05f
#define KOOPA_SHELL_SPEED 0.2f
#define KOOPA_JUMP_POWER 0.35f


#define KOOPA_BBOX_WIDTH 16
#define KOOPA_BBOX_HEIGHT 26
#define KOOPA_BBOX_HEIGHT_DIE 7

#define KOOPA_DIE_TIMEOUT 500
#define KOOPA_SHOT_TIMEOUT 1000

#define KOOPA_STATE_WALKING 100
#define KOOPA_STATE_DIE 200
#define KOOPA_STATE_SHOT 300
#define KOOPA_STATE_SHELL 400
#define KOOPA_STATE_SHELL_MOVING 500
#define KOOPA_STATE_SHELL_HOLDING 600

#define ID_ANI_KOOPA_WALKING 35100
#define ID_ANI_KOOPA_DIE 5001
#define ID_ANI_KOOPA_SHOT 35400
#define ID_ANI_KOOPA_SHELL 35200
#define ID_ANI_KOOPA_SHELL_MOVING 35300

class CKoopa : public CGameObject
{
protected:
	float ax;
	float ay;
	bool shot;
	float kick_dir =1;
	ULONGLONG die_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return !shot; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CKoopa(float x, float y);
	virtual void SetState(int state);
	void GotKick(float dir);
};
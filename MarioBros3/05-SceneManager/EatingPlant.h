#pragma once
#include "GameObject.h"

#define PLANT_BBOX_WIDTH 14
#define PLANT_BBOX_HEIGHT 28

#define ID_ANI_EATINGPLANT 37000


#define PLANT_STATE_MOVING_UP 100
#define PLANT_STATE_MOVING_DOWN 200
#define PLANT_STATE_SHOOTING 300
#define PLANT_STATE_WAITING 400

#define WAITING_WAIT_TIME 5000
#define SHOOT_WAIT_TIME 3000

#define PLANT_MOVING_DISTANCE 32
#define PLANT_MOVING_SPEED 0.02f

class CEatingPlant : public CGameObject
{
protected:
	ULONGLONG timer_start;
	float distance;
	int direction = -1;
	int plant_type = 0;
	float start_x, start_y;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }

public:
	CEatingPlant(float x, float y);
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	virtual void SetState(int state);
	void Destroy() { this->isDeleted = true; }
};
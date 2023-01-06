#include "EatingPlant.h"
#include "debug.h"
#include "PlayScene.h"
#include "Mario.h"
#include "Game.h"
#include "debug.h"
#include "StraightFireBall.h"
#define MARIO_INS (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer()
#define CURRENT_SCENE ((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())
CEatingPlant::CEatingPlant(float x, float y) :CGameObject(x, y)
{
	start_x = x;
	start_y = y;
	EntityTag = Tag::Enemy;
	SetState(PLANT_STATE_WAITING);
	distance = 0;
}

void CEatingPlant::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - PLANT_BBOX_WIDTH / 2;
	top = y - PLANT_BBOX_HEIGHT / 2;
	right = left + PLANT_BBOX_WIDTH;
	bottom = top + PLANT_BBOX_HEIGHT;
}


void CEatingPlant::OnNoCollision(DWORD dt)
{
}

void CEatingPlant::OnCollisionWith(LPCOLLISIONEVENT e)
{

}

void CEatingPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	y += vy * dt;
	distance += vy * dt;

	if (this->state == PLANT_STATE_WAITING)
	{
		if (GetTickCount64() - timer_start > WAITING_WAIT_TIME)
		{
			SetState(PLANT_STATE_MOVING_UP);
		}
	}
	else if (this->state == PLANT_STATE_MOVING_UP)
	{
		if (abs(distance) >= PLANT_MOVING_DISTANCE)
		{
			distance = 0;
			SetState(PLANT_STATE_SHOOTING);
		}
	}
	else if (this->state == PLANT_STATE_SHOOTING)
	{
		if (GetTickCount64() - timer_start > SHOOT_WAIT_TIME)
		{
			SetState(PLANT_STATE_MOVING_DOWN);
		}
	}
	else
	{
		if (abs(distance) >= PLANT_MOVING_DISTANCE)
		{
			distance = 0;
			SetState(PLANT_STATE_WAITING);
		}
	}


	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CEatingPlant::Render()
{

	int aniId = ID_ANI_EATINGPLANT;
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CEatingPlant::SetState(int state)
{

	switch (state)
	{
	case PLANT_STATE_MOVING_UP:
		vy = -PLANT_MOVING_SPEED;
		break;
	case PLANT_STATE_MOVING_DOWN:
		vy = PLANT_MOVING_SPEED;
		break;
	case PLANT_STATE_WAITING:
		vy = 0;
		break;
	case PLANT_STATE_SHOOTING:
		vy = 0;
		break;
	default:
		vy = 0;
		break;
	}
	timer_start = GetTickCount64();
	CGameObject::SetState(state);

}

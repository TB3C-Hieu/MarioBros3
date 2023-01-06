#include "Plant.h"
#include "debug.h"
#include "PlayScene.h"
#include "Mario.h"
#include "Game.h"
#include "debug.h"
#include "StraightFireBall.h"
#define MARIO_INS (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer()
#define CURRENT_SCENE ((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())
CPlant::CPlant(float x, float y, int type) :CGameObject(x, y)
{
	start_x = x;
	start_y = y;
	plant_type = type;
	EntityTag = Tag::Enemy;
	SetState(PLANT_STATE_WAITING);
	distance = 0;
}

void CPlant::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - PLANT_BBOX_WIDTH / 2;
	top = y - PLANT_BBOX_HEIGHT / 2;
	right = left + PLANT_BBOX_WIDTH;
	bottom = top + PLANT_BBOX_HEIGHT;
}


void CPlant::OnNoCollision(DWORD dt)
{
}

void CPlant::OnCollisionWith(LPCOLLISIONEVENT e)
{
	
}

void CPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	y += vy * dt;
	distance += vy * dt;
	CMario* mario = MARIO_INS;
	float mx, my;
	mario->GetPosition(mx, my);
	if (mx > this->x)
	{
		direction = 1;
	}
	else {
		direction = -1;
	}
	if (this->state == PLANT_STATE_WAITING)
	{
		if (GetTickCount64() - timer_start > WAITING_WAIT_TIME)
		{
			shot = false;
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
		if (!shot) {
			if (GetTickCount64() - timer_start > SHOOT_WAIT_TIME / 2)
			{
				CGameObject* obj = NULL;
				float aim = PLANT_AIM_UP;

				if (y > my - 16) {
					aim = PLANT_AIM_UP;
				}

				else if (y > my -24) {
					aim = PLANT_AIM_MID;
				}
				else if (y < my) {
					aim = PLANT_AIM_DOWN;
				}
				obj = new CStraightFireball(x + 16*(float)direction, y - 5, (float)direction,aim*(float)direction);
				CURRENT_SCENE->AddObject(obj);
				shot = true;
			}
		}
		if (GetTickCount64() - timer_start > SHOOT_WAIT_TIME)
		{
			SetState(PLANT_STATE_MOVING_DOWN);
		}
	}
	else
	{
		if (abs(distance)>= PLANT_MOVING_DISTANCE)
		{
			distance = 0;
			SetState(PLANT_STATE_WAITING);
		}
	}


	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CPlant::Render()
{
	CMario* mario = MARIO_INS;
	float mx, my;
	mario->GetPosition(mx, my);
	int aniId = ID_ANI_PLANT_UP_LLEFT;
	if (plant_type == 0) {
		if (direction == 1) {
			aniId = ID_ANI_PLANT_UP_LRIGHT;
		}
		if (this->state == PLANT_STATE_SHOOTING)
			if (direction == 1)
			{
				if (this->y > my - 16) {
					aniId = ID_ANI_PLANT_UP_LRIGHT;
				}
				else {
					aniId = ID_ANI_PLANT_DOWN_LRIGHT;
				}
			}
			else
			{
				if (this->y > my - 16) {
					aniId = ID_ANI_PLANT_UP_LLEFT;
				}
				else {
					aniId = ID_ANI_PLANT_DOWN_LLEFT;
				}
			}
	}
	else
	{
		aniId = ID_ANI_GREENPLANT_UP_LLEFT;
		if (direction == 1) {
			aniId = ID_ANI_GREENPLANT_UP_LRIGHT;
		}
		if (this->state == PLANT_STATE_SHOOTING)
			if (direction == 1)
			{
				if (this->y > my - 16) {
					aniId = ID_ANI_GREENPLANT_UP_LRIGHT;
				}
				else {
					aniId = ID_ANI_GREENPLANT_DOWN_LRIGHT;
				}
			}
			else
			{
				if (this->y > my - 16) {
					aniId = ID_ANI_GREENPLANT_UP_LLEFT;
				}
				else {
					aniId = ID_ANI_GREENPLANT_DOWN_LLEFT;
				}
			}
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CPlant::SetState(int state)
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

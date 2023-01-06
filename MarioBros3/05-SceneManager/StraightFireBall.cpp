#include <algorithm>
#include "debug.h"

#include "StraightFireball.h"
#include "Game.h"
#include "Collision.h"


void CStraightFireball::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vx = FIREBALL_SPEED * direction / 1.4;
	vy = FIREBALL_SPEED * direction * aim / 1.4;
	x += vx * dt;
	y += vy * dt;
	CCollision::GetInstance()->Process(this, dt, coObjects);

}

void CStraightFireball::OnNoCollision(DWORD dt)
{

}

void CStraightFireball::OnCollisionWith(LPCOLLISIONEVENT e)
{
}




void CStraightFireball::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_FIREBALL)->Render(x, y);

	//RenderBoundingBox();


}


void CStraightFireball::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - FIREBALL_BBOX_HEIGHT / 2;
	top = y - FIREBALL_BBOX_WIDTH / 2;
	right = left + FIREBALL_BBOX_HEIGHT;
	bottom = top + FIREBALL_BBOX_WIDTH;
}


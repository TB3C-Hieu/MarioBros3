#include <algorithm>
#include "debug.h"

#include "RacoonTail.h"
#include "Goomba.h"
#include "Game.h"
#include "Collision.h"
#include "Koopa.h"
#include "Plant.h"
#include "Brick.h"
#include "QuestionBrick.h"
#include "EatingPlant.h"
void CRacoonTail::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vx = TAIL_SPEED * dir;

	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CRacoonTail::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	travel_dis += vx * dt;
	if (abs(travel_dis) > TAIL_DISTANCE)
	{
		isDeleted = true;
	}
}

void CRacoonTail::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CPlant*>(e->obj))
		OnCollisionWithPlant(e);
	else if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CKoopa*>(e->obj))
		OnCollisionWithKoopa(e);
	else if (dynamic_cast<CQuestionBrick*>(e->obj))
		OnCollisionWithQuestionBrick(e);
	else if (dynamic_cast<CBrick*>(e->obj))
		OnCollisionWithBrick(e);
	else if (dynamic_cast<CEatingPlant*>(e->obj))
		OnCollisionWithEatingPlant(e);
	this->Delete();

}

void CRacoonTail::OnCollisionWithPlant(LPCOLLISIONEVENT e)
{
	CPlant* plant = dynamic_cast<CPlant*>(e->obj);
	plant->Delete();
}
void CRacoonTail::OnCollisionWithEatingPlant(LPCOLLISIONEVENT e)
{
	CEatingPlant* plant = dynamic_cast<CEatingPlant*>(e->obj);
	plant->Delete();
}

void CRacoonTail::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
	goomba->SetState(GOOMBA_STATE_SHOT);
}
void CRacoonTail::OnCollisionWithKoopa(LPCOLLISIONEVENT e)
{
	CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);
	koopa->SetState(KOOPA_STATE_SHOT);
}
void CRacoonTail::OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CQuestionBrick*>(e->obj)) {
		CQuestionBrick* qb = dynamic_cast<CQuestionBrick*>(e->obj);
		if (qb->GetState() != QBRICK_STATE_BROKEN)
			qb->SetState(QBRICK_STATE_BROKEN);
	}

}
void CRacoonTail::OnCollisionWithBrick(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CBrick*>(e->obj)) {
		CBrick* qb = dynamic_cast<CBrick*>(e->obj);
		if (qb->GetState() != BRICK_STATE_BROKEN)
			qb->SetState(BRICK_STATE_BROKEN);
	}

}



void CRacoonTail::Render()
{
RenderBoundingBox();
}


void CRacoonTail::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - FIREBALL_BBOX_HEIGHT / 2;
	top = y - FIREBALL_BBOX_WIDTH / 2;
	right = left + FIREBALL_BBOX_HEIGHT;
	bottom = top + FIREBALL_BBOX_WIDTH;
}


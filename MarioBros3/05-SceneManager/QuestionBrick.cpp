#include "QuestionBrick.h"
#include "PlayScene.h"
#include "GameObject.h"
#include "PowerUp.h"
#define CURRENT_SCENE ((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())

void CQuestionBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if (GetState()== QBRICK_STATE_SEAL)
		animations->Get(ID_ANI_QUESTION_BRICK)->Render(x, y);
	else
		animations->Get(ID_ANI_QUESTION_BRICK_BROKEN)->Render(x, y);
	//RenderBoundingBox();
}

void CQuestionBrick::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state) {
	case QBRICK_STATE_SEAL:
		looted = false;
		break;
	case QBRICK_STATE_BROKEN:
		looted = true;

		break;
	}
}
void CQuestionBrick::OnNoCollision(DWORD dt) {

}
void CQuestionBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	if (looted && !done)
	{
		y -= BRICK_SPEED*dt;
		distance_moved += BRICK_SPEED * dt;
		if (distance_moved >= BRICK_MOVING_DISTANCE)
		{
			y = start_y;
			CGameObject* obj = NULL;
			obj = new CPowerUp(x, y - 32);
			CURRENT_SCENE->AddObject(obj);
			done = true;
		}

	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void CQuestionBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BRICK_BBOX_WIDTH / 2;
	t = y - BRICK_BBOX_HEIGHT / 2;
	r = l + BRICK_BBOX_WIDTH;
	b = t + BRICK_BBOX_HEIGHT;
}
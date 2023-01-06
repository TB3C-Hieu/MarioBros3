#include "PButton.h"
#include "PlayScene.h"
#include "GameObject.h"
#include "PowerUp.h"
#define CURRENT_SCENE ((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())

void CPButton::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if (GetState() == QBRICK_STATE_SEAL)
		animations->Get(ID_ANI_PBUTTON)->Render(x, y);
	else
		animations->Get(ID_ANI_PBUTTON_BROKEN)->Render(x, y);
	//RenderBoundingBox();
}

void CPButton::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state) {
	case QBRICK_STATE_SEAL:
		break;
	case QBRICK_STATE_BROKEN:
		CURRENT_SCENE->SwapToCoin();
		break;
	}
}
void CPButton::OnNoCollision(DWORD dt) {

}
void CPButton::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void CPButton::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BRICK_BBOX_WIDTH / 2;
	t = y - BRICK_BBOX_HEIGHT / 2;
	r = l + BRICK_BBOX_WIDTH;
	b = t + BRICK_BBOX_HEIGHT;
}
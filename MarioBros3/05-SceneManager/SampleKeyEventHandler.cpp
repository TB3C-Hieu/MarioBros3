#include "SampleKeyEventHandler.h"

#include "debug.h"
#include "Game.h"

#include "Mario.h"
#include "PlayScene.h"
#include "GameObject.h"
#include "Fireball.h"
#include "Koopa.h"
#define CURRENT_SCENE ((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())
void CSampleKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	CMario* mario = (CMario *)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer(); 
	CGameObject* obj = NULL;
	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);
	switch (KeyCode)
	{
	case DIK_K:
	case DIK_DOWN:
		mario->SetState(MARIO_STATE_SIT);
		break;
	case DIK_S:
		mario->SetState(MARIO_STATE_JUMP);
		mario->SlowFall();
		break;
	case DIK_1:
		mario->SetLevel(MARIO_LEVEL_SMALL);
		break;
	case DIK_2:
		mario->SetLevel(MARIO_LEVEL_BIG);
		break;
	case DIK_0:
		mario->SetState(MARIO_STATE_DIE);
		break;
	case DIK_3:
		mario->SetLevel(MARIO_LEVEL_FIRE);
		break;
	case DIK_A: // reset
		mario->Shoot();
		break;	

	case DIK_4: // reset
		mario->SetLevel(MARIO_LEVEL_RACOON);
		break;
	case DIK_Q:
		obj = new CGoomba(cx + SCREEN_WIDTH - 16, 10);
		CURRENT_SCENE->AddObject(obj);
		break;
	case DIK_E:
		obj = new CKoopa(cx + SCREEN_WIDTH - 16, 10);
		CURRENT_SCENE->AddObject(obj);
		break;
	case DIK_R:
		CURRENT_SCENE->SwapToCoin();
	
	}
}

void CSampleKeyHandler::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	switch (KeyCode)
	{
	case DIK_S:
		mario->SetState(MARIO_STATE_RELEASE_JUMP);
		break;
	case DIK_K:
	case DIK_DOWN:
		mario->SetState(MARIO_STATE_SIT_RELEASE);
		break;
	}
}

void CSampleKeyHandler::KeyState(BYTE *states)
{
	LPGAME game = CGame::GetInstance();
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	if (game->IsKeyDown(DIK_RIGHT) or game->IsKeyDown(DIK_L))
	{
		if (game->IsKeyDown(DIK_A))
			mario->SetState(MARIO_STATE_RUNNING_RIGHT);
		else
			mario->SetState(MARIO_STATE_WALKING_RIGHT);
	}
	else if (game->IsKeyDown(DIK_LEFT) or game->IsKeyDown(DIK_J))
	{
		if (game->IsKeyDown(DIK_A))
			mario->SetState(MARIO_STATE_RUNNING_LEFT);
		else
			mario->SetState(MARIO_STATE_WALKING_LEFT);
	}
	else
		mario->SetState(MARIO_STATE_IDLE);
}
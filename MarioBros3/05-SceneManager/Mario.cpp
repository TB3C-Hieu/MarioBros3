#include <algorithm>
#include "debug.h"

#include "Mario.h"
#include "Game.h"
#include "PlayScene.h"
#include "Goomba.h"
#include "Coin.h"
#include "Portal.h"
#include "QuestionBrick.h"
#include "GhostPlatform.h"
#include "Brick.h"
#include "Collision.h"
#include "Koopa.h"
#include "StraightFireBall.h"
#include "Plant.h"
#include "EatingPlant.h"
#include "Fireball.h"
#include "RacoonTail.h"
#include "PowerUp.h"
#include "PButton.h"
#define CURRENT_SCENE ((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())

void CMario::Shoot() {
	if (level == MARIO_LEVEL_FIRE) {
		CGameObject* obj = NULL;
		obj = new CFireball(x + 16 * (float)nx, y, (float)nx);
		CURRENT_SCENE->AddObject(obj);
	}
	else if (level == MARIO_LEVEL_RACOON && GetTickCount64() - tail_attack_timer > MARIO_TAILATTACK_TIME)
	{
		tail_attacking = true;
		tail_attack_timer = GetTickCount64();
	}
}
void CMario::SlowFall() {
	if (!isOnPlatform && level == MARIO_LEVEL_RACOON) {
		if (abs(vx) != MARIO_RUNNING_SPEED) {
			slow_falling = true;
			slow_timer = GetTickCount64();

		}
		else
		{
			if (!flying) total_fly_timer = GetTickCount64();
			flying = true;
			fly_timer = GetTickCount64();
		}

	}
}
void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	vy += ay * dt;
	vx += ax * dt;
	if (flying)
	{
		vy = -0.04f;
		vx = abs(maxVx)*nx;
	}
	else if (slow_falling)
	{
		vy = 0.04f;
		vx = abs(MARIO_WALKING_SPEED)*nx;
	}
	if (GetTickCount64() - slow_timer > MARIO_SLOW_TIME) {
		slow_falling = false;
	}	
	if (GetTickCount64() - fly_timer > MARIO_SLOW_TIME) {
		flying = false;
	}
	if (GetTickCount64() - total_fly_timer > MARIO_MAX_FLY_DURATION && flying)
	{
		flying = false;
		vx = abs(MARIO_WALKING_SPEED) * (float)nx;

	}
	if (GetTickCount64() - tail_attack_timer > MARIO_TAILATTACK_TIME)
	{
		tail_attacking = false;
		attacked = false;
	}	
	if (GetTickCount64() - tail_attack_timer > 100 && tail_attacking && !attacked )
	{
		CGameObject* obj = NULL;
		attacked = true;
		obj = new CRacoonTail(x, y + 6, (float)nx);
		CURRENT_SCENE->AddObject(obj);
	}


	if (abs(vx) > abs(maxVx)) vx = maxVx;

	// reset untouchable timer if untouchable time has passed
	if ( GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME) 
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	isOnPlatform = false;

	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMario::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;

}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CGhostPlatform*>(e->obj))
	{
		CGhostPlatform* gplat = dynamic_cast<CGhostPlatform*>(e->obj);
		if (e->ny < 0)
		{
			gplat->SetBlocking(1);
			//bounce
			float px, py;
			gplat->GetPosition(px, py);
			this->y = py - height;
		}
		else
			gplat->SetBlocking(0);
	}
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
		if (e->ny < 0) isOnPlatform = true;
	}
	else
		if (e->nx != 0 && e->obj->IsBlocking())
		{
			vx = 0;
		}
	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CCoin*>(e->obj))
		OnCollisionWithCoin(e);
	else if (dynamic_cast<CPortal*>(e->obj))
		OnCollisionWithPortal(e);
	else if (dynamic_cast<CQuestionBrick*>(e->obj))
		OnCollisionWithQBrick(e);
	else if (dynamic_cast<CBrick*>(e->obj))
		OnCollisionWithBrick(e);
	else if (dynamic_cast<CGhostPlatform*>(e->obj))
		OnCollisionWithGPlatform(e);
	else if (dynamic_cast<CKoopa*>(e->obj))
		OnCollisionWithKoopa(e);
	else if (dynamic_cast<CPlant*>(e->obj))
		OnCollisionWithPlant(e);
	else if (dynamic_cast<CStraightFireball*>(e->obj))
		OnCollisionWithPlant(e);
	else if (dynamic_cast<CEatingPlant*>(e->obj))
		OnCollisionWithPlant(e);
	else if (dynamic_cast<CPowerUp*>(e->obj))
		OnCollisionWithPowerUp(e);
	else if (dynamic_cast<CPButton*>(e->obj))
		OnCollisionWithPButton(e);
}

void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{
		if (goomba->GetState() != GOOMBA_STATE_DIE)
		{
			goomba->SetState(GOOMBA_STATE_DIE);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else // hit by Goomba
	{
		if (untouchable == 0)
		{
			if (goomba->GetState() != GOOMBA_STATE_DIE)
			{
				if (level > MARIO_LEVEL_SMALL)
				{
					LevelDown();
					StartUntouchable();
				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
			}
		}
	}
}void CMario::OnCollisionWithPowerUp(LPCOLLISIONEVENT e)
{
	CPowerUp* pu = dynamic_cast<CPowerUp*>(e->obj);
	y -= 8;
	LevelUp();
	pu->Delete();
}
void CMario::OnCollisionWithPlant(LPCOLLISIONEVENT e)
{
		if (untouchable == 0)
		{
			if (level > MARIO_LEVEL_SMALL)
			{
				LevelDown();
				StartUntouchable();
			}
			else
			{
				DebugOut(L">>> Mario DIE >>> \n");
				SetState(MARIO_STATE_DIE);
			}
		}
}
void CMario::OnCollisionWithKoopa(LPCOLLISIONEVENT e)
{
	CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);

	// jump on top >> kill Goomba and deflect a bit 

	if (e->ny < 0)
	{
		if (koopa->GetState() != KOOPA_STATE_SHELL)
		{
			koopa->SetState(KOOPA_STATE_SHELL);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else // hit by Goomba
	{
		if (untouchable == 0)
		{
			if (koopa->GetState() != KOOPA_STATE_SHELL && koopa->GetState()!= KOOPA_STATE_SHELL_HOLDING)
			{
				if (level > MARIO_LEVEL_SMALL)
				{
					LevelDown();
					StartUntouchable();
				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
			}
		}
	}
	if (e->nx != 0)
	{
		if (koopa->GetState() == KOOPA_STATE_SHELL)
		{
			if (state == MARIO_STATE_RUNNING_LEFT || state == MARIO_STATE_RUNNING_RIGHT)
			{
				koopa->SetState(KOOPA_STATE_SHELL_HOLDING);
			}
			else {
				if (e->nx > 0) {
					koopa->GotKick(-1);
				}
				else {
					koopa->GotKick(1);
				}
			}
		}
		else if (koopa->GetState() == KOOPA_STATE_SHELL_HOLDING)
		{
			if (state != MARIO_STATE_RUNNING_LEFT && state != MARIO_STATE_RUNNING_RIGHT && state != MARIO_STATE_JUMP && state!= MARIO_STATE_RELEASE_JUMP)
			{
				koopa->SetState(KOOPA_STATE_SHELL);
				if (e->nx > 0) {
					koopa->GotKick(-1);
				}
				else {
					koopa->GotKick(1);
				}
			}
		}
	}
}
void CMario::OnCollisionWithQBrick(LPCOLLISIONEVENT e)
{
	CQuestionBrick* qbrick = dynamic_cast<CQuestionBrick*>(e->obj);

	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny > 0)
	{
		qbrick->SetState(QBRICK_STATE_BROKEN);
	}
}
void CMario::OnCollisionWithBrick(LPCOLLISIONEVENT e)
{
	CBrick* brick = dynamic_cast<CBrick*>(e->obj);
	
	if (e->ny > 0)
	{
		if (brick->GetState() != BRICK_STATE_BROKEN) 
		{
			brick->SetState(BRICK_STATE_BROKEN);
		}
	}
}
void CMario::OnCollisionWithPButton(LPCOLLISIONEVENT e)
{
	CPButton* button = dynamic_cast<CPButton*>(e->obj);
	
	if (e->ny < 0)
	{
		if (button->GetState() != QBRICK_STATE_BROKEN)
		{
			button->SetState(QBRICK_STATE_BROKEN);
		}
	}
}
void CMario::OnCollisionWithGPlatform(LPCOLLISIONEVENT e)
{

	// jump on top >> kill Goomba and deflect a bit 
	
}
void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	coin++;
}

void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	CPortal* p = (CPortal*)e->obj;
	CGame::GetInstance()->InitiateSwitchScene(p->GetSceneId());
}

//
// Get animation ID for small Mario
//
int CMario::GetAniIdSmall()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_SMALL_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;

	return aniId;
}


//
// Get animdation ID for big Mario
//
int CMario::GetAniIdRacoon()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_RACOONMARIO_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_RACOONMARIO_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_RACOONMARIO_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_RACOONMARIO_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_RACOONMARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_RACOONMARIO_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_RACOONMARIO_IDLE_RIGHT;
				else aniId = ID_ANI_RACOONMARIO_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_RACOONMARIO_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_RACOONMARIO_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_RACOONMARIO_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_RACOONMARIO_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_RACOONMARIO_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_RACOONMARIO_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_RACOONMARIO_IDLE_RIGHT;
	if (slow_falling) {
		if (nx < 0)
			aniId = ID_ANI_RACOONMARIO_SLOWFALL_LEFT;
		else
			aniId = ID_ANI_RACOONMARIO_SLOWFALL_RIGHT;
	}
	else if (tail_attacking)
	{
		aniId = ID_ANI_RACOONMARIO_TAILATTACK_RIGHT;
	}
	return aniId;
}//
// Get animdation ID for big Mario
//
int CMario::GetAniIdBig()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_IDLE_RIGHT;

	return aniId;
}
//
// Get animdation ID for Fire Mario
//
int CMario::GetAniIdFire()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_FIREMARIO_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_FIREMARIO_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_FIREMARIO_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_FIREMARIO_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_FIREMARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_FIREMARIO_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_FIREMARIO_IDLE_RIGHT;
				else aniId = ID_ANI_FIREMARIO_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_FIREMARIO_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_FIREMARIO_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_FIREMARIO_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_FIREMARIO_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_FIREMARIO_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_FIREMARIO_WALKING_LEFT;
			}


	if (aniId == -1) aniId = ID_ANI_FIREMARIO_IDLE_RIGHT;

	return aniId;
}

void CMario::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;

	if (state == MARIO_STATE_DIE)
		aniId = ID_ANI_MARIO_DIE;
	else if (level == MARIO_LEVEL_RACOON)
		aniId = GetAniIdRacoon();
	else if (level == MARIO_LEVEL_FIRE)
		aniId = GetAniIdFire();
	else if (level == MARIO_LEVEL_BIG)
		aniId = GetAniIdBig(); 
	else if (level == MARIO_LEVEL_SMALL)
		aniId = GetAniIdSmall();

	animations->Get(aniId)->Render(x, y);

	//RenderBoundingBox();
	
	DebugOutTitle(L"Coins: %d", coin);
}

void CMario::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == MARIO_STATE_DIE) return; 

	switch (state)
	{
	case MARIO_STATE_RUNNING_RIGHT:
		if (isSitting) break;
		nx = 1;

		if (!isOnPlatform) break;
		maxVx = MARIO_RUNNING_SPEED;
		ax = MARIO_ACCEL_RUN_X;
		break;
	case MARIO_STATE_RUNNING_LEFT:
		if (isSitting) break;
		nx = -1;

		if (!isOnPlatform) break;
		maxVx = -MARIO_RUNNING_SPEED;
		ax = -MARIO_ACCEL_RUN_X;
		break;
	case MARIO_STATE_WALKING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_WALKING_SPEED;
		ax = MARIO_ACCEL_WALK_X;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_WALKING_SPEED;
		ax = -MARIO_ACCEL_WALK_X;
		nx = -1;
		break;
	case MARIO_STATE_JUMP:
		if (isSitting) break;
		if (isOnPlatform)
		{
			if (abs(this->vx) == MARIO_RUNNING_SPEED)
				vy = -MARIO_JUMP_RUN_SPEED_Y;
			else
				vy = -MARIO_JUMP_SPEED_Y;
		}
		break;

	case MARIO_STATE_RELEASE_JUMP:
		if (vy < 0) vy += MARIO_JUMP_SPEED_Y / 2;
		break;

	case MARIO_STATE_SIT:
		if (isOnPlatform && level != MARIO_LEVEL_SMALL)
		{
			state = MARIO_STATE_IDLE;
			isSitting = true;
			vx = 0; vy = 0.0f;
			y +=MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_SIT_RELEASE:
		if (isSitting)
		{
			isSitting = false;
			state = MARIO_STATE_IDLE;
			y -= MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_IDLE:
		ax = 0.0f;
		vx = 0.0f;
		break;

	case MARIO_STATE_DIE:
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		vx = 0;
		ax = 0;
		break;
	}

	CGameObject::SetState(state);
}

void CMario::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (level>=MARIO_LEVEL_BIG)
	{
		if (isSitting)
		{
			left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else 
		{
			left = x - MARIO_BIG_BBOX_WIDTH/2;
			top = y - MARIO_BIG_BBOX_HEIGHT/2;
			right = left + MARIO_BIG_BBOX_WIDTH;
			bottom = top + MARIO_BIG_BBOX_HEIGHT;
		}
		height = bottom - top;

	}
	else
	{
		left = x - MARIO_SMALL_BBOX_WIDTH/2;
		top = y - MARIO_SMALL_BBOX_HEIGHT/2;
		right = left + MARIO_SMALL_BBOX_WIDTH;
		bottom = top + MARIO_SMALL_BBOX_HEIGHT;
		height = bottom - top + 3;

	}
}

void CMario::SetLevel(int l)
{
	// Adjust position to avoid falling off platform
	if (this->level == MARIO_LEVEL_SMALL)
	{
		y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
	}
	level = l;
}

void CMario::LevelUp()
{
	level += 1;
	if (level > 4) level = 4;
}
void CMario::LevelDown() {
	if (level > 2)
	{
		level = 2;
	}
	else if (level > 1) {
		level = 1;
	}
	else {
		level = 1;
		y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
	}
}


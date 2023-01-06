#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_COIN 11100

#define	COIN_WIDTH 10
#define COIN_BBOX_WIDTH 10
#define COIN_BBOX_HEIGHT 16

class CPowerUp : public CGameObject {
private:
	float ay,ax;
public:
	CPowerUp(float x, float y) : CGameObject(x, y) { 
		EntityTag = Tag::pickable; 
		vx = 0.05f;
		ay = 0.001f;
		ax = 0;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	virtual int IsCollidable() { return 1; }
};
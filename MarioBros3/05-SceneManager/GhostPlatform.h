#pragma once

#include "GameObject.h"

// 
// The most popular type of object in Mario! 
// 
class CGhostPlatform : public CGameObject
{
protected:
	int length;				// Unit: cell 
	float cellWidth;
	float cellHeight;
	int	is_blocking;

public:
	CGhostPlatform(float x, float y,
		float cell_width, float cell_height, int length) :CGameObject(x, y)
	{
		this->length = length;
		this->cellWidth = cell_width;
		this->cellHeight = cell_height;
		this->is_blocking = 0;
		EntityTag = Tag::block;
	}

	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void RenderBoundingBox();
	int IsBlocking() { return is_blocking; }
	void SetBlocking(int value) { this->is_blocking = value; }

};

typedef CGhostPlatform* LPGHOSTPLATFORM;
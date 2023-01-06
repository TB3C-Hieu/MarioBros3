#ifndef __CAMERA_H__
#define __CAMERA_H__

//#include <>

#include "Utils.h"
#include "d3dx10.h"
#include "directxmath.h"

#define CAMERA_DEFAULT_SCROLLING_SPEED_VX 2.0f;
#define CAMERA_DEFAULT_SCROLLING_SPEED_VY 2.0f;
class Camera
{
private:
	//camera width
	float camera_width;
	//camera height
	float camera_height;

	//camera position
	D3DXVECTOR2 camera_Position;

	//camera limit for left position
	float bound_left;
	//camera limit for top position
	float bound_top;
	//camera limit for right position (camera_Position.x - camera width)
	float bound_right;
	//camera limit for bottom position (camera_Position.y - camera Height);
	float bound_bottom;

	bool scroll_x;
	bool scroll_y;


	bool following;
public:
	Camera();
	~Camera();

	void setCameraPosition(D3DXVECTOR2 position);
	void setCameraPosition(float x, float y);
	void setCameraPositionX(float x);
	void setCameraPositionY(float y);

	float getCameraWidth();
	float getCameraHeight();

	D3DXVECTOR2 toCameraPosistion(float WorldPositionX, float WorldPositionY);

	float getCameraPositionX();
	float getCameraPositionY();
	D3DXVECTOR2 getCameraPosition();

	void setBound(float left, float top, float right, float bottom);
	float getBoundleft();
	float getBoundTop();
	float getBoundRight();
	float getBoundBottom();

	void setScrollX(bool isscrollX);
	void setScrollY(bool isscrollY);

	bool isFollowing();

	void Update(DWORD dt);

};

//typedef Camera* LPCAMERA

#endif 


#ifndef __CAMERA__H__
#define __CAMERA__H__

#pragma once

#include <d3dx9.h>

class Camera
{
public:
	Camera();

	void setBound(RECT rect);

	float speedX;

	bool stopScrollScreen;

	bool donePrepare;
	
	float posXTarget;

	void update(float x, float dt);

	bool move(float vX, float posXTarget, float dt, bool dir = false);

	D3DXVECTOR3 getPosCamera();

	D3DXVECTOR3 getPointTransform(float x, float y);

	RECT getScreen();

private:

	D3DXVECTOR3 _position;
	D3DXMATRIX _MatrixTransform;
	RECT _boundScene;

};

#endif
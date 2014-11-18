#ifndef __GAMEOBJECT__H__
#define __GAMEOBJECT__H__

#pragma once


#include<d3dx9.h>
#include"Point.h"
#include<vector>
#include"Collision.h"
#include"GameNode.h"



class ObjectGame
{
public:

	int ID;

	int ID_Image;

	bool _isFlipX = false;

	RECT* _rectRS;

	bool _isAnimation = false;

	float vX;

	float vY;

	Size getContainSize();

	void setZOther(float);

	float getZOther();

	void setContainSize(float, float);

	void setContainSize(Size);

	void setPosition(float , float);

	void setPosition(Point);

	void setPositionX(float);

	void setPositionY(float);

	Point getPosition();

	float getPositionX();

	float getPositionY();

	ObjectGame();
	~ObjectGame();

	ObjectGame(GameNode);

	virtual void update(float);

	virtual Box getBox();

    void drawBoundingBox(LPDIRECT3DDEVICE9, Box);

protected:

	Box _box;

	float _zOther;

	Size _containtSize;

	D3DXVECTOR2 _position;

};

#endif
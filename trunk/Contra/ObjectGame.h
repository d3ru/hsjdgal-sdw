#ifndef __GAMEOBJECT__H__
#define __GAMEOBJECT__H__

#pragma once


#include<d3dx9.h>
#include"Point.h"
#include<vector>


class ObjectGame
{
public:

	int ID;

	int ID_Image;

	bool _isFlipX = false;

	RECT* _rectRS;

	RECT _rect;

	bool _isAnimation = false;

	Size _containtSize;

	RECT getRect();

	Size getContainSize();

	void setZOther(float);

	float getZOther();

	void setContainSize(float, float);

	void setPosition(float , float);

	void setPosition(Point);

	void setPositionX(float);

	void setPositionY(float);

	Point getPosition();

	float getPositionX();

	float getPositionY();

	ObjectGame();
	~ObjectGame();

	ObjectGame(std::vector<std::string> );

	virtual void update(float);

protected:

	float _zOther;

	D3DXVECTOR2 _position;

};

#endif
#ifndef __DYNAMICOBJECT__H__
#define __DYNAMICOBJECT__H__

#pragma once

#include"ObjectGame.h"

class DynamicObject : public ObjectGame
{
public:
	DynamicObject();
	~DynamicObject();

	
	DynamicObject(GameNode);

	float getTimeCollision(ObjectGame*,float&, float&, float);

	virtual Box getBox() override;
};

#endif


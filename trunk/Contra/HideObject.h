#ifndef __HIDEOBJECT__H__
#define __HIDEOBJECT__H__

#include"ObjectGame.h"

#pragma once


enum class TYPEOBJECT
{
	GROUND,
	SWITCH,
	WATER,
};


class HideObject : public ObjectGame
{
public:
	HideObject();

	TYPEOBJECT typeObject;

	HideObject(GameNode);
};

#endif


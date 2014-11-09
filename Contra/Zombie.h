#ifndef __ZOMBIE__H__
#define __ZOMBIE__H__

#include"DynamicObject.h"
#include"Animation.h"
#include"Zombie.h"
#include"GameNode.h"
#include"HideObject.h"

#pragma once

enum class ZombieStatus
{
	isNormal,
	isOnAir,
	islyingDown,
	isUnderWater,
};


enum class AnimationStatus
{
	isInit,
	isFire,
	isRotate,
	isRun,
	isFireUp,
	isFireDown,
};

class Zombie : public DynamicObject, public Animation 
{
public:
	

	static Zombie* createInstance(GameNode);

	static Zombie* getInstance();

	Zombie();
	
	Zombie(GameNode);

	void update(float dt);

	void draw();


	bool isMove;

	ZombieStatus zombieStatus;

	AnimationStatus animationStatus;


	void collision(float, std::vector<HideObject*>);

private:

	

	bool isJump;
	
	void updateRECT();

	bool isOnFoot;

	
	void addBullet();
};

#endif


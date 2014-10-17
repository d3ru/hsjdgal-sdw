#ifndef __ZOMBIE__H__
#define __ZOMBIE__H__

#include"ObjectGame.h"
#include"Animation.h"
#include"Zombie.h"


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
	isNormal,
	isRun,
	isFireUp,
	isFireDown,
};

class Zombie : public ObjectGame, public Animation 
{
public:

	static Zombie* createInstance(std::vector<std::string>);

	static Zombie* getInstance();

	Zombie();
	
	Zombie(std::vector<std::string>);

	void update(float dt);

	void draw();


	bool isMove;

	ZombieStatus zombieStatus;

	AnimationStatus animationStatus;

	float vX;
	float vY;

private:

	
	void updateRECT();



	
	void addBullet();
};

#endif


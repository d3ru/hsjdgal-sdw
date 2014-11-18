#ifndef __ZOMBIE__H__
#define __ZOMBIE__H__

#include"DynamicObject.h"
#include"Animation.h"
#include"Zombie.h"
#include"GameNode.h"
#include"HideObject.h"

#pragma once

enum class ZOMBIESTATUS
{
	RESET,
	HIDE,
	ONLAND,
	LYINGDOWN,
	FALLING,
	ONARI,
	UNDERWATER,
};

enum class ANIMATIONSTATUS
{
	INIT,
	RUN,
	ROTATE,
	FIRE,
};

enum class COLLISIONSTATUS
{
	NOPE,
	GROUND,
	SWITCH,
	WATER,
};


class Zombie : public DynamicObject, public Animation 
{
public:
	

	static Zombie* createInstance(GameNode);

	static Zombie* getInstance();

	Zombie();
	~Zombie();
	
	Zombie(GameNode);

	void update(float dt);

	void draw();

	ZOMBIESTATUS zombieStatus;
	ANIMATIONSTATUS animationStatus;
	COLLISIONSTATUS collisionStatus;

	void collision(float, std::vector<HideObject*>);

	bool isMove; 


private:

	
	float detalTimeSwing; // thoi gian 1 frame Rambo chuyen dong tai cho

	float deltaTimeFire; // thoi gian 1 lan ban khi o duoi nuoc

	float detalA; 

	int directionY;

	bool isJump;	

	bool isOnFoot;

	void proccessKeyBoard(float dt);


};

#endif


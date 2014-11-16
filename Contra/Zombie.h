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
	ONLAND,
	LYINGDOWN,
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

class Zombie : public DynamicObject, public Animation 
{
public:
	

	static Zombie* createInstance(GameNode);

	static Zombie* getInstance();

	Zombie();
	
	Zombie(GameNode);

	void update(float dt);

	void draw();

	ZOMBIESTATUS zombieStatus;
	ANIMATIONSTATUS animationStatus;

	void collision(float, std::vector<HideObject*>);

	bool isMove; 


private:

	float detalA; 

	int directionY;

	bool isJump;	

	bool isOnFoot;

	void proccessKeyBoard();


};

#endif


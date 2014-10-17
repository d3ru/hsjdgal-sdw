#ifndef __BULLETFACTORY__H__
#define __BULLETFACTORY__H__

#include"ObjectFactory.h"
#include"Bullet.h"
#include"Zombie.h"

#pragma once
class BulletFactory : public ObjectFactory
{
public:
	
	static BulletFactory* createInstance();

	Bullet* create(Zombie*);

};

#endif

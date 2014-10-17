#ifndef __ZOMBIEFACTORY__H__
#define __ZOMBIEFACTORY__H__

#include"ObjectFactory.h"
#include"Zombie.h"


#pragma once
class ZombieFactory : public ObjectFactory
{
public:

	static ZombieFactory* createInstance();

	Zombie* create();



};

#endif


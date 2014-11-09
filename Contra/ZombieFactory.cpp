#include "ZombieFactory.h"

static ZombieFactory* instance = nullptr;

ZombieFactory* ZombieFactory::createInstance()
{
	if (instance == nullptr)
		instance = new ZombieFactory();
	return instance;
}

Zombie* ZombieFactory::create()
{
	return Zombie::createInstance(listInfo.at(0));
}

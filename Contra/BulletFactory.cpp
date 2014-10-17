#include "BulletFactory.h"
#include "Zombie.h"

static BulletFactory* instance = nullptr;

BulletFactory* BulletFactory::createInstance()
{
	if (instance == nullptr)
		instance = new BulletFactory();
	return instance;
}

Bullet* BulletFactory::create(Zombie* zombie)
{ 
	return new Bullet(info.at(0), zombie);
}

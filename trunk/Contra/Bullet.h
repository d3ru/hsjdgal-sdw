#ifndef __BULLET__H__
#define __BULLET__H__

#include"ObjectGame.h"
#include"Zombie.h"

enum class BulletStatus
{
	isNormal,
	isHide,
};


class Bullet : public ObjectGame
{
public:

	static Bullet* createInstance(std::vector<std::string>);

	Bullet();
	
	Bullet(std::vector<std::string>, Zombie*);

	BulletStatus bulletStatus;

	void update(float);

	void draw();

private :

	float vX;

	float vY;

	int dir_X;

	float distaceBullet;
};

#endif

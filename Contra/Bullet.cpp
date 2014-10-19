#include "Bullet.h"
#include "SpriteManager.h"


static Bullet* instance = nullptr;

Bullet* Bullet::createInstance(std::vector<std::string> arr)
{
	if (instance == nullptr)
		instance = new Bullet();
	return instance;
}

Bullet::Bullet()
{
}

Bullet::Bullet(std::vector<std::string> arr, Zombie* zombie)
{
	this->ID_Image = atoi(arr.at(0).c_str());

	this->ID = atoi(arr.at(1).c_str());

	this->vX = 290;

	this->vY = 0;

	

	bulletStatus = BulletStatus::isNormal;

	

	if (!zombie->_isFlipX)
	{
		dir_X = 1;
		this->setPosition(zombie->getPositionX() + zombie->getContainSize().width / 2 + this->getContainSize().width / 2, zombie->getPositionY() - 13);
		distaceBullet = zombie->getPositionX() + 400;
		if (zombie->isMove)
			vX += zombie->vX;
	}
	else if (zombie->_isFlipX)
	{
		dir_X = -1;
		this->setPosition(zombie->getPositionX() - zombie->getContainSize().width / 2, zombie->getPositionY() - 13);
		distaceBullet = zombie->getPositionX() - 400;
		if (zombie->isMove)
			vX += zombie->vX;
	}

	
}

void Bullet::update(float dt)
{
	if (bulletStatus == BulletStatus::isNormal && !Zombie::getInstance()->_isFlipX && this->getPositionX() >= this->distaceBullet)
	{
		bulletStatus = BulletStatus::isHide;
	}
	else if (bulletStatus == BulletStatus::isNormal && Zombie::getInstance()->_isFlipX && this->getPositionX() <= this->distaceBullet)
	{
		bulletStatus = BulletStatus::isHide;
	}
	this->setPosition(this->getPositionX() + this->dir_X * vX * dt, this->getPositionY() + vY * dt);
}

void Bullet::draw()
{
	if (this->bulletStatus == BulletStatus::isNormal)
		SpriteManager::createInstance()->drawObj(this);
}


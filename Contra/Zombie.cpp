#include "Zombie.h"
#include "SpriteManager.h"
#include"Input.h"
#include"BulletFactory.h"

static Zombie* instance = nullptr;

Zombie* Zombie::createInstance(std::vector<std::string> arr)
{
	if (instance == nullptr)
		instance = new Zombie(arr);
	return instance;
}

Zombie* Zombie::getInstance()
{
	if (instance == nullptr)
		instance = new Zombie();
	return instance;
}

Zombie::Zombie()
{
}

Zombie::Zombie(std::vector<std::string> arr)
{
	this->ID = atoi(arr.at(0).c_str());

	this->ID_Image = atoi(arr.at(1).c_str());

	this->_isAnimation = true;

	this->setContainSize(atoi(arr.at(2).c_str()),atoi(arr.at(3).c_str()));

	this->_columm = atoi(arr.at(4).c_str());

	this->_totalFrames = atoi(arr.at(5).c_str());

	this->_elapseTimeSwitchFrame = atof(arr.at(6).c_str());

	this->setPosition(100, 500);

	this->isMove = false;

	this->vX = 30.0f;

	this->vY = 0;

	this->setZOther(1);

	this->zombieStatus = ZombieStatus::isNormal;

	this->animationStatus = AnimationStatus::isInit;


	for (int i = 0; i < 14; i++)
	{
		auto rect = new RECT();

		rect->left = i * 56;
		rect->right = rect->left + 56;
		rect->top = 0;
		rect->bottom = 92;

		listRect.push_back(rect);
	}

	
	
}

void Zombie::update(float dt)
{
	Input::CreateInstance()->ProcessKeyboard();
	Input::CreateInstance()->Update();

	int isKeyDown = Input::CreateInstance()->GetKeyDown();
	int iskeyUp = Input::CreateInstance()->GetKeyUp();


	if (zombieStatus == ZombieStatus::isNormal)
	{
		if (Input::CreateInstance()->IsKeyDown(DIK_RIGHT))
		{
			this->_isFlipX = false;
			this->vX = 90;

			if (Input::CreateInstance()->IsKeyDown(DIK_UP))
			{
				if (animationStatus == AnimationStatus::isNormal || animationStatus == AnimationStatus::isInit)
					animationStatus = AnimationStatus::isFireUp;
			}
			else
			{

				if (animationStatus == AnimationStatus::isInit)
					animationStatus = AnimationStatus::isRun;
			}
		}
		else if (Input::CreateInstance()->IsKeyDown(DIK_LEFT))
		{
			this->_isFlipX = true;
			this->vX = -90;
			if (Input::CreateInstance()->IsKeyDown(DIK_UP))
			{
				if (animationStatus == AnimationStatus::isNormal || animationStatus == AnimationStatus::isInit)
					animationStatus = AnimationStatus::isFireUp;
			}
			else
			{

				if (animationStatus == AnimationStatus::isInit)
					animationStatus = AnimationStatus::isRun;
			}
		}
		
		else
		{
			this->vX = 0;
		}
	}

	if (iskeyUp == DIK_LEFT || iskeyUp == DIK_RIGHT || iskeyUp == DIK_UP)
	{
		animationStatus = AnimationStatus::isInit;
	}
	
	
	this->setPosition(this->getPositionX() + this->vX * dt, this->getPositionY() + this->vY * dt);

	updateRECT();
	
	this->_rectRS = cropRect(dt);
	
}

void Zombie::updateRECT()
{
	//Stand
	if (animationStatus == AnimationStatus::isInit)
	{
		index = 3;
		lastFrame = 3;
		firstFrame = 3;
	}
	//Run
	if (animationStatus == AnimationStatus::isRun)
	{
		animationStatus = AnimationStatus::isNormal;
		index = 4;
		lastFrame = 6;
		firstFrame = 3;
	}
	//Up - R - L
	if (animationStatus == AnimationStatus::isFireUp)
	{
		animationStatus = AnimationStatus::isFireDown;
		index = 9;
		lastFrame = 12;
		firstFrame = 9;
	}


}



void Zombie::addBullet()
{
	/*Bullet* bullet = BulletFactory::CreateInstance()->create((Zombie*)this);
	listBullet->push_back(bullet);*/
}

void Zombie::draw()
{
	SpriteManager::createInstance()->drawObj(this);
	/*if (listBullet)
	{
		for (auto bullet : *listBullet)
		{
			bullet->draw();
		}
	}*/
}

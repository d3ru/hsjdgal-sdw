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


	this->setPosition(100, 100);

	this->isMove = false;

	this->isJump = true;

	this->isOnFoot = false;

	this->vX = 90.0f;

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

	for (int i = 0; i < 2; i++)
	{
		auto rect = new RECT();
		rect->left = i * 66;
		rect->right = rect->left + 66;
		rect->top = 92;
		rect->bottom = 126;

		listRect.push_back(rect);
	}

	for (int i = 0; i < 4; i++)
	{
		auto rect = new RECT();

		rect->left = i * 34 + 132;
		rect->right = rect->left + 34;
		rect->top = 92;
		rect->bottom = 126;

		listRect.push_back(rect);
	}
	
}

void Zombie::update(float dt)
{
	Input::CreateInstance()->ProcessKeyboard();
	Input::CreateInstance()->Update();

	int isKeyDown = Input::CreateInstance()->GetKeyDown();
	int iskeyUp = Input::CreateInstance()->GetKeyUp();

	//Stand Up
	if (iskeyUp == DIK_DOWN && zombieStatus == ZombieStatus::islyingDown)
	{
		zombieStatus = ZombieStatus::isNormal;
		this->setPositionY(this->getPositionY() + 30);
	}

	//Laying Dowwn
	if (Input::CreateInstance()->IsKeyDown(DIK_DOWN) && zombieStatus == ZombieStatus::isNormal  && !isOnFoot)
	{
		zombieStatus = ZombieStatus::islyingDown;
		this->setAnimation(14,14,14);
		this->setPositionY(this->getPositionY() - 30);
		
	}
	
	//Fire When Lying Down
	if (zombieStatus == ZombieStatus::islyingDown)
	{
		if (Input::CreateInstance()->IsKeyDown(DIK_Z) && animationStatus == AnimationStatus::isInit)
		{
			animationStatus = AnimationStatus::isFire;
			this->setAnimation(14,14,16);
		}
	}

	//Jump
	if (( zombieStatus == ZombieStatus::isNormal)&& Input::CreateInstance()->IsKeyDown(DIK_SPACE) && isJump && !isOnFoot)
	{
		zombieStatus = ZombieStatus::isOnAir;
		this->vY = 300;
		isJump = false;		
		if (animationStatus == AnimationStatus::isInit)
		{
			animationStatus = AnimationStatus::isRotate;
			this->setAnimation(17,19,20,0.15);
		}
	}
	if (this->getPositionY() >= 250 && zombieStatus == ZombieStatus::isOnAir)
	{
		//zombieStatus = ZombieStatus::isNormal;
		this->vY = -250;
	}
	
	if (zombieStatus == ZombieStatus::isNormal)
	{
		
#pragma region Move To Right

		if (Input::CreateInstance()->IsKeyDown(DIK_RIGHT))
		{
			this->_isFlipX = false;
			this->vX = 90;
			this->isOnFoot = true;
			
			//Right - Up
			if (Input::CreateInstance()->IsKeyDown(DIK_UP))
			{
				if (animationStatus == AnimationStatus::isRun || animationStatus == AnimationStatus::isInit)
				{
					animationStatus = AnimationStatus::isFireUp;
					this->setAnimation(9, 9, 12);
				}
			}
			//Right - Down
			else if (Input::CreateInstance()->IsKeyDown(DIK_DOWN))
			{
				if (animationStatus == AnimationStatus::isRun || animationStatus == AnimationStatus::isInit)
				{
					animationStatus = AnimationStatus::isFireDown;
					this->setAnimation(0, 1, 3);
				}
			}

			//Right
			else
			{

				if (animationStatus == AnimationStatus::isInit)
				{
					animationStatus = AnimationStatus::isRun;

					this->setAnimation(3,4,6);
					
				}
			}
		}

#pragma endregion

#pragma region Move To Left


		else if (Input::CreateInstance()->IsKeyDown(DIK_LEFT))
		{
			this->_isFlipX = true;
			this->vX = -90;
			this->isOnFoot = true;

			//Left - Up
			if (Input::CreateInstance()->IsKeyDown(DIK_UP))
			{
				if (animationStatus == AnimationStatus::isRun || animationStatus == AnimationStatus::isInit)
				{
					animationStatus = AnimationStatus::isFireUp;
					this->setAnimation(9, 9, 12);
				}
			}
			//Left - Down
			else if (Input::CreateInstance()->IsKeyDown(DIK_DOWN))
			{
				if (animationStatus == AnimationStatus::isRun || animationStatus == AnimationStatus::isInit)
				{
					animationStatus = AnimationStatus::isFireDown;
					this->setAnimation(0, 1, 3);
				}
			}
			//Left
			else
			{
				if (animationStatus == AnimationStatus::isInit)
				{
					animationStatus = AnimationStatus::isRun;
					this->setAnimation(3, 4, 6);
				}
			}
		}
		
#pragma endregion

#pragma region Stand
		else
		{
			this->vX = 0;

			if (Input::CreateInstance()->IsKeyDown(DIK_Z))
			{
				if (animationStatus == AnimationStatus::isInit)
				{
					animationStatus = AnimationStatus::isFire;
					this->setAnimation(3, 3, 3);
				}
			}
			else
			{
				this->setAnimation(3, 3, 3);
				this->isOnFoot = false;
			}
		}

#pragma endregion
		
	}

	//On release all keys
	if (iskeyUp == DIK_LEFT || iskeyUp == DIK_RIGHT || iskeyUp == DIK_UP || iskeyUp == DIK_DOWN || iskeyUp == DIK_Z)
	{
		animationStatus = AnimationStatus::isInit;
	}
	
	if (this->getPositionY() < 100 && zombieStatus != ZombieStatus::islyingDown)
	{
		this->setPositionY(100);
		this->vY = 0;
		this->isJump = true;
		this->animationStatus = AnimationStatus::isInit;
		zombieStatus = ZombieStatus::isNormal;
	}
	
	this->setPosition(this->getPositionX() + this->vX * dt, this->getPositionY() + this->vY * dt);

	
	this->_rectRS = cropRect(dt);
	
}

void Zombie::updateRECT()
{
	//Stand
	/*if (animationStatus == AnimationStatus::isInit)
	{
		this->setAnimation(3, 3, 3);
	}*/
	//Run
	/*if (animationStatus == AnimationStatus::isRun)
	{
		animationStatus = AnimationStatus::isNormal;
		index = 4;
		lastFrame = 6;
		firstFrame = 3;
	}*/
	//Up - R - L
	/*if (animationStatus == AnimationStatus::isFireUp)
	{
		animationStatus = AnimationStatus::isFireDown;
		this->setAnimation(9, 9, 12);
	}*/


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

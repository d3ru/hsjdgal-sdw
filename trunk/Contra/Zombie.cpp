#include "Zombie.h"
#include "SpriteManager.h"
#include"Input.h"
#include"BulletFactory.h"

static Zombie* instance = nullptr;

Zombie* Zombie::createInstance(GameNode gameNode)
{
	if (instance == nullptr)
		instance = new Zombie(gameNode);
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

Zombie::Zombie(GameNode node)
{
	this->ID = node.ID;

	this->ID_Image = node.IDIMAGE;

	this->_isAnimation = true;

	this->setContainSize(node.CONTAINSIZE);


	this->setPosition(node.POSITION);

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
	if (this->getPositionY() >= 390 && zombieStatus == ZombieStatus::isOnAir)
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
			this->vX = 100;
			this->isOnFoot = true;
			this->isMove = true;
			
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
					//this->setAnimation(6, 7, 9, 0.2);
					
				}
			}
		}

#pragma endregion

#pragma region Move To Left


		else if (Input::CreateInstance()->IsKeyDown(DIK_LEFT))
		{
			this->_isFlipX = true;
			this->vX = -100;
			this->isOnFoot = true;
			this->isMove = true;


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
			this->isMove = false;


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
	
	if (this->getPositionY() < 280 && zombieStatus != ZombieStatus::islyingDown)
	{
		this->setPositionY(280);
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


void Zombie::collision(float dt, std::vector<HideObject*> listObjectCollision)
{
	this->_box = this->getBox();

	float normalX = 0;
	float normalY = 0;

	float timeCollision;
	if (this->isMove)
	{

		for (auto objCollision : listObjectCollision)
		{
			timeCollision = this->getTimeCollision(objCollision, normalX, normalY, dt);

			if (timeCollision == 2.0f)
			{
				this->setPositionX(10);
			}
			
		}
	}
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

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

	this->vX = 0.0f;

	this->vY = 0;

	this->directionY = 1;

	this->detalA = 20;

	this->setZOther(1);


	this->zombieStatus = ZOMBIESTATUS::RESET;
	this->animationStatus = ANIMATIONSTATUS::INIT;

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

	this->setAnimation(3,3,3);

}

void Zombie::update(float dt)
{
	
	this->proccessKeyBoard();

	//Update position of Rambo
	this->vY -= this->detalA * this->directionY;
	this->setPosition(this->getPositionX() + this->vX * dt, this->getPositionY() + this->vY * dt);

	//Update animation of Ranbo
	this->_rectRS = cropRect(dt);

}

void Zombie::proccessKeyBoard()
{
	//Init KeyBoard
	Input::CreateInstance()->ProcessKeyboard();
	Input::CreateInstance()->Update();

	int isKeyDown = Input::CreateInstance()->GetKeyDown();
	int iskeyUp = Input::CreateInstance()->GetKeyUp();

	//************************************* -QUA PHAI- *************************************//

	if (zombieStatus == ZOMBIESTATUS::ONLAND && Input::CreateInstance()->IsKeyDown(DIK_RIGHT))
	{
		this->isMove = false;
		this->vX = 100.0f;
		this->_isFlipX = false;

		//Di thang sang phai huong suong len tren
		if (Input::CreateInstance()->IsKeyDown(DIK_UP))
		{
			if (animationStatus == ANIMATIONSTATUS::INIT || animationStatus == ANIMATIONSTATUS::RUN)
			{
				animationStatus = ANIMATIONSTATUS::FIRE;
				this->setAnimation(9,9,12);
			}

		}

		//Di thang sangp phai huong sung xuong duoi
		else if (Input::CreateInstance()->IsKeyDown(DIK_DOWN))
		{
			if (animationStatus == ANIMATIONSTATUS::INIT || animationStatus == ANIMATIONSTATUS::RUN)
			{
				animationStatus = ANIMATIONSTATUS::FIRE;
				this->setAnimation(0, 1, 3);
			}
		}
		
		else
		{
			//Di thang qua phai
			if (animationStatus == ANIMATIONSTATUS::INIT)
			{
				animationStatus = ANIMATIONSTATUS::RUN;
				this->setAnimation(3, 4, 6);
			}
		}
	}

	//************************************* -QUA TRAI- *************************************//


	else if (zombieStatus == ZOMBIESTATUS::ONLAND && Input::CreateInstance()->IsKeyDown(DIK_LEFT))
	{
		this->isMove = true;
		this->vX = -100.0f;
		this->_isFlipX = true;
		
		//Di thang sang trai huong suong len tren
		if (Input::CreateInstance()->IsKeyDown(DIK_UP))
		{
			if (animationStatus == ANIMATIONSTATUS::INIT || animationStatus == ANIMATIONSTATUS::RUN)
			{
				animationStatus = ANIMATIONSTATUS::FIRE;
				this->setAnimation(9, 9, 12);
			}

		}

		//Di thang sangp trai huong sung xuong duoi
		else if (Input::CreateInstance()->IsKeyDown(DIK_DOWN))
		{
			if (animationStatus == ANIMATIONSTATUS::INIT || animationStatus == ANIMATIONSTATUS::RUN)
			{
				animationStatus = ANIMATIONSTATUS::FIRE;
				this->setAnimation(0, 1, 3);
			}
		}

		else
		{
			//Di thang qua trai
			if (animationStatus == ANIMATIONSTATUS::INIT)
			{
				animationStatus = ANIMATIONSTATUS::RUN;
				this->setAnimation(3, 4, 6);
			}
		}
	}

	//************************************* -DUNG YEN- *************************************//

	else if (zombieStatus == ZOMBIESTATUS::ONLAND)
	{
		this->isMove = false;
		this->setAnimation(3,3,3);
		this->vX = 0.0;
		
	}

	//************************************* -NAM XUONH- *************************************//
	if (zombieStatus == ZOMBIESTATUS::ONLAND && Input::CreateInstance()->IsKeyDown(DIK_DOWN))
	{
		zombieStatus = ZOMBIESTATUS::LYINGDOWN;
		this->vX = 0.0;
		this->setAnimation(14,14,14);
		this->setContainSize(82, 30);
		this->detalA = 100;
	
	}

	//************************************* -NHAY LEN- *************************************//
	if (zombieStatus == ZOMBIESTATUS::ONLAND && Input::CreateInstance()->IsKeyDown(DIK_SPACE) && isJump)
	{
		zombieStatus = ZOMBIESTATUS::ONARI;
		this->vY = 500;
		this->setAnimation(17, 19, 20);
		this->setContainSize(30, 30);
		this->isJump = false;

	}



	//On release all Keys
	if (iskeyUp == DIK_LEFT || iskeyUp == DIK_RIGHT || iskeyUp == DIK_DOWN || iskeyUp == DIK_UP)
	{
		animationStatus = ANIMATIONSTATUS::INIT;

		if (zombieStatus == ZOMBIESTATUS::LYINGDOWN)
		{
			zombieStatus = ZOMBIESTATUS::ONLAND;
			this->setContainSize(30,92);
		}
	}

	
}

void Zombie::collision(float dt, std::vector<HideObject*> listObjectCollision)
{
	this->_box = this->getBox();

	float normalX = 0;
	float normalY = 0;

	float timeCollision;
	//if (this->isMove)
	{

		
		for (auto objCollision : listObjectCollision)
		{
			timeCollision = this->getTimeCollision(objCollision, normalX, normalY, dt);

			if (timeCollision == 2.0f)
			{
				this->setPositionX(this->getPositionX() + normalX);
				this->setPositionY(this->getPositionY() + normalY);

				this->detalA = 0;
				this->vY = 0;

				if (zombieStatus == ZOMBIESTATUS::RESET)
					zombieStatus = ZOMBIESTATUS::ONLAND;
				if (zombieStatus == ZOMBIESTATUS::ONARI)
				{
					zombieStatus = ZOMBIESTATUS::ONLAND;
					this->setContainSize(30,92);
					this->isJump = true;
				}


				
				if (normalY == 1 || normalY == -1)
				{
					int j = 8;
				}


				if (normalX == 1 || normalX == -1)
				{
					int k = 9;
				}

			}
			 
			if (timeCollision < 1.0f)
			{
				 if (normalX == 1 || normalX == -1)
				 {
					 int k = 9;
				 }
				 
				 if (normalY == 1 || normalY == -1)
				 {
					 int j = 8;
				 }
			}
			else if (timeCollision == 1.0)
			{
				
				int b = 3;
				this->detalA = 20;
			}

		
		}
	}
}

void Zombie::draw()
{
	SpriteManager::createInstance()->drawObj(this);
	
}

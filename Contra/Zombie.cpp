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

Zombie::~Zombie()
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
	this->collisionStatus = COLLISIONSTATUS::NOPE;

	for (int i = 0; i < 10; i++)
	{
		auto rect = new RECT();

		rect->left = i * 68;
		rect->right = rect->left + 68;
		rect->top = 0;
		rect->bottom = rect->top + 92;

		listRect.push_back(rect);
	}

	for (int i = 0; i < 6; i++)
	{
		auto rect = new RECT();

		rect->left = i * 68;
		rect->right = rect->left + 68;
		rect->top = 92;
		rect->bottom = rect->top + 92;

		listRect.push_back(rect);
	}

	for (int i = 0; i < 6; i++)
	{
		auto rect = new RECT();

		rect->left = i * 68 + 408;
		rect->right = rect->left + 68;
		rect->top = 150;
		rect->bottom = rect->top + 35;

		listRect.push_back(rect);
	}

	for (int i = 0; i < 2; i++)
	{
		auto rect = new RECT();

		rect->left = i * 68 + 476;
		rect->right = rect->left + 68;
		rect->top = 241;
		rect->bottom = rect->top + 35;

		listRect.push_back(rect);
	}

	//Lan xuong nuoc
	auto rect = new RECT();

	rect->left = 409;
	rect->right = rect->left + 68;
	rect->top = 260;
	rect->bottom = rect->top + 16;

	listRect.push_back(rect);

	//Nam xuong
	auto rect1 = new RECT();

	rect1->left = 0;
	rect1->right = 68;
	rect1->top = 241;
	rect1->bottom = 276;

	listRect.push_back(rect1);

	
	this->setAnimation(0,0,0);

}


void Zombie::update(float dt)
{
	this->proccessKeyBoard(dt);

	//Update position of Rambo
	this->vY -= this->detalA * this->directionY;
	this->setPosition(this->getPositionX() + this->vX * dt, this->getPositionY() + this->vY * dt);

	//Update animation of Ranbo
	this->_rectRS = cropRect(dt);

}

void Zombie::proccessKeyBoard(float dt)
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
		this->vX = 120;
		this->_isFlipX = false;

		//Di thang sang phai huong suong len tren
		if (Input::CreateInstance()->IsKeyDown(DIK_UP))
		{
			if (animationStatus == ANIMATIONSTATUS::INIT || animationStatus == ANIMATIONSTATUS::RUN)
			{
				animationStatus = ANIMATIONSTATUS::FIRE;
				this->setAnimation(4,4,7, 0.15);
			}

		}

		//Di thang sangp phai huong sung xuong duoi
		else if (Input::CreateInstance()->IsKeyDown(DIK_DOWN))
		{
			if (animationStatus == ANIMATIONSTATUS::INIT || animationStatus == ANIMATIONSTATUS::RUN)
			{
				animationStatus = ANIMATIONSTATUS::FIRE;
				this->setAnimation(7, 8, 10, 0.15);
			}
		}
		
		else
		{
			//Di thang qua phai
			if (animationStatus == ANIMATIONSTATUS::INIT)
			{
				animationStatus = ANIMATIONSTATUS::RUN;
				this->setAnimation(10, 11, 16, 0.15);
			}
		}
	}

	//************************************* -QUA TRAI- *************************************//


	else if (zombieStatus == ZOMBIESTATUS::ONLAND && Input::CreateInstance()->IsKeyDown(DIK_LEFT))
	{
		this->isMove = true;
		this->vX = -120.0f;
		this->_isFlipX = true;
		
		//Di thang sang trai huong suong len tren
		if (Input::CreateInstance()->IsKeyDown(DIK_UP))
		{
			if (animationStatus == ANIMATIONSTATUS::INIT || animationStatus == ANIMATIONSTATUS::RUN)
			{
				animationStatus = ANIMATIONSTATUS::FIRE;
				this->setAnimation(4, 4, 7, 0.15);
			}

		}

		//Di thang sangp trai huong sung xuong duoi
		else if (Input::CreateInstance()->IsKeyDown(DIK_DOWN))
		{
			if (animationStatus == ANIMATIONSTATUS::INIT || animationStatus == ANIMATIONSTATUS::RUN)
			{
				animationStatus = ANIMATIONSTATUS::FIRE;
				this->setAnimation(7, 8, 10, 0.15);
			}
		}

		else
		{
			//Di thang qua trai
			if (animationStatus == ANIMATIONSTATUS::INIT)
			{
				animationStatus = ANIMATIONSTATUS::RUN;
				this->setAnimation(10, 10, 16, 0.15);
			}
		}
	}

	//************************************* -NAM XUONH- *************************************//
	else if (zombieStatus == ZOMBIESTATUS::ONLAND && Input::CreateInstance()->IsKeyDown(DIK_DOWN))
	{
		zombieStatus = ZOMBIESTATUS::LYINGDOWN;

		this->vX = 0.0;
		this->setAnimation(25, 25, 25);
		this->setContainSize(68, 35);
		this->detalA = 100;

	}

	//************************************* -DUNG BAN LEN- *************************************//

	else if (zombieStatus == ZOMBIESTATUS::ONLAND && Input::CreateInstance()->IsKeyDown(DIK_UP))
	{
		if (Input::CreateInstance()->IsKeyDown(DIK_Z) && animationStatus == ANIMATIONSTATUS::INIT)
		{
			animationStatus = ANIMATIONSTATUS::FIRE;
			this->setAnimation(2,2,4);
		}
	}


	//************************************* -DUNG YEN- *************************************//

	else if (zombieStatus == ZOMBIESTATUS::ONLAND)
	{
		this->isMove = false;
		this->setAnimation(0,0,0);
		this->vX = 0.0;
		
	}

	

	/*if (zombieStatus == ZOMBIESTATUS::LYINGDOWN && Input::CreateInstance()->IsKeyDown(DIK_SPACE))
	{
		zombieStatus = ZOMBIESTATUS::FALLING;
		this->setAnimation(3,3,3);
	}

	if (zombieStatus == ZOMBIESTATUS::FALLING && iskeyUp == DIK_SPACE)
	{
		zombieStatus = ZOMBIESTATUS::ONLAND;
	}*/

	//************************************* -NHAY LEN- *************************************//
	if (zombieStatus == ZOMBIESTATUS::ONLAND && Input::CreateInstance()->IsKeyDown(DIK_SPACE) && isJump)
	{
		zombieStatus = ZOMBIESTATUS::ONARI;
		this->vY = 425;
		this->setAnimation(16, 16, 20);
		this->setContainSize(35, 35);
		this->isJump = false;

	}
	// Nhay len bay sang phai
	if (zombieStatus == ZOMBIESTATUS::ONARI && Input::CreateInstance()->IsKeyDown(DIK_RIGHT) && !isMove)
	{
		isMove = true;
		this->_isFlipX = false;
		this->vX = 100;
	}
	//Nhay len bay sang trai
	if (zombieStatus == ZOMBIESTATUS::ONARI && Input::CreateInstance()->IsKeyDown(DIK_LEFT) && !isMove)
	{
		isMove = true;
		this->vX = -100;
		this->_isFlipX = true;
	}

	//************************************* -DUOI NUOC- *************************************//

	if (zombieStatus == ZOMBIESTATUS::UNDERWATER && Input::CreateInstance()->IsKeyDown(DIK_RIGHT) && zombieStatus != ZOMBIESTATUS::HIDE)
	{
		
		this->_isFlipX = false;
		
		this->vX = 120.0f;

		if (zombieStatus == ZOMBIESTATUS::UNDERWATER && Input::CreateInstance()->IsKeyDown(DIK_Z) && animationStatus == ANIMATIONSTATUS::INIT)
		{
			animationStatus = ANIMATIONSTATUS::FIRE;
			this->setAnimation(23, 23, 23);
		}
	}

	else if (zombieStatus == ZOMBIESTATUS::UNDERWATER && Input::CreateInstance()->IsKeyDown(DIK_LEFT) && zombieStatus != ZOMBIESTATUS::HIDE)
	{
		
		this->_isFlipX = true;
		
		this->vX = -120.0f;

		if (Input::CreateInstance()->IsKeyDown(DIK_Z) && animationStatus == ANIMATIONSTATUS::INIT)
		{
			animationStatus = ANIMATIONSTATUS::FIRE;
			this->setAnimation(23,23,23);
		}

	}

	else if (zombieStatus == ZOMBIESTATUS::UNDERWATER && Input::CreateInstance()->IsKeyDown(DIK_Z))
	{
		this->deltaTimeFire = 0;
		this->setAnimation(23, 23, 23);
		
	}
	

	else if (zombieStatus == ZOMBIESTATUS::UNDERWATER && Input::CreateInstance()->IsKeyDown(DIK_DOWN))
	{
		zombieStatus = ZOMBIESTATUS::HIDE;
		this->vX = 0.0f;
		this->setContainSize(35, 16);
		this->setAnimation(24, 24, 24);
		
	}

	else if (zombieStatus == ZOMBIESTATUS::UNDERWATER)
	{

		this->vX = 0.0;
		this->setAnimation(22,22,22);
		this->setContainSize(35,35);		
		
	}

	
	

	//On release all Keys
	if (iskeyUp == DIK_LEFT || iskeyUp == DIK_RIGHT || iskeyUp == DIK_DOWN || iskeyUp == DIK_UP )
	{
		animationStatus = ANIMATIONSTATUS::INIT;
		this->isMove = true;
		if (zombieStatus == ZOMBIESTATUS::LYINGDOWN)
		{
			zombieStatus = ZOMBIESTATUS::ONLAND;
			this->setContainSize(30,92);
		}
		if (zombieStatus == ZOMBIESTATUS::UNDERWATER)
		{
			this->setContainSize(35,35);
		}
		if (zombieStatus == ZOMBIESTATUS::HIDE)
		{
			zombieStatus = ZOMBIESTATUS::UNDERWATER;
			this->setAnimation(22, 22, 22);
			this->setContainSize(35, 35);
		}
	}


	
}

void Zombie::collision(float dt, std::vector<HideObject*> listObjectCollision)
{
	this->_box = this->getBox();

	float normalX = 0;
	float normalY = 0;

	float timeCollision;
	
	{

		
		for (auto objCollision : listObjectCollision)
		{
			timeCollision = this->getTimeCollision(objCollision, normalX, normalY, dt);

			if (timeCollision == 2.0f )
			{
				
				if (objCollision->typeObject == TYPEOBJECT::GROUND )
				{
					
					collisionStatus = COLLISIONSTATUS::GROUND;
					this->setPositionY(this->getPositionY() + normalY);
					this->detalA = 0;
					this->vY = 0;

					if (zombieStatus == ZOMBIESTATUS::RESET)
						zombieStatus = ZOMBIESTATUS::ONLAND;
					if (zombieStatus == ZOMBIESTATUS::ONARI)
					{
						zombieStatus = ZOMBIESTATUS::ONLAND;
						animationStatus = ANIMATIONSTATUS::INIT;
						this->setContainSize(30, 92);
						this->isJump = true;
					}
				}

				if (objCollision->typeObject == TYPEOBJECT::SWITCH)
				{
					collisionStatus = COLLISIONSTATUS::SWITCH;
					if (zombieStatus == ZOMBIESTATUS::ONLAND || zombieStatus == ZOMBIESTATUS::ONARI)
					{
						this->setAnimation(3, 3, 3);
						if (this->_isFlipX == false)
							this->vX = 80;
						else
						{
							this->vX = -80;
						}
					}
				}	

				//Va cham voi nuoc
				if (objCollision->typeObject == TYPEOBJECT::WATER)
				{
					if (zombieStatus == ZOMBIESTATUS::ONLAND)
					{
						zombieStatus = ZOMBIESTATUS::UNDERWATER;
						animationStatus = ANIMATIONSTATUS::INIT;
					}
					this->setPositionY(this->getPositionY() + normalY);
					//this->setAnimation(20,20,20);
					this->vY = 0;
					this->detalA = 0;
					
				}
				

			}

			
			 
			if (timeCollision < 1.0f)
			{
				/*if (normalX == -1)
				{
					this->setPositionX(this->getPositionX() + normalX);
					if (objCollision->typeObject == TYPEOBJECT::SWITCH)
					{
						
						this->vX = 80;
					}
				}

				if (normalX == 1)
				{
					this->setPositionX(this->getPositionX() + normalX);
					if (objCollision->typeObject == TYPEOBJECT::SWITCH)
					{
						
						this->vX = -80;
					}
				}


				if (normalY == 1 || normalY == -1)
				{
					int j = 9;
				}
*/
				//this->collisionStatus = COLLISIONSTATUS::NOPE;
			}
			else if (timeCollision == 1.0)
			{
				
				int b = 3;
				this->detalA = 20;
				this->collisionStatus = COLLISIONSTATUS::NOPE;
				
			}

		
		}
	}
}

void Zombie::draw()
{
	SpriteManager::createInstance()->drawObj(this);
	
}

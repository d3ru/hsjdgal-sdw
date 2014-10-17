#include "Ball.h"
#include"SpriteManager.h"
#include"Input.h"

static Ball* instance = nullptr;

Ball* Ball::getInstance()
{
	if (instance == nullptr)
		instance = new Ball();
	return instance;
}

Ball* Ball::createInstance(std::vector<std::string> arr)
{
	if (instance == nullptr)
		instance = new Ball(arr);
	return instance;
}

Ball::Ball()
{}

Ball::Ball(std::vector<std::string> arr)
{
	this->ID = atoi(arr.at(0).c_str());
	this->ID_Image = atoi(arr.at(1).c_str());

	

	this->_position.x = 400;
	this->_position.y = 300;


	vX = (((rand() % 80) + 20) * (rand() % 2 == 0 ? 1 : -1)) * 2.0;
	vY = (((rand() % 80) + 40) * (rand() % 2 == 0 ? 1 : -1)) * 2.0;


	this->setZOther(1);

}

void Ball::processInput()
{
	//Input::createInstance()->ProcessKeyboard();
	//Input::createInstance()->Update();

	//int key_down = Input::createInstance()->GetKeyDown();
	//int key_up = Input::createInstance()->GetKeyUp();

	


	/*if (Input::createInstance()->IsKeyDown(DIK_RIGHT))
	{
		vX = 3.0;
	}
	else if ((Input::createInstance()->IsKeyDown(DIK_LEFT)))
	{
		vX = -3.0;
	}
	else
	{
		vX = 0.0;
	}
*/
	
}

void Ball::update(float dt)
{
	processInput();
	if (this->getPositionX() >= 800 - this->getContainSize().width / 2 || this->getPositionX() <= this->getContainSize().width / 2)
		vX = -vX;
	if (this->getPositionY() >= 600  || this->getPositionY() <= this->getContainSize().height)
		vY = -vY;
	if (this->getPositionX() >= 800 - this->getContainSize().width / 2)
		this->setPositionX(800 - this->getContainSize().width / 2);
	if (this->getPositionX() <=  this->getContainSize().width / 2)
		this->setPositionX(this->getContainSize().width / 2);
	if (this->getPositionY() >= 600)
		this->setPositionY(600);
	if (this->getPositionY() <= this->getContainSize().height)
		this->setPositionY(this->getContainSize().height);
	
	this->setPosition(this->getPositionX() + vX*dt, this->getPositionY() + vY*dt);
}

void Ball::draw()
{
	SpriteManager::createInstance()->drawObj(this);
}

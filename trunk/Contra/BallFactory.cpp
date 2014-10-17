#include "BallFactory.h"
#include <time.h>

static BallFactory* instance = nullptr;

BallFactory* BallFactory::getInstance()
{
	if (instance == nullptr)
		instance = new BallFactory();
	return instance;
}

Ball* BallFactory::createObj()
{
	return Ball::createInstance(info.at(0));
}

std::vector<Ball*>* BallFactory::createListBall()
{
	
	auto listBall = new std::vector<Ball*>();

	for (int i = 0; i < 20; i++)
	{
		Ball* ball = new Ball(info.at(0));
		listBall->push_back(ball);
	}

	return listBall;
}

BallFactory::BallFactory() 
{
}



#ifndef __PALLFACTORY__H__
#define __PALLFACTORY__H__

#include"ObjectFactory.h"
#include"Ball.h"

class BallFactory : public ObjectFactory
{
public:

	static BallFactory* getInstance();

	Ball* createObj();

	std::vector<Ball*>* createListBall();

	BallFactory();
	

};

#endif

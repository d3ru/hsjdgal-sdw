#ifndef __PALL__H__
#define __PALL__H__

#include"ObjectGame.h"

class Ball : public ObjectGame
{
public:
	Ball();

	static Ball* getInstance();

	static Ball* createInstance(std::vector<std::string>);

	Ball(std::vector<std::string>);

	virtual void update(float dt) override;

	void processInput();

	float vX;

	float vY;

	void draw();
};

#endif


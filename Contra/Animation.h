#ifndef __ANIMATION__H__
#define __ANIMATION__H__

#include <d3d9.h>
#include<vector>

class Animation
{
public:
	
	float _beforeTimeOld;
	
	void setAnimation(int , int, int, float frameTime = 0.1);

	RECT* cropRect(float dt);

	std::vector<RECT*> listRect;

private:

	int index;

	int lastFrame;

	int firstFrame;	

	float frameRateTime;
};

#endif
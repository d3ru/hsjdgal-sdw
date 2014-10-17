#ifndef __ANIMATION__H__
#define __ANIMATION__H__

#include <d3d9.h>
#include<vector>

class Animation
{
public:
	
	float _elapseTimeSwitchFrame;

	float _beforeTimeOld;

	int _currentFrame;

	int _increase;

	int _totalFrames;

	int _columm;

	RECT* updateRectRS(int Width, int Height);

	Animation();

	Animation(int curFrame, int, int totalFrames, int coloumn, float elapseTimeSwitchFrame);

    void animated(float dt);

	int index;

	int lastFrame;

	int firstFrame;

	std::vector<RECT*> listRect;
	

	RECT* cropRect(float dt);
	
};

#endif
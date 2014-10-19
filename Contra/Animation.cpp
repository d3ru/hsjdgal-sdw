#include "Animation.h"

void Animation::setAnimation(int FirsFrame, int Index, int LastFrame, float FrameRateTime)
{
	firstFrame = FirsFrame;

	index = Index;

	lastFrame = LastFrame;

	frameRateTime = FrameRateTime;
}


RECT* Animation::cropRect(float dt)
{

	_beforeTimeOld += dt;

	if (_beforeTimeOld > frameRateTime)
	{
		index++;
		if (index >= lastFrame)
		{
			index = firstFrame;
		}
		_beforeTimeOld = 0;
	}

	return listRect[index];

}

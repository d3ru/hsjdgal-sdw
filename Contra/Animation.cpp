#include "Animation.h"


Animation::Animation()
{
}


Animation::Animation(int curFrame, int, int totalFrames, int coloumn, float elapseTimeSwitchFrame)
{
	_currentFrame = curFrame;

	_totalFrames = totalFrames;

	_columm = coloumn;

	_elapseTimeSwitchFrame = elapseTimeSwitchFrame;
}

void Animation::animated(float dt)
{
	_beforeTimeOld += dt;

	if (_beforeTimeOld > _elapseTimeSwitchFrame)
	{
		_currentFrame++;
		if (_currentFrame >= _totalFrames)
		{
			_currentFrame = 0;
		}
		_beforeTimeOld -= _elapseTimeSwitchFrame;
	}
}


RECT* Animation::updateRectRS(int Width, int Height)
{
	RECT* rectRS = new RECT();

	rectRS->left = (_currentFrame % _columm) * Width;
	rectRS->right = rectRS->left + Width;
	rectRS->top = (_currentFrame / _columm) * Height;
	rectRS->bottom = rectRS->top + Height;

	return rectRS;
}

RECT* Animation::cropRect(float dt)
{

	_beforeTimeOld += dt;

	if (_beforeTimeOld > 0.1)
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

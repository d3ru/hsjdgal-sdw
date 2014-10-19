#include "Camera.h"
#include "config.h"


Camera::Camera()
{
	_position.x = 0;
	_position.y = Screen_Height;
	_position.z = 0;

	stopScrollScreen = false;

	donePrepare = false;

	speedX = 100;

	D3DXMatrixIdentity(&_MatrixTransform);
	_MatrixTransform._22 = -1;
}

D3DXVECTOR3 Camera::getPosCamera()
{
	return _position;
}

void Camera::setBound(RECT rect)
{
	this->_boundScene = rect;
}

RECT Camera::getScreen()
{
	RECT rect;

	rect.left = this->_position.x;
	rect.right = rect.left + Screen_Width;
	rect.top = this->_position.y;
	rect.bottom = rect.top - Screen_Height;

	return rect;
}

D3DXVECTOR3 Camera::getPointTransform(float x, float y)
{

	_MatrixTransform._41 = -_position.x;
	_MatrixTransform._42 = _position.y;

	D3DXVECTOR4 v_result;
	D3DXVECTOR3 posOld(x, y, 0);

	D3DXVec3Transform(&v_result, &posOld, &_MatrixTransform);

	return D3DXVECTOR3(v_result.x, v_result.y, v_result.z);
}

void Camera::update(float XX, float dt)
{
	if (!donePrepare)
	{
		float xTarget = XX - Screen_Width / 2;

		if (!stopScrollScreen)
		{
			_position.x = (int)xTarget;

			if (_position.x < _boundScene.left)
				_position.x = _boundScene.left;
			if (_position.x > _boundScene.right - Screen_Width / 2)
				_position.x = _boundScene.right - Screen_Width / 2;
		}
	}
}

bool Camera::move(float Vx, float PosXTarget, float dt, bool dir)
{
	if (!donePrepare)
	{
		this->posXTarget = PosXTarget;
		this->donePrepare = true;

		return false;
	}
	else
	{
		int direction = dir ? -1 : 1;

		float xTarget = this->posXTarget - Screen_Width / 2;
		float distance = (xTarget - _position.x) * direction;

		if (distance > Vx * dt)
		{
			_position.x += Vx * dt;

			return false;
		}
		else
		{
			_position.x = xTarget;
			this->donePrepare = false;

			return true;
		}
	}
}
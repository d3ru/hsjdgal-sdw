#include "ObjectGame.h"


ObjectGame::ObjectGame()
{}

ObjectGame::~ObjectGame()
{}

ObjectGame::ObjectGame(std::vector<std::string> arr)
{}

RECT ObjectGame::getRect()
{
	_rect.top = this->getPosition().y + _containtSize.height / 2;
	_rect.bottom = _rect.top - _containtSize.height;
	_rect.left = this->getPosition().x - _containtSize.width / 2;
	_rect.right = _rect.left + _containtSize.width;

	return _rect;
}

void ObjectGame::setContainSize(float width, float height)
{
	_containtSize.width = width;
	_containtSize.height = height;
}

Size ObjectGame::getContainSize()
{
	return _containtSize;
}

void ObjectGame::setPosition(float x, float y)
{
	_position.x = x;
	_position.y = y;
}

void ObjectGame::setPosition(Point pos)
{
	setPosition(pos.x, pos.y);
}

void ObjectGame::setPositionX(float x)
{
	_position.x = x;
}

void ObjectGame::setPositionY(float y)
{
	_position.y = y;
}

Point ObjectGame::getPosition()
{
	return Point(_position.x, _position.y);
}

float ObjectGame::getPositionX()
{
	return _position.x;
}

float ObjectGame::getPositionY()
{
	return _position.y;
}

void ObjectGame::update(float dt)
{ 
}

void ObjectGame::setZOther(float Z)
{
	_zOther = Z;
}

float ObjectGame::getZOther()
{
	return _zOther;
}
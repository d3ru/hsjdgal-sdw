#include "ObjectGame.h"


ObjectGame::ObjectGame()
{}

ObjectGame::~ObjectGame()
{}

ObjectGame::ObjectGame(GameNode node)
{}


void ObjectGame::setContainSize(float width, float height)
{
	_containtSize.width = width;
	_containtSize.height = height;
}

void ObjectGame::setContainSize(Size Size)
{
	setContainSize(Size.width, Size.height);
}

Box ObjectGame::getBox()
{
	_box = Box(_position.x, _position.y, _containtSize.width, _containtSize.height);

	return _box;
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
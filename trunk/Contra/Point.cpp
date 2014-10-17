#include "Point.h"


Point::Point()
{
	this->x = 0;
	this->y = 0;
}

Point::Point(float X, float Y)
{
	this->x = X;
	this->y = Y;
}


Point::~Point()
{
}

Size::Size()
{ 
	width = 0;
	height = 0;
}

Size::Size(float xx, float yy) 
{
	width = xx;
	height = yy;
}

#ifndef __POINT__H__
#define __POINT__H__


class Point
{
public:
	float x;
	float y;
	Point();
	Point(float, float);
	~Point();
};

class Size
{	
public:

	float width;
	float height;
	Size();
	Size(float, float);
};

#endif

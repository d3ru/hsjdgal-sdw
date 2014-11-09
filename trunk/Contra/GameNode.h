#ifndef __GAMENODE__H__
#define __GAMENODE__H__


#pragma once

#include"Point.h"

class GameNode
{
public:
	GameNode();

	GameNode(int, int, Point, Size);
	
	int ID;

	int IDIMAGE;

	Point POSITION;

	Size CONTAINSIZE;



};


#endif

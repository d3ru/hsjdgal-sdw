#ifndef __TILE__H__
#define __TILE__H__

#include"Point.h"
#include"d3dx9.h"

#pragma once

enum class TileStatus
{
	isNormal,
	isHide,
};

class Tile
{
public:
	Tile();
	~Tile();

	TileStatus tileStaus = TileStatus::isNormal;

	int IDTile;

	Point posTile;

};


#endif

#ifndef __BACKGROUND__H__
#define __BACKGROUND__H__


#include"TextureManager.h"
#include"Tile.h"

#pragma once

class BackGround
{
public:

	static BackGround* createInstance();

	BackGround();
	~BackGround();

	void readData(std::string filePath);

	void checkTileInBound(RECT rect);

	void drawBackGround();

private:

	int _idTexture;

	int _column; //Number column of tile map

	int _row; //Number row of tile map

	int _size; //Size per tile 8x8 16x16 32x32

	int _numTile; //Number tile of texture

	Texture* _texture; //Texture of map

	Tile** _matrix;
	
	void transforMatrix(std::vector<std::string>, int);//Add info of Tile to matrix

	RECT getRectByID(int); //get RECT by ID for draw

	std::vector<Tile> listTile;

};

#endif
#include "BackGround.h"
#include <fstream>
#include"FileUtils.h"
#include"config.h"
#include"SpriteManager.h"


static BackGround* instance = nullptr;

BackGround* BackGround::createInstance()
{
	if (instance == nullptr)
		instance = new BackGround();
	return instance;
}

BackGround::BackGround()
{
	this->_matrix = nullptr;
	this->_texture = TextureManager::getInstance()->getTetureByKey(1005);
}


BackGround::~BackGround()
{
	if (_matrix)
		delete[] _matrix;
}

void BackGround::readData(std::string filePath)
{
	std::string line;
	std::vector<std::string> arr;
	std::vector<std::vector<std::string>> info;

	std::ifstream* myfile = new std::ifstream(filePath);

	if (myfile->is_open())
	{
		getline(*myfile, line);
	}

	//Read info tileMap - size - column - row
	arr = FileUtils::getInstance()->split(line, '\t');
	_size = atoi(arr.at(0).c_str());
	_column = atoi(arr.at(1).c_str());
	_row = atoi(arr.at(2).c_str());
	_numTile = atoi(arr.at(3).c_str());

	//Matrix
	_matrix = new Tile*[_column];
	for (int i = 0; i < _column; i++)
	{
		_matrix[i] = new Tile[_row];
	}

	//Read data tileMap
	int row = 0;
	while (!myfile->eof())
	{
		if (getline(*myfile, line))
		{
			if (line != "")
			{
				arr = FileUtils::getInstance()->split(line, '\t');
				transforMatrix(arr, row);
				row++;
			}
		}
	}

	
}


void BackGround::transforMatrix(std::vector<std::string> arr, int Row)
{

	for (int i = 0; i < arr.size(); i++)
	{
		
		this->_matrix[i][Row].IDTile =  atoi(arr[i].c_str());
		this->_matrix[i][Row].posTile = Point(i * _size , Screen_Height - _size * Row );
		//listTile.push_back(_matrix[i][Row]);
		
	}
}


RECT BackGround::getRectByID(int ID)
{
	RECT rect;

	rect.left = ID * _size;
	rect.right = rect.left + _size;
	rect.top = 0;
	rect.bottom = _size;

	return rect;
}


void BackGround::checkTileInBound(RECT rect)
{
	for (int j = 0; j < _row; j++)
	{
		for (int i = 0; i < _column; i++)
		{
			if (_matrix[i][j].posTile.x >= rect.left  && _matrix[i][j].posTile.x - _size <= rect.right)
				_matrix[i][j].tileStaus = TileStatus::isNormal;
			else
			{
				_matrix[i][j].tileStaus = TileStatus::isHide;
			}
		}
	}
}

void BackGround::drawBackGround()
{
	for (int j = 0; j < _row; j++)
	{ 
		for (int i = 0; i < _column; i++)
		{
			if (_matrix[i][j].tileStaus == TileStatus::isNormal)
			{
				D3DXVECTOR3 posCenter = D3DXVECTOR3(_matrix[i][j].posTile.x - _size / 2, _matrix[i][j].posTile.y - _size / 2, 0);
				SpriteManager::createInstance()->draw(this->_texture, &getRectByID(this->_matrix[i][j].IDTile), posCenter);
			}
		}
	}

	/*for (auto tile : listTile)
	{
		D3DXVECTOR3 posCenter = D3DXVECTOR3(tile.posTile.x - _size / 2, tile.posTile.y - _size / 2, 0);
		SpriteManager::createInstance()->draw(this->_texture, &getRectByID(tile.IDTile), posCenter);
	}*/
	
}

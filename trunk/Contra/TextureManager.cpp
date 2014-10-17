#include "TextureManager.h"


static TextureManager*_instance = nullptr;

TextureManager* TextureManager::getInstance()
{
	if (_instance == NULL)
	{
		_instance = new TextureManager();
	}
	return _instance;
}

TextureManager* TextureManager::createInstance(LPDIRECT3DDEVICE9 _d3ddv)
{
	if (_instance == NULL)
	{
		_instance = new TextureManager(_d3ddv);
	}

	return _instance;
}

TextureManager::TextureManager()
{
	//this->list_Texture = new std::hash_map<int, Texture*>();
}

TextureManager::TextureManager(LPDIRECT3DDEVICE9 d3ddv)
{
	this->_d3ddv = d3ddv;
}

//doc tu file image lay key va filename---> texture
bool TextureManager::createTextureByFileName(int key, std::string filename)
{
	Texture* texture = new Texture(this->_d3ddv);

	if (texture->init(filename, color))
	{
		addTexture(key, texture);
		return true;
	}
	else
	{
		return false;
		
	}
}

//add texture vao hashmap theo key
void TextureManager::addTexture(int key, Texture* texture)
{
	this->list_Texture[key] = texture;
}

//lay texture by key
Texture* TextureManager::getTetureByKey(int key)
{
	return this->list_Texture.find(key)->second;
}

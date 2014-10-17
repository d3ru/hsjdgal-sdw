#ifndef __TEXTUREMANAGER__H__
#define __TEXTUREMANAGER__H__

#include"Texture.h"
#include<hash_map>
#include<string>

#define color D3DCOLOR_XRGB(255, 0, 255)


class TextureManager
{
public:

	static TextureManager* createInstance(LPDIRECT3DDEVICE9 _d3ddv);
	static TextureManager* getInstance();
	bool createTextureByFileName(int key, std::string filename);
	void addTexture(int key, Texture* texture);
	Texture* getTetureByKey(int key);
	TextureManager();
	TextureManager(LPDIRECT3DDEVICE9 _d3ddv);
protected:
private:
	//static TextureManager* _instance;
	std::hash_map<int, Texture*> list_Texture;
	LPDIRECT3DDEVICE9 _d3ddv;
};

#endif
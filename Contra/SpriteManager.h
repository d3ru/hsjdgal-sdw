#ifndef __SPRITEMANAGER__H__
#define __SPRITEMANAGER__H__

#pragma once


#include"SpriteManager.h"
#include"Texture.h"
#include"Sprite.h"
#include"ObjectGame.h"

class SpriteManager
{
public:
	SpriteManager();
	~SpriteManager();

	Sprite* _Sprite;

	static SpriteManager* createInstance();
	void init(LPD3DXSPRITE spriteHandle);
	void draw(Texture* texture, RECT *RectRS, D3DXVECTOR3 pos, D3DCOLOR transcolor = 0xFFFFFFFF);
//	void drawObj(ObjectGame* objectGame, D3DCOLOR transcolor);
	void drawObj(ObjectGame*, D3DCOLOR transcolor = 0xFFFFFFFF);
};

#endif
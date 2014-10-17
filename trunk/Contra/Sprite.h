#ifndef __SPRITE__H__
#define __SPRITE__H__

#include <d3dx9.h>
#include "Texture.h"

class Sprite
{
protected:

	LPD3DXSPRITE _SpriteHandler;

public:
	
	Sprite(LPD3DXSPRITE _SpriteHandler);
	~Sprite();

	//ve texture tai vi tri mac dinh la chinh giua
    void draw(Texture* image, RECT *RectRS, D3DXVECTOR3 pos, D3DCOLOR transcolor = 0xFFFFFFFF, bool isCenter = true);

	void draw(Texture* image, RECT *RectRS, D3DXVECTOR3 pos, D3DXVECTOR2 scale, D3DCOLOR transcolor = 0xFFFFFFFF, bool isCenter = true);

	void drawFlipX(Texture* image, RECT *RectRS, D3DXVECTOR3 pos, D3DCOLOR transcolor = 0xFFFFFFFF, bool isCenter = true);
};

#endif


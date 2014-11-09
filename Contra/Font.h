#ifndef __FONT_H___
#define __FONT_H___

#include"Texture.h"
#include"Point.h"
#include"Animation.h"

#pragma once
class Font : public Animation
{
public:
	Font();
	~Font();

	void drawFont(char*, float, float);
	void drawFont(int,float, float);

private:

	Texture* _fontTexture;

	Size _fontSize;
	
};

#endif
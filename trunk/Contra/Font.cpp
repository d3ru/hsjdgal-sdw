#include "Font.h"


Font::Font()
{
	_fontSize.width = 32;
	_fontSize.height = 32;

}


Font::~Font()
{
	if (_fontTexture)
		delete _fontTexture;
}


void Font::drawFont(char* S, float X, float Y)
{
	D3DXVECTOR3 pos = D3DXVECTOR3(X, Y, 0);
	int num = strlen(S);
}

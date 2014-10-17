#include "Texture.h"


Texture::Texture(LPDIRECT3DDEVICE9 d3ddv)
{
	_texture = nullptr;
	_d3ddv = d3ddv;
}


Texture::~Texture()
{
	if (_texture)
	{
		_texture->Release();
	}
}

bool Texture::init(std::string fileName, D3DCOLOR color)
{
	HRESULT result; // take a value return
	
	result = D3DXGetImageInfoFromFile(fileName.c_str(), &_infoImage);
	if (result != D3D_OK)
	{
		_texture = NULL;
		return false;
	}
	// create a new Texture by loading bitmap image file
	result = D3DXCreateTextureFromFileEx(
		_d3ddv, // directx Device
		fileName.c_str(), // bitmap file
		_infoImage.Width, //bitmap image width
		_infoImage.Height, //bitmap image Height
		1,
		D3DPOOL_DEFAULT, // type of the surface
		D3DFMT_UNKNOWN, //surface format
		D3DPOOL_DEFAULT, // memory class for the texture
		D3DX_DEFAULT, //image filter
		D3DX_DEFAULT, //mip filter
		color, // color key for transparency
		&_infoImage,//bitmap file information
		NULL, //color palette
		&_texture //destination Texture
		);
	if (result != D3D_OK)
	{
		_texture = NULL;
		return false;
	}
	return  true;
}

LPDIRECT3DTEXTURE9 Texture::getTexture()
{
	return _texture;
}

Size Texture::getContainSize()
{
	return Size(_infoImage.Width, _infoImage.Height);
}
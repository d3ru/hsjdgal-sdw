#include "SpriteManager.h"
#include "TextureManager.h"

static SpriteManager* _Instance = nullptr;

SpriteManager* SpriteManager::createInstance()
{
	if (_Instance == nullptr)
	{
		_Instance = new SpriteManager();
	}
	return _Instance;
}

SpriteManager::SpriteManager()
{
}


SpriteManager::~SpriteManager()
{
}

void SpriteManager::init(LPD3DXSPRITE spriteHandle)
{
	_Sprite = new Sprite(spriteHandle);
}

void SpriteManager::draw(Texture* texture, RECT *RectRS, D3DXVECTOR3 pos, D3DCOLOR transcolor)
{
	_Sprite->draw(texture, RectRS, pos, transcolor, true);
}

void SpriteManager::drawObj(ObjectGame* gameObject, D3DCOLOR transcolor)
{
	RECT *rectRS = new RECT();


	Texture *texture = TextureManager::getInstance()->getTetureByKey(gameObject->ID_Image);

		
	D3DXVECTOR3 position(gameObject->getPosition().x, gameObject->getPosition().y, gameObject->getZOther());


	if (gameObject->_isAnimation)
		rectRS = gameObject->_rectRS;
	else if (!gameObject->_isAnimation)
	{
		rectRS->left = 0;
		rectRS->top = 0;
		rectRS->right = rectRS->left + gameObject->getContainSize().width;
		rectRS->bottom = rectRS->right + gameObject->getContainSize().height;

		gameObject->setContainSize(texture->getContainSize().width, texture->getContainSize().height);
	}
		
	if (!gameObject->_isFlipX)
		_Sprite->draw(texture, rectRS, position, transcolor, true);
	else
	{
		_Sprite->drawFlipX(texture, rectRS, position, transcolor, true);
	}
}

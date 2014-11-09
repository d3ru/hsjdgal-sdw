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
	sprite = new Sprite(spriteHandle);

	camera = new Camera();
}

void SpriteManager::draw(Texture* texture, RECT *RectRS, D3DXVECTOR3 pos, D3DCOLOR transcolor)
{
	D3DXVECTOR3 posDraw = camera->getPointTransform(pos.x, pos.y);

	sprite->draw(texture, RectRS, posDraw, transcolor, true);
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
		rectRS->right = rectRS->left + texture->getContainSize().width;
		rectRS->bottom = rectRS->right + texture->getContainSize().height;

		gameObject->setContainSize(texture->getContainSize().width, texture->getContainSize().height);
	}

	D3DXVECTOR3 posDraw(camera->getPointTransform(position.x, position.y));
		
	if (!gameObject->_isFlipX)
		sprite->draw(texture, rectRS, posDraw, transcolor, true);
	else
	{
		sprite->drawFlipX(texture, rectRS, posDraw, transcolor, true);
	}
}

void SpriteManager::updateCamera(float posRambo, float dt)
{
	camera->update(posRambo, dt);
}

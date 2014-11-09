#include "DynamicObject.h"


DynamicObject::DynamicObject()
{
}


DynamicObject::~DynamicObject()
{
}

DynamicObject::DynamicObject(GameNode node) : ObjectGame(node)
{
	
}

Box DynamicObject::getBox()
{
	return ObjectGame::getBox();
}

float DynamicObject::getTimeCollision(ObjectGame* obj, float &normalx, float &normaly, float dt)
{
	Box box = this->getBox();

	Box broadphaseBox = Collision::getInstance()->getSweptBroadphaseBox(box, dt);

	Box targetBox = Collision::getInstance()->getSweptBroadphaseBox(obj->getBox(), dt);

	float moveX = 0.0f;
	float moveY = 0.0f;
	
	//Kiem tra 2 box hien tai co va cham voi nhau ???

	if (Collision::getInstance()->AABBCheck(box, targetBox))
	{
		if (Collision::getInstance()->AABB(box, targetBox, moveX, moveY))
		{
			normalx = moveX;
			normaly = moveY;

			return 2.0f;
		}
		//No collision
		return 1.0f;
	}
	else
	{
		if (Collision::getInstance()->AABBCheck(broadphaseBox, targetBox))
		{
			return Collision::getInstance()->sweptAABB(box, targetBox, normalx, normaly, dt);
		}
		else
		{
			//No collision
			return 1.0f;
		}
	}

	return 0.0f;
}

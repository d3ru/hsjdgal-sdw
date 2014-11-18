#include "HideObject.h"


HideObject::HideObject()
{
}

HideObject::HideObject(GameNode node)
{
	this->ID = node.ID;

	this->setPosition(node.POSITION);

	this->setContainSize(node.CONTAINSIZE);

	if (this->ID < 3000 && this->ID >= 2000)
		typeObject = TYPEOBJECT::GROUND;
	else if (this->ID >= 300 && this->ID < 4000)
		typeObject = TYPEOBJECT::SWITCH;
	else if (this->ID >= 4000 && this->ID < 5000)
	{
		typeObject = TYPEOBJECT::WATER;
	}
}


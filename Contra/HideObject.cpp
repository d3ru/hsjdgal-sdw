#include "HideObject.h"


HideObject::HideObject()
{
}

HideObject::HideObject(GameNode node)
{
	this->ID = node.ID;

	this->setPosition(node.POSITION);

	this->setContainSize(node.CONTAINSIZE);
}


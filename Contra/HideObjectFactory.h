#ifndef __HIDEOBJECTFACTORY__H__
#define __HIDEOBJECTFACTORY__H__


#pragma once

#include"ObjectFactory.h"
#include"HideObject.h"

class HideObjectFactory : public ObjectFactory
{
public:

	static HideObjectFactory* createInstance();

	std::vector<HideObject*> create();
	
};

#endif


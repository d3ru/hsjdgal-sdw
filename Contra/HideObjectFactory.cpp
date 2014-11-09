#include "HideObjectFactory.h"

static HideObjectFactory* _instance = nullptr;

HideObjectFactory* HideObjectFactory::createInstance()
{
	if (_instance == nullptr)
		_instance = new HideObjectFactory();
	return _instance;
}

std::vector<HideObject*> HideObjectFactory::create()
{
	std::vector<HideObject*> listObj;

	for (auto node : listInfo)
	{
		auto hideObj = new HideObject(node);
		listObj.push_back(hideObj);
	}

	return listObj;
}


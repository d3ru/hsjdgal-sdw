#include "ObjectFactory.h"
#include <string>


ObjectGame* ObjectFactory::createObj()
{
	return nullptr;
}

ObjectGame* ObjectFactory::createObj(int ID)
{
	return nullptr;
}

ObjectGame* ObjectFactory::createObj(std::vector<std::string> arr)
{
	return nullptr;
}

void ObjectFactory::addInfo(std::vector<std::string> arr)
{
	
	this->info.push_back(arr);

}

void ObjectFactory::addInfo(std::vector<GameNode> arr)
{
	for (auto _node : arr)
	{
		this->listInfo.push_back(_node);
	}

}

std::vector<std::string> ObjectFactory::getInfoById(int ID)
{
	for (auto line : info)
	{
		if (atoi(line.at(0).c_str()) == ID)
		{
			return line;			
		}
	}
}
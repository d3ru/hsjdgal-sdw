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

	int i = 2;
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
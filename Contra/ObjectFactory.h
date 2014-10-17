#ifndef __OBJECTFACTIRY__H__
#define __OBJECTFACTIRY__H__

#include<vector>
#include"ObjectGame.h"

class ObjectFactory
{
public:
	
	void addInfo(std::vector<std::string>);

	virtual ObjectGame* createObj();

	virtual ObjectGame* createObj(int ID);

	virtual ObjectGame* createObj(std::vector<std::string> arr);

	virtual std::vector<std::string> getInfoById(int ID);

protected:

	std::vector<std::vector<std::string>> info;
	
};
#endif

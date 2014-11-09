#include "FileUtils.h"
#include<fstream>
#include<string>
#include"TextureManager.h"
#include"ZombieFactory.h"
#include"BulletFactory.h"
#include"HideObjectFactory.h"

static FileUtils* instance = nullptr;

FileUtils* FileUtils::getInstance()
{
	if (instance == nullptr)
		instance = new FileUtils();
	return instance;
}


void FileUtils::loadFileCSV()
{
	
	this->readFileCSV(fileZombie, ZombieFactory::createInstance());
	this->readFileCSV(fileBullet, BulletFactory::createInstance());
	this->readFileCSV(fileHideObject, HideObjectFactory::createInstance());

	this->readFileImage();
}

void FileUtils::readFileCSV(const char* fileName, ObjectFactory* objFactory)
{
	std::vector<std::vector<std::string>> info = readFile(fileName,',');
	
	for (auto line : info)
	{
		objFactory->addInfo(line);
	}

	std::vector<GameNode> _info = readData(fileName, ',');

	objFactory->addInfo(_info);
	
}


void FileUtils::readFileImage()
{
	std::vector<std::vector<std::string>> info = readFile(fileImage ,',');

	for (auto line : info)
	{
		int ID_Image = atoi(line.at(0).c_str());
		std::string linkImage = line.at(1);
		TextureManager::getInstance()->createTextureByFileName(ID_Image, linkImage);
	}
}

std::vector<std::vector<std::string>> FileUtils::readFile(std::string filePath, char key)
{
	std::vector<std::vector<std::string>> info;
	std::vector<std::string> arr;
	std::string line;



	std::ifstream* myFile = new std::ifstream(filePath);
	if (myFile->is_open())
	{
		while (!myFile->eof())
		{
			if (getline(*myFile, line))
			{
				if (line != "")
				{
					arr = split(line, key);
					if (arr.size() > 0)
					{
						info.push_back(arr);
					}
				}
			}
		}
	}

	return info;
	
}

std::vector<GameNode> FileUtils::readData(std::string filePath, char key)
{
	std::vector<GameNode> result;
	std::string line;
	GameNode node;
	std::vector<std::string> _arr;

	std::ifstream* myFile = new std::ifstream(filePath);
	if (myFile->is_open())
	{
		while (!myFile->eof())
		{
			if (getline(*myFile, line))
			{
				if (line != "")
				{
				    _arr = split(line, key);

					if (_arr.size() > 0)
					{
						node = GameNode(atoi(_arr.at(0).c_str()), atoi(_arr.at(1).c_str()), Point(atof(_arr.at(2).c_str()), atof(_arr.at(3).c_str())), Size(atof(_arr.at(4).c_str()), atof(_arr.at(5).c_str())));

						result.push_back(node);
					}
				}
			}
		}
	}

	return result;
}

std::vector<std::string> FileUtils::split(std::string string, char key)
{
	std::vector<std::string> arr;

	std::string sTemp = "";

	int index = 0;

	while (index < string.length())
	{
		while (string[index] != key && index < string.length() && string[index] != ' ')
		{
			sTemp += string[index];
			index++;
		}
		if (sTemp.size() > 0)
			arr.push_back(sTemp);
		index++;
		sTemp.clear();
	}

	return arr;
}
#include "FileUtils.h"
#include<fstream>
#include<string>
#include"TextureManager.h"
#include"BallFactory.h"
#include"ZombieFactory.h"
#include"BulletFactory.h"

static FileUtils* instance = nullptr;

FileUtils* FileUtils::getInstance()
{
	if (instance == nullptr)
		instance = new FileUtils();
	return instance;
}


void FileUtils::loadFileCSV()
{
	this->readFileCSV(fileBall, BallFactory::getInstance());
	this->readFileCSV(fileZombie, ZombieFactory::createInstance());
	this->readFileCSV(fileBullet, BulletFactory::createInstance());

	this->readFileImage();
}

void FileUtils::readFileCSV(const char* fileName, ObjectFactory* objFactory)
{
	std::vector<std::vector<std::string>> info = readFile(fileName,',');
	
	for (auto line : info)
	{
		objFactory->addInfo(line);
	}
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
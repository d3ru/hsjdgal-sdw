#ifndef __FILESUTILS__H__
#define __FILESUTILS__H__


#define fileImage "..\\Resource\\file\\Image.csv"
#define fileBall "..\\Resource\\file\\Ball.csv"
#define filePall "..\\Resource\\file\\Pall.csv"
#define fileZombie "..\\Resource\\file\\Zombie.csv"
#define fileBullet "..\\Resource\\file\\Bullet.csv"


#include <vector>
#include <hash_map>
#include "ObjectFactory.h"

class FileUtils
{
public:
	
	static FileUtils* getInstance();

	void loadFileCSV();

private:

	void readFileCSV(const char* fileName, ObjectFactory* objectFactory);
	void readFileImage();

	static std::vector<std::vector<std::string>> readFile(std::string, char key);
	static std::vector<std::string> split(std::string, char);

};

#endif

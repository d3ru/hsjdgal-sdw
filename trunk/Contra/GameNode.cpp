#include "GameNode.h"


GameNode::GameNode()
{
}


GameNode::GameNode(int id, int idImage, Point point, Size size)
{
	this->ID = id;

	this->IDIMAGE = idImage;

	this->POSITION = point;

	this->CONTAINSIZE = size;
}
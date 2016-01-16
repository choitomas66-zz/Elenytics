#include "Room.h"
#include "utilities.h"

Room::Room(double x, double y, double width, double height){
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

double Room::getRandomX(){
	return fRand(x, x+width);
}

double Room::getRandomY(){
	return fRand(y, y+height);
}
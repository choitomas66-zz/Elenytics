#include "AP.h"
#include "utilities.h"


AP::AP(int id, double x, double y, double power, double dev){
	this->id = id;
	this->x = x;
	this->y = y;
	this->power = power;
	this->dev = dev;
}

int AP::getID(){
	return id;
}

double AP::getPower(double ux, double uy){
	double sdistance = (ux-x)*(ux-x) + (uy-y)*(uy-y);
	double pw = fRand(power-dev,power+dev)/(1+sdistance); //add 1 to prevent infinite power
	if(pw < 0.001) pw = 0; //minimum power level to detect
	return pw;
}
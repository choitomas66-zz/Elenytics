#ifndef ROOM_H
#define ROOM_H

#include <vector>

using namespace std;

class Room {
	public:
		Room(double x, double y, double width, double height);
		double getRandomX();
		double getRandomY();
		vector< vector<double> > mu; //fingerprints
		vector< vector<double> > std; //[Point][AP]
	private:
		double x, y;
		double width, height;
};

#endif
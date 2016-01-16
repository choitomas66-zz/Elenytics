#ifndef AP_H
#define AP_H

class AP {
	public:
		AP(int id, double x, double y, double power, double dev);
		double getPower(double ux, double uy);
		int getID();
	private:
		int id;
		double x, y;
		double power;
		double dev;
};

#endif
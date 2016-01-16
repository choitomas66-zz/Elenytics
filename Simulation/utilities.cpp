#include <cstdlib>
#include <cmath>
#include <ctime>
#include "utilities.h"

#define PI 3.1415926535
#define e 2.718281828

//calculate probability
double findProb(double fpmu, double fpstd, double usrx) {
    return (1/(fpstd * sqrt(2*PI))) * exp(-0.5*pow(((usrx-fpmu)/fpstd), 2));
}

double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}
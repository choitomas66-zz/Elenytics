#include <iostream>
#include <algorithm>
#include <utility> 
#include <cstdlib>
#include <cmath>
#include <ctime>

using namespace std;

#define max_W 100
#define max_L 100
#define max_AP 4
#define max_fprint 5
#define max_calib 10
#define signal_max 100
#define signal_min 40
#define PI 3.1415926535
#define e 2.718281828

struct fingerPrint{
    double x[max_AP];
    double s[max_AP];
    string section;
};

pair<int, int> AP[max_AP];
pair<int, int> fprint[max_fprint];
pair<double, string> nearest;
fingerPrint fp[max_fprint];
fingerPrint usr;

double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

// create calibration fingerprints
void calibrate() {

    // get Data
    double sum, input[max_calib];
    fp[0].section = "Meat";
    fp[1].section = "Dairy";
    fp[2].section = "Fruits";
    fp[3].section = "Chips and Chocolates";
    fp[4].section = "Fish";
    for(int i = 0; i < max_fprint; i++) {
        for(int j = 0; j < max_AP; j++) {
            sum = 0;
            // random signal strengths within a random range
            double r = fRand(signal_min, signal_max);
            double b = fRand(3, 10);
            for(int k = 0; k < max_calib; k++) {
                input[k] = fRand(r-b, r+b);
                sum += input[k];
            }
            // average
            fp[i].x[j] = sum / max_calib;
            sum = 0;
            // std dev
            for(int k = 0; k < max_calib; k++) {
                sum += (fp[i].x[j] - input[k])*(fp[i].x[j] - input[k]);
            }
            sum = pow(sum, 0.5);
            fp[i].s[j] = sum;
        }
    }
}

//obtain user data
void user() {
    // assign random signal strengths
    double sum, input[max_calib];
    for(int j = 0; j < max_AP; j++) {
        sum = 0;
        for(int k = 0; k < max_calib; k++) {
            double r = fRand(signal_min, signal_max);
            input[k] = fRand(r-5, r+5);
            sum += input[k];
        }
        // average
        usr.x[j] = sum / max_calib;
        sum = 0;
        // std dev
        for(int k = 0; k < max_calib; k++) {
            sum += (usr.x[j] - input[k])*(usr.x[j] - input[k]);
        }
        sum = pow(sum, 0.5);
        usr.s[j] = sum;

    }
}

//calculate probability
double findProb(double fpmu, double fpstd, double usrx) {
    return (1/(fpstd * sqrt(2*PI))) * pow(e, -0.5*pow(((usrx-fpmu)/fpstd), 2));
}

//find nearest using probability
void findNearest() {
    double prob = 0;
    int index;
    for(int i = 0; i < max_fprint; i++) {
        //find prob
        double tmp = 1;
        for(int j = 0; j < max_AP; j++) {
            cout << "Probability from wifi AP " << j << ": " <<  findProb(fp[i].x[j], fp[i].s[j], usr.x[j]) << endl;
            tmp *= findProb(fp[i].x[j], fp[i].s[j], usr.x[j]);        
        }
        if(tmp > prob) {
            prob = tmp;
            index = i;
        }
        cout << "Probability nearest location is " << fp[i].section << ": " << tmp << endl << endl;
    }
    nearest.first = prob;
    nearest.second = fp[index].section;
}

void inputAP() {
    for(int i = 0; i < max_AP; i++) {
        cin >> AP[i].first >> AP[i].second;
    }
}

int main() {
   
    srand(time(0));
    cout << "Calibrating..." << endl;
    calibrate();
    for(int i = 0; i < max_fprint; i++) {
        for(int j = 0; j < max_AP; j++) {
            cout << "AP: " << j << " reading: " << fp[i].x[j] << " " << fp[i].s[j] << endl;
        }
    }
    cout << "Obtaining User Data..." << endl;
    user();
    cout << "Finding Nearest..." << endl;
    findNearest();
    cout << "Nearest Section: " << nearest.second << endl;
    cout << "Probability: " << nearest.first << endl;
    return 0;
}

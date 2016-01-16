#include <iostream>
#include <algorithm>
#include <utility> 
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <vector>
#include "Room.h"
#include "AP.h"
#include "utilities.h"

using namespace std;

int main(){
	srand(time(0));

	int apc = 3; //AP count
	vector<AP> a;
	a.push_back(AP(0,10.0,10.0,100.0,20.0)); //add apc number of APs
	a.push_back(AP(1,10.0,30.0,100.0,15.0));
	a.push_back(AP(2,35.0,45.0,100.0,10.0));

	//initialize square grid of rooms, position increments upwards and to the right
	double side = 50; //side length
	double rs = 2; //rs*rs is the number of rooms
	vector<Room> vR;
	double l = side/rs;
	for(int i = 0; i<rs; i++){
		for(int j = 0; j<rs; j++){
			vR.push_back(Room(i*l,j*l,l,l)); //add rooms
		}
	}

	double userx = 0;
	double usery = 0;
	cout << "Input positon (x y):\n";
	cin >> userx >> usery;
	cout << "Expected position: Room (" << (int)(userx/l) <<", "<< (int)(usery/l)<< ")\n";

	int max_fprint = 5; //fingerprints per room
	int samples = 10; //samples at each point

	cout << "Computing fingerprints for all rooms.\n";
	for(int i = 0; i < vR.size(); i++){ //for all the rooms
		for(int j =0; j<max_fprint; j++){ //for all fingerprints
			double fx = vR[i].getRandomX(); //get random position in the room
			double fy = vR[i].getRandomY();
			vector<double> temp;
			vR[i].mu.push_back(temp);
			vR[i].std.push_back(temp);

			for(int k = 0; k< apc; k++){ //for all AP
				double sum = 0;
				vector<double> s(samples);

				for(int l = 0; l<samples; l++){
					s[l] = a[k].getPower(fx, fy); //simply drop in your power calculation here
					sum += s[l];
				}
				double mean = sum/samples;
				//cout << "Room: " << i << " AvgPower of AP "<< k << " at (" << fx << ", "<< fy<< "): "<< mean << "\n";
				sum = 0;
				//std dev
				for(int l = 0; l < samples; l++) {
	                sum += (s[l]-mean)*(s[l]-mean);
	            }
	            sum /= samples;
	            sum = sqrt(sum);
	            vR[i].mu[j].push_back(mean);
	            vR[i].std[j].push_back(sum);
			}
		}
	}

	//get user data (mean and std dev)
	cout << "Computing user data.\n";
	vector<double> usermu(apc);
	vector<double> userstd(apc);
	for(int i =0; i<apc; i++){ //for all the APs
		double sum = 0;
		vector<double> s(samples);

		for(int j =0; j<samples; j++){ //sample a certain number of times
			s[j] = a[i].getPower(userx, usery);
			sum += s[j];
		}
		double mean = sum/samples;
		cout << "AvgPower: " << mean << "\n";
		sum = 0;
		//std dev
		for(int l = 0; l < samples; l++) {
            sum += (s[l]-mean)*(s[l]-mean);
        }
        sum /= samples;
        sum = sqrt(sum);
        cout << "StdDev: " << sum << "\n";
        usermu.push_back(mean);
        userstd.push_back(sum);
	}

	//find where the user is
	double prob = 0;
	int index = 0;
	for(int i = 0; i<vR.size(); i++){
		for(int j =0; j<max_fprint; j++){
			double tmp = 1;
			for(int k =0; k<apc; k++){
				cout << "Probability from wifi AP " << k << ": " <<  findProb(vR[i].mu[j][k], vR[i].std[j][k], usermu[k]) << endl;
				tmp *= findProb(vR[i].mu[j][k], vR[i].std[j][k], usermu[k]);
			}
			if(tmp > prob){
				prob = tmp;
				index = i;
			}
		}
	}

	int calcx = index/(int)rs;
	int calcy = index%(int)rs;
	cout << "Probability: " << prob << "\n";
	cout << "Calculated position: " << index << " or room (" << calcx << ", "<< calcy<<")\n";

	return 0;
}
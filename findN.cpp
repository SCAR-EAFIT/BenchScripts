#include <iostream>
#include <fstream>
#include <limits>
#include <cmath>

using namespace std;

unsigned long getMemTotal();
double findN(double, double, double, double);

int main(){
    unsigned long memTotalKiB = getMemTotal();
    unsigned long memTotalB = memTotalKiB * 1024;
    double memTotalMB = memTotalB / (1024.0 * 1024.0);
    double NBValues[] = {128, 256, 384, 512, 640, 768, 896, 1024};

    cout << "Memory size: " << memTotalMB << " MB" << endl << endl;

	for(auto NBValue: NBValues){
		cout << "NB: " << NBValue << endl;
		for(double i = 0.90; i <= 1; i+=0.01){
			cout << findN(memTotalMB, 1, i, NBValue) << " ";
		}
		cout << endl << endl;
	}

    return 0;
}

unsigned long getMemTotal(){
    string token;
    ifstream file("/proc/meminfo");

    while(file >> token){
        if(token == "MemTotal:"){
            unsigned long mem;
            if(file >> mem){
                return mem;
            } 
			else{
                return 0;
            }
        }
        file.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    return 0;
}

double findN(double mem, double nodes, double perc, double NBValue){
	double totalMemory = mem * nodes;
    totalMemory = trunc(totalMemory * pow(2, 20));
    double topLimit = perc * trunc(sqrt(totalMemory / 8));
    double quoTient = trunc(topLimit / NBValue);

	return quoTient * NBValue;
}
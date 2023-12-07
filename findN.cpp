#include <iostream>
#include <fstream>
#include <limits>
#include <cmath>

using namespace std;

unsigned long get_mem_total() {
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

double findN(double mem, double nodes, double perc, double NB_value){
	double totalmemory = mem * nodes;
    totalmemory = trunc(totalmemory * pow(2, 20));
    double toplimit = perc * trunc(sqrt(totalmemory / 8));
    double quotient = trunc(toplimit / NB_value);

	return quotient * NB_value;
}

int main() {
    unsigned long mem_total_kib = get_mem_total();
    unsigned long mem_total_bytes = mem_total_kib * 1024;
    double mem_total_megabytes = mem_total_bytes / (1024.0 * 1024.0);
    double NB[] = {128, 256, 384, 512, 640, 768, 896, 1024};

    cout << "Memory size: " << mem_total_megabytes << " MB" << endl;
    cout << endl;

	for(auto NB_value: NB){
		cout << "NB: " << NB_value << endl;
		for(double i = 0.90; i <= 1; i+=0.01){
			cout << findN(mem_total_megabytes, 1, i, NB_value) << " ";
		}
		cout << endl << endl;
	}

    return 0;
}
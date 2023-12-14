#include <iostream>
#include <fstream>
#include <limits>
#include <cmath>

using namespace std;

unsigned long getMemTotal();
double findN(double, double, double, double);

/*
    @param argc (Number of parameters and meaning): 1 -> N° of nodes; 2 -> N° of nodes, memory size (MB)
    @param argv (Possible values for each parameter): N° of nodes -> 1, 2, 3, ..., n; Memory size (MB) -> 4, 8, 16, 32, 64, ..., N
*/
int main(int argc, char **argv){
    double memTotalMB;
    double NBValues[] = {128, 256, 384, 512, 640, 768, 896, 1024};
    double nodeNumber = atof(argv[1]);

    if(argc == 2){
        unsigned long memTotalKiB = getMemTotal();
        unsigned long memTotalB = memTotalKiB * 1024;
        memTotalMB = memTotalB / (1024.0 * 1024.0);
    }
    else{
        memTotalMB = atof(argv[2]);
    }

    cout << "Memory size: " << memTotalMB << " MB" << endl << endl;

	for(double NBValue: NBValues){
		cout << "NB: " << NBValue << endl;
		for(double i = 0.90; i <= 1; i+=0.01){
			cout << findN(memTotalMB, nodeNumber, i, NBValue) << " ";
		}
		cout << endl << endl; // Output format: N1 N2 N3 ... N10
	}

    return 0;
}

/*
    @brief Get the memory size looking inside the meminfo file.
    @return Memory size in KiB, or 0 in case of error.
*/
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

/*
    @brief Calculates the value of N based on memory, nodes, percentage, and NB value.
    @param mem: Size of memory (MB) of the node.
    @param nodes: Number of nodes where the program is going to run.
    @param perc: Percentage of memory to be used.
    @param NBValue: NB value declared in NBValues array.
    @return Calculated value of N.
*/
double findN(double mem, double nodes, double perc, double NBValue){
	double totalMemory = mem * nodes;
    totalMemory = trunc(totalMemory * pow(2, 20));
    double topLimit = perc * trunc(sqrt(totalMemory / 8));
    double quoTient = trunc(topLimit / NBValue);

	return quoTient * NBValue;
}
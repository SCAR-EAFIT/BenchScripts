#include <iostream>
#include <fstream>
#include <limits>

unsigned long get_mem_total() {
    std::string token;
    std::ifstream file("/proc/meminfo");
    while (file >> token) {
        if (token == "MemTotal:") {
            unsigned long mem;
            if (file >> mem) {
                return mem;
            } else {
                return 0;
            }
        }
        // Ignore the rest of the line
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return 0; // Nothing found
}

int main() {
    unsigned long mem = get_mem_total();
    // Convert to gibibytes (1 GiB = 1024^3 kibibytes)
    double mem_gib = static_cast<double>(mem) / (1024 * 1024);
    double mem_gb = mem_gib * 1.07374;
    std::cout << "Memory size: " << mem_gb << " GB" << std::endl;
    std::cout << "Memory size: " << mem_gib << " GiB" << std::endl;

    return 0;
}
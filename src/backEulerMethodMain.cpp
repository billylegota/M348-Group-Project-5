#include <iostream>
#include <vector>
#include <string>

#include "backEulerMethod.h"
#include "matlabPlot.h"

double f(double t, double y) { return -10 * y; }

double dyf(double t, double y) { return -10; }

double f2(double t, double y) { return (1 + (8 - 9 * y) * y) * y; }

double dyf2(double t, double y) { return 1 + (16 - 27 * y) * y; }

double f3(double t, double y) { return -y * y; }

double dyf3(double t, double y) { return -2 * y; }

double f4(double t, double y) { return -y / (1 + y * y); }

double dyf4(double t, double y) { return (y * y - 1) / ((1 + y * y) * (1 + y * y)); }

int main() {
    double t0, t1, y0;
    int n;
    std::cout << "Enter t0, t1, y0, n: ";
    std::cin >> t0 >> t1 >> y0 >> n;
    std::vector<double> y(n + 1);

    backwardsEulerMethod(f4, dyf4, y, y0, t0, t1);

    std::string fileName;
    std::cout << "Enter output file name: ";
    std::cin >> fileName;
    std::ofstream fout(fileName.c_str());
    if (!fout.is_open()) {
        std::cerr << "ERROR: Opening file" << std::endl;
        return 1;
    }
    matlabPlot(fout, y);
    fout.close();

    return 0;
}
  

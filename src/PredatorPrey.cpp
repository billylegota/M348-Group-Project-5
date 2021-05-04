#include <cmath>
#include <iostream>
#include <vector>
#include <fstream>

#include "TrapezoidalMethod.h"
#include "Util.h"


void predatorPrey(int n, double prey, double predator, double t0, double t1, const std::string &filename) {
    const auto a = 2.0;
    const auto b = 0.01;
    const auto c = 1.0;
    const auto d = 0.01;

    // Vector of functions. The first entry is f1, second is f2, etc.
    std::vector<funcn> f({
        [=](double t, const std::vector<double> &y) { return a * y[0] - b * y[0] * y[1]; },
        [=](double t, const std::vector<double> &y) { return -c * y[1] + d * y[0] * y[1]; }
    });

    // Vector to store result.
    std::vector<double> t(n);
    std::vector<std::vector<double>> y(n);

    // Initial conditions.
    std::vector<double> y0({prey, predator});

    auto result = trapezoidalMethod(f, t, y, y0, t0, t1);
    if (result != TRAPEZOIDAL_STATUS_OK) {
        std::cerr << "Trapezoidal method failed. Dimension mismatch!" << std::endl;
        return;
    }

    std::ofstream file(filename, std::ios_base::out);
    if (!file.is_open()) {
        std::cerr << "Unable to open file " << filename << std::endl;
        return;
    }

    // Write data to file.
    for (auto i = 0; i < t.size(); i++) {
        file << t[i] << ", " << y[i] << std::endl;
    }
    file.close();

    std::cout << "Done." << std::endl;
}


int main() {
    std::vector<int> x0({
        500, 400, 300, 200, 100, 600, 700, 800, 900, 1000
    });
    std::vector<int> y0({
        360, 320, 280, 240, 200, 400, 440, 480, 520, 560
    });

    auto n = 10000;
    auto t0 = 0;
    auto t1 = 10;

    for (auto i = 0; i < x0.size(); i++) {
        predatorPrey(n, x0[i], y0[i], t0, t1, "../output/" + std::to_string(x0[i]) + "_" + std::to_string(y0[i]) + ".txt");
    }

    return EXIT_SUCCESS;
}

#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

#include "BackwardEulerMethod.h"
#include "TrapezoidalMethod.h"
#include "Util.h"


void backwardEulerMethodDemo(int index, int n, double y0, double t0, double t1, const std::string &filename) {
    // Vector of functions.
    std::vector<func1> functions({
        [](double t, double y) { return -10 * y; },
        [](double t, double y) { return (1 + (8 - 9 * y) * y) * y; },
        [](double t, double y) { return -y * y; },
        [](double t, double y) { return -y / (1 + y * y); }
    });

    // Vector of derivatives. These are the partial derivatives of the above functions with respect to y.
    std::vector<func1> derivatives({
        [](double t, double y) { return -10; },
        [](double t, double y) { return 1 + (16 - 27 * y) * y; },
        [](double t, double y) { return -2 * y; },
        [](double t, double y) { return (y * y - 1) / ((1 + y * y) * (1 + y * y)); }
    });

    // Choose the function and corresponding derivative.
    auto f = functions[index];
    auto fy = derivatives[index];

    std::vector<double> t(n);
    std::vector<double> y(n);

    auto result = backwardEulerMethod(f, fy, t, y, y0, t0, t1);
    if (result != EULER_STATUS_OK) {
        std::cerr << "Backward Euler method failed. Newton iteration did not converge!" << std::endl;
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


void trapezoidalMethodDemo(double gravity, double length, double drag, int n, double theta0, double omega0, double t0,
                           double t1, const std::string &filename) {
    // Vector of functions. The first entry is f1, second is f2, etc.
    std::vector<funcn> f({
        [=](double t, const std::vector<double> &y) {
            return y[1];
        },
        [=](double t, const std::vector<double> &y) {
            return -(gravity / length) * sin(y[0]) - drag * y[1];
        }
    });

    // Vector to store result.
    std::vector<double> t(n);
    std::vector<std::vector<double>> y(n);

    // Initial conditions.
    std::vector<double> y0({theta0, omega0});

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
    while (true) {
        std::cout << "Choose one:" << std::endl;
        std::cout << " 1) Backward Euler method demo" << std::endl;
        std::cout << " 2) Trapezoidal method demo" << std::endl;
        std::cout << " 3) Exit" << std::endl;

        std::cout << ": " << std::flush;
        int choice;
        std::cin >> choice;
        if (choice == 1) {
            int index;
            std::cout << "Enter the function number (1-4): " << std::flush;
            std::cin >> index;

            int n;
            std::cout << "Enter number of time steps: " << std::flush;
            std::cin >> n;

            double y0;
            std::cout << "Enter initial condition: " << std::flush;
            std::cin >> y0;

            double t0 = 0;
            double t1;
            std::cout << "Enter total time [s]: " << std::flush;
            std::cin >> t1;

            std::string filename;
            std::cout << "Enter filename: " << std::flush;
            std::cin >> filename;

            backwardEulerMethodDemo(index - 1, n, y0, t0, t1, filename);
        }
        else if(choice == 2) {
            double gravity;
            std::cout << "Enter gravitational acceleration [m / s ^ 2]: " << std::flush;
            std::cin >> gravity;

            double length;
            std::cout << "Enter length of pendulum [m]: " << std::flush;
            std::cin >> length;

            double drag;
            std::cout << "Enter coefficient of drag: " << std::flush;
            std::cin >> drag;

            int n;
            std::cout << "Enter number of time steps: " << std::flush;
            std::cin >> n;

            double theta0;
            std::cout << "Enter initial angular displacement [rad]: " << std::flush;
            std::cin >> theta0;

            double omega0;
            std::cout << "Enter initial angular velocity [rad / s]: " << std::flush;
            std::cin >> omega0;

            double t0 = 0;
            double t1;
            std::cout << "Enter total time [s]: " << std::flush;
            std::cin >> t1;

            std::string filename;
            std::cout << "Enter filename: " << std::flush;
            std::cin >> filename;

            trapezoidalMethodDemo(gravity, length, drag, n, theta0, omega0, t0, t1, filename);
        }
        else if(choice == 3) {
            break;
        }
        else {
            std::cout << "Invalid choice." << std::endl;
        }
    }
    return EXIT_SUCCESS;
}

#include <cmath>
#include <iostream>
#include <vector>

#include "exprtk.hpp"

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


void trapezoidalMethodPendulumDemo(double gravity, double length, double drag, int n, double theta0, double omega0,
                                   double t0, double t1, const std::string &filename) {
    // Vector of functions. The first entry is f1, second is f2, etc.
    std::vector<funcn> f({
        [=](double t, const std::vector<double> &y) { return y[1]; },
        [=](double t, const std::vector<double> &y) { return -(gravity / length) * sin(y[0]) - drag * y[1]; }
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


void trapezoidalMethodOrbitDemo(int n, double days, const std::string &filename) {
    const auto gravitationalConstant = 6.674e-11;
    const auto earthMass = 5.97e24;
    const auto sx0 = 0;
    const auto sy0 = 3.577e8;
    const auto vx0 = 1023;
    const auto vy0 = 0;
    const auto dayLength = 86400;

    // Coordinates are: sx, sy, vx, vy.
    std::vector<funcn> f({
        [=](double t, const std::vector<double> &y) { return y[2]; },
        [=](double t, const std::vector<double> &y) { return y[3]; },
        [=](double t, const std::vector<double> &y) {
            auto radius = sqrt(pow(y[0], 2) + pow(y[1], 2));
            auto acceleration = -gravitationalConstant * earthMass / pow(radius, 2);
            return acceleration * y[0] / radius;    // Component in x direction.
        },
        [=](double t, const std::vector<double> &y) {
            auto radius = sqrt(pow(y[0], 2) + pow(y[1], 2));
            auto acceleration = -gravitationalConstant * earthMass / pow(radius, 2);
            return acceleration * y[1] / radius;    // Component in y direction.
        }
    });

    // Vector to store result.
    std::vector<double> t(n);
    std::vector<std::vector<double>> y(n);

    // Initial conditions.
    std::vector<double> y0({sx0, sy0, vx0, vy0});

    auto result = trapezoidalMethod(f, t, y, y0, 0, days * dayLength);
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


void trapezoidalMethodSIRDemo(int n, double t0, double t1, double s0, double i0, double r0, double b, double k,
                              const std::string &filename) {
    // Normalize values.
    const auto total = s0 + i0 + r0;

    s0 /= total;
    i0 /= total;
    r0 /= total;

    // Coordinates are: s, i, r.
    std::vector<funcn> f({
        [=](double t, const std::vector<double> &y) { return -b * y[0] * y[1]; },
        [=](double t, const std::vector<double> &y) { return b * y[0] * y[1] - k * y[1]; },
        [=](double t, const std::vector<double> &y) { return k * y[1]; }
    });

    // Vector to store result.
    std::vector<double> t(n);
    std::vector<std::vector<double>> y(n);

    // Initial conditions.
    std::vector<double> y0({s0, i0, r0});

    auto result = trapezoidalMethod(f, t, y, y0, t0, t1);
    if (result != TRAPEZOIDAL_STATUS_OK) {
        std::cerr << "Trapezoidal method failed. Dimension mismatch!" << std::endl;
        return;
    }

    // Undo normalization.
    for (auto &entry : y) {
        for (double &value : entry) {
            value *= total;
        }
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


void trapezoidalMethodSystemDemo(const std::vector<funcn> &f, const std::vector<double> &y0, int n, double t0,
                                 double t1, const std::string &filename) {
    // Vector to store result.
    std::vector<double> t(n);
    std::vector<std::vector<double>> y(n);

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


void trapezoidalMethod1DDemo(int n, double y0s, double t0, double t1, const std::string &filename) {
    // We have to write f(t, y) in vector form. This just means replacing `y` with `y[0]`.
    std::vector<funcn> f({
        [](double t, const std::vector<double> &y) { return -10 * y[0]; }
    });

    // The time vector is unchanged. The vector of y files will be indexed like an n x 1 column vector, `y[n][0]`.
    std::vector<double> t(n);
    std::vector<std::vector<double>> y(n);

    // We have to convert the initial condition from scalar to vector form.
    std::vector<double> y0({y0s});

    // The rest of the code is the same.
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
    std::cout << "Choose one:" << std::endl;
    std::cout << "    1) Backward Euler method demo" << std::endl;
    std::cout << "    2) Trapezoidal method pendulum demo" << std::endl;
    std::cout << "    3) Trapezoidal method orbit demo" << std::endl;
    std::cout << "    4) Trapezoidal method SIR demo" << std::endl;
    std::cout << "    5) Trapezoidal method 1D demo" << std::endl;
    std::cout << "    6) Trapezoidal method arbitrary system demo" << std::endl;
    std::cout << "    7) Exit" << std::endl;
    std::cout << std::endl;

    while (true) {
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
        else if (choice == 2) {
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

            trapezoidalMethodPendulumDemo(gravity, length, drag, n, theta0, omega0, t0, t1, filename);
        }
        else if (choice == 3) {
            int n;
            std::cout << "Enter number of time steps: " << std::flush;
            std::cin >> n;

            double days;
            std::cout << "Enter total time [days]: " << std::flush;
            std::cin >> days;

            std::string filename;
            std::cout << "Enter filename: " << std::flush;
            std::cin >> filename;

            trapezoidalMethodOrbitDemo(n, days, filename);
        }
        else if (choice == 4) {
            int n;
            std::cout << "Enter number of time steps: " << std::flush;
            std::cin >> n;

            double t;
            std::cout << "Enter total time: " << std::flush;
            std::cin >> t;

            double s0;
            std::cout << "Enter S(0): " << std::flush;
            std::cin >> s0;

            double i0;
            std::cout << "Enter I(0): " << std::flush;
            std::cin >> i0;

            double r0;
            std::cout << "Enter R(0): " << std::flush;
            std::cin >> r0;

            double b;
            std::cout << "Enter b: " << std::flush;
            std::cin >> b;

            double k;
            std::cout << "Enter k: " << std::flush;
            std::cin >> k;

            std::string filename;
            std::cout << "Enter filename: " << std::flush;
            std::cin >> filename;

            trapezoidalMethodSIRDemo(n, 0, t, s0, i0, r0, b, k, filename);
        }
        else if (choice == 5) {
            int n;
            std::cout << "Enter number of time steps: " << std::flush;
            std::cin >> n;

            double t0 = 0;
            double t1;
            std::cout << "Enter total time: " << std::flush;
            std::cin >> t1;

            double y0;
            std::cout << "Enter y(0): " << std::flush;
            std::cin >> y0;

            std::string filename;
            std::cout << "Enter filename: " << std::flush;
            std::cin >> filename;

            trapezoidalMethod1DDemo(n, y0, t0, t1, filename);
        }
        else if (choice == 6) {
            int m;
            std::cout << "Enter the number of dimensions: " << std::flush;
            std::cin >> m;

            typedef exprtk::symbol_table<double> symbol_table_t;
            typedef exprtk::expression<double> expression_t;
            typedef exprtk::parser<double> parser_t;

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::vector<funcn> f(m);
            for (auto i = 0; i < m; i++) {
                std::string expressionString;
                std::cout << "Enter the expression for f" << i << "(t, y): " << std::flush;
                std::getline(std::cin, expressionString);

                f[i] = [=](double t, const std::vector<double> &y) {
                    std::vector<double> yCopy = y;

                    symbol_table_t symbolTable;
                    symbolTable.add_constant("t", t);
                    symbolTable.add_vector("y", yCopy);

                    expression_t expression;
                    expression.register_symbol_table(symbolTable);

                    parser_t parser;
                    parser.compile(expressionString, expression);

                    return expression.value();
                };
            }

            std::vector<double> y0(m);
            for (auto i = 0; i < m; i++) {
                std::cout << "Enter the initial condition for y" << i << "(t0): " << std::flush;
                std::cin >> y0[i];
            }

            int n;
            std::cout << "Enter number of time steps: " << std::flush;
            std::cin >> n;

            double t0;
            std::cout << "Enter start time: " << std::flush;
            std::cin >> t0;

            double t1;
            std::cout << "Enter stop time: " << std::flush;
            std::cin >> t1;

            std::string filename;
            std::cout << "Enter filename: " << std::flush;
            std::cin >> filename;

            trapezoidalMethodSystemDemo(f, y0, n, t0, t1, filename);
        }
        else if (choice == 7) {
            break;
        }
        else {
            std::cout << "Invalid choice." << std::endl;
        }
    }
    return EXIT_SUCCESS;
}

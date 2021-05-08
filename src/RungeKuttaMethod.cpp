#include "RungeKuttaMethod.h"


/**
 * Uses the Runge-Kutta method of order 4 to solve a system of ODEs of the form:
 *
 *      y1' = f1(t, y1, ..., yn), t0 < t < t1
 *          :
 *      yn' = fn(t, y1, ..., yn), t0 < t < t1
 *
 * From the initial conditions:
 *
 *      y1(t0), ..., yn(t0)
 *
 * @param f the vector of functions {f1, ..., fn}.
 * @param t the vector to store the time index in.
 * @param y the vector to store the result in.
 * @param y0 the initial condition vector.
 * @param t0 the initial time.
 * @param t1 the final time.
 * @return STATUS_OK if method succeeds, STATUS_ERROR_DIMENSION_MISMATCH if the number of functions and initial
 *         conditions does not match.
 */
RungeKuttaStatus rungeKuttaMethod(const std::vector<funcn> &f, std::vector<double> &t,
                                  std::vector<std::vector<double>> &y, const std::vector<double> &y0, double t0,
                                  double t1) {
    // Make sure the size of the func vector and initial conditions match.
    if (f.size() != y0.size()) return RUNGE_KUTTA_STATUS_ERROR_DIMENSION_MISMATCH;

    // m is the number of systems and n is the number of time steps.
    auto m = f.size();
    auto n = (int) y.size();
    auto h = (t1 - t0) / (n - 1);

    // Initial conditions.
    t[0] = t0;
    y[0] = y0;

    for (auto i = 0; i < n - 1; i++) {
        // K1.
        std::vector<double> k1(m);
        for (auto j = 0; j < m; j++) {
            k1[j] = h * f[j](t[i], y[i]);
        }

        // K2.
        std::vector<double> temp(m);
        for (auto j = 0; j < m; j++) {
            temp[j] = y[i][j] + k1[j] / 2;
        }
        std::vector<double> k2(m);
        for (auto j = 0; j < m; j++) {
            std::vector<double> tmp(m);
            k2[j] = h * f[j](t[i] + h / 2, temp);
        }

        // K3.
        for (auto j = 0; j < m; j++) {
            temp[j] = y[i][j] + k2[j] / 2;
        }
        std::vector<double> k3(m);
        for (auto j = 0; j < m; j++) {
            k3[j] = h * f[j](t[i] + h / 2, temp);
        }

        // K4.
        for (auto j = 0; j < m; j++) {
            temp[j] = y[i][j] + k3[j];
        }
        std::vector<double> k4(m);
        for (auto j = 0; j < m; j++) {
            k3[j] = h * f[j](t[i] + h, temp);
        }

        // Update time step and combine terms.
        t[i + 1] = t[i] + h;
        for (auto j = 0; j < m; j++) {
            temp[j] = y[i][j] + (k1[j] + 2 * k2[j] + 2 * k3[j] + k4[j]) / 6;
        }
        y[i + 1] = temp;
    }

    return RUNGE_KUTTA_STATUS_OK;
}
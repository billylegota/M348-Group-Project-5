#include "TrapezoidalMethod.h"


/**
 * Uses the trapezoidal method to solve a system of ODEs of the form:
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
TrapezoidalStatus trapezoidalMethod(const std::vector<funcn> &f, std::vector<double> &t,
                                    std::vector<std::vector<double>> &y, const std::vector<double> &y0, double t0,
                                    double t1) {
    // Make sure the size of the func vector and initial conditions match.
    if (f.size() != y0.size()) return TRAPEZOIDAL_STATUS_ERROR_DIMENSION_MISMATCH;

    // m is the number of systems and n is the number of time steps.
    auto m = f.size();
    auto n = (int) y.size();
    auto h = (t1 - t0) / (n - 1);

    // Initial conditions.
    t[0] = t0;
    y[0] = y0;

    for (auto i = 0; i < n - 1; i++) {
        // Evaluate each func at (t, y1, ..., yn).
        std::vector<double> yt1(m);
        for (auto j = 0; j < m; j++) {
            yt1[j] = f[j](t[i], y[i]);
        }

        // Apply the Euler step.
        std::vector<double> yEuler(m);
        for (auto j = 0; j < m; j++) {
            yEuler[j] = y[i][j] + h * yt1[j];
        }
        t[i + 1] = t[i] + h;

        // Evaluate each func at (t, yEuler1, ..., yEulerN).
        std::vector<double> yt2(m);
        for (auto j = 0; j < m; j++) {
            yt2[j] = f[j](t[i + 1], yEuler);
        }

        // Apply the Trapezoidal rule.
        y[i + 1].resize(m);
        for (auto j = 0; j < m; j++) {
            y[i + 1][j] = y[i][j] + h * (yt1[j] + yt2[j]) / 2;
        }
    }

    return TRAPEZOIDAL_STATUS_OK;
}

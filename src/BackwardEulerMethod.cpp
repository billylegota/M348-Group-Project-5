#include <cmath>
#include <limits>

#include "BackwardEulerMethod.h"


/**
 * Uses the backward Euler method to solve an ODE of the form:
 *
 *      y' = f(t, y), t0 < t < t1
 *
 * From the initial condition:
 *
 *      y(t0) = y0
 *
 * @param f the function `f`. The first argument corresponds to t and second to y.
 * @param fy partial derivative of `f` with respect to `y`. The first argument corresponds to t and second to y.
 * @param t vector to store time index (must have correct size).
 * @param y vector to store result (must have correct size).
 * @param y0 initial condition.
 * @param t0 initial time.
 * @param t1 final time.
 * @param tolerance the tolerance for Newton's method.
 * @param maxIterations the maximum number of iterations for Newton's method.
 * @return STATUS_OK if method succeeds, STATUS_ERROR_NEWTON_FAILS_TO_CONVERGE if Newton's method fails to converge.
 */
EulerStatus backwardEulerMethod(const func1 &f, const func1 &fy, std::vector<double> &t, std::vector<double> &y,
                                 double y0, double t0, double t1, double tolerance, int maxIterations) {
    auto n = (int) y.size();
    auto h = (t1 - t0) / (n - 1);

    t[0] = t0;
    y[0] = y0;

    for (auto i = 0; i < n - 1; i++) {
        t[i + 1] = t[i] + h;

        // Newton loop
        y[i + 1] = y[i];
        auto delta = std::numeric_limits<double>::infinity();
        for(auto iteration = 0; fabs(delta) > tolerance; iteration++) {
            delta = -(y[i + 1] - h * f(t[i + 1], y[i + 1]) - y[i]) / (1 - h * fy(t[i + 1], y[i + 1]));
            y[i + 1] += delta;
            if (iteration >= maxIterations) return EULER_STATUS_ERROR_NEWTON_FAILS_TO_CONVERGE;
        }
    }
    return EULER_STATUS_OK;
}

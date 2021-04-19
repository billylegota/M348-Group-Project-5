#include <cmath>
#include <limits>

#include "backEulerMethod.h"


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
 * @param y vector to store result (must have correct size).
 * @param y0 initial condition.
 * @param t0 initial time.
 * @param t1 final time.
 * @param tolerance the tolerance for Newton's method.
 * @param maxIterations the maximum number of iterations for Newton's method.
 * @return STATUS_OK if method succeeds, STATUS_ERROR_NEWTON_FAILS_TO_CONVERGE if Newton's method fails to converge.
 */
EulerStatus backwardsEulerMethod(const function &f, const function &fy, std::vector<double> &y, double y0, double t0,
                                 double t1, double tolerance, int maxIterations) {
    auto n = y.size() - 1;
    auto h = (t1 - t0) / n;

    auto t = t0;
    y[0] = y0;

    for (auto i = 0; i < n; i++) {
        t += h;

        // Newton loop
        // TODO: Come up with a better name for yy and dyy.
        auto yy = y[i];
        auto dyy = std::numeric_limits<double>::infinity();
        for(auto iteration = 0; fabs(dyy) > tolerance; iteration++) {
            dyy = -(yy - h * f(t, yy) - y[i]) / (1 - h * fy(t, yy));
            yy += dyy;
            if (iteration >= maxIterations) return STATUS_ERROR_NEWTON_FAILS_TO_CONVERGE;
        }

        y[i + 1] = yy;
    }
    return STATUS_OK;
}

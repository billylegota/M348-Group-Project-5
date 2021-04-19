#pragma once
#ifndef BACK_EULERMETHOD_H
#define BACK_EULERMETHOD_H

#include <functional>
#include <vector>


using function = std::function<double(double t, double y)>;

enum EulerStatus {
    STATUS_OK = 0,
    STATUS_ERROR_NEWTON_FAILS_TO_CONVERGE = 1
};


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
                                 double t1, double tolerance = 1e-6, int maxIterations = 10);

#endif

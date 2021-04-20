#pragma once
#ifndef CHAPTER_6_BACK_EULER_METHOD_H
#define CHAPTER_6_BACK_EULER_METHOD_H

#include <functional>
#include <vector>


using func1 = std::function<double(double t, double y)>;

enum EulerStatus {
    EULER_STATUS_OK = 0,
    EULER_STATUS_ERROR_NEWTON_FAILS_TO_CONVERGE = 1
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
                                 double y0, double t0, double t1, double tolerance = 1e-6, int maxIterations = 10);

#endif // CHAPTER_6_BACK_EULER_METHOD_H

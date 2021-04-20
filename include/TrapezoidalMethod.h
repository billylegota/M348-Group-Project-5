#pragma once
#ifndef CHAPTER_6_TRAPEZOIDAL_METHOD_H
#define CHAPTER_6_TRAPEZOIDAL_METHOD_H

#include <functional>
#include <vector>

using funcn = std::function<double(double t, const std::vector<double> &y)>;

enum TrapezoidalStatus {
    TRAPEZOIDAL_STATUS_OK = 0,
    TRAPEZOIDAL_STATUS_ERROR_DIMENSION_MISMATCH = 1
};


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
                                    double t1);

#endif // CHAPTER_6_TRAPEZOIDAL_METHOD_H

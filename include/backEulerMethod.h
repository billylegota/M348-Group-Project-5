#ifndef BACKEULERMETHOD_H
#define BACKEULERMETHOD_H
///////////////////////////////////////////////////////////////////////////////
// Backward Euler Method for Solving an ODE
//
// y' = f(t,y), a < t < b,
// y(a) = y0
//
// Inputs:
//   f          The name of the function "f" in the ODE
//   dyf        The name of the partial derivative of "f" with respect to y
//   y          Space for the solution (with correct size on input)
//   y0         Initial condition
//   a          Initial time
//   b          Final time
//   newtonTol  Tolerance for Newton's Method (stop after 10 iterations)
// Outputs:
//   y          The solution (at equally spaced points)
// Return:
//   0          If all okay
//   1          If Newton fails to converge
///////////////////////////////////////////////////////////////////////////////
#include <vector>

int backEulerMethod(double f(double,double), double dyf(double,double), std::vector<double>& y,
		    double y0, double a, double b, double newtonTol=1e-6);

#endif

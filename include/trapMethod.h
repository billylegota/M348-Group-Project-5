#ifndef TRAPMETHOD_H
#define TRAPMETHOD_H
///////////////////////////////////////////////////////////////////////////////
// Trapezoidal Method for Solving an ODE
//
// y' = f(t,y), a < t < b,
// y(a) = y0
//
// Inputs:
//   f         The name of the function "f" in the ODE
//   y         Space for the solution (with correct size on input)
//   a         Initial time
//   b         Final time
//   y0        Initial condition
// Outputs:
//   y         The solution (at equally spaced points)
///////////////////////////////////////////////////////////////////////////////
#include <vector>

void trapMethod(double f(double,double), std::vector<double>& y, double y0=0, double a=0, double b=1);
void trapMethod(double f(double,double), std::vector<double>& x ,std::vector<double>& y, double y0=0, double a=0, double b=1);

#endif

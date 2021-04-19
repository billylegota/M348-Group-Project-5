#ifndef TRAPMETHOD2_H
#define TRAPMETHOD2_H
///////////////////////////////////////////////////////////////////////////////
// Trapezoidal Method for Solving a system of two ODEs
//
// y1' = f1(t,y1,y2), a < t < b,
// y2' = f2(t,y1,y2), a < t < b,
// y1(a) = y01, y2(a) = y02
//
// Inputs:
//   f         The name of the function f=(f1,f2) in the ODE
//   y         Space for the solution (with correct size on input)
//   y0        Initial condition
//   a         Initial time
//   b         Final time
// Outputs:
//   y         The solution (at equally spaced points)
///////////////////////////////////////////////////////////////////////////////
#include <vector>

void trapMethod2(void f(double,double[2],double[2]), std::vector<double> y[2],
		 double y0[2], double a=0, double b=1);

void trapMethod2(void f(double,double[2],double[2]), std::vector<double>& x, 
                 std::vector<double> y[2], double y0[2], double a=0, double b=1);
#endif

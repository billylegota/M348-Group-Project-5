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
#include "backEulerMethod.h"
#include <cmath>
using namespace std;

int backEulerMethod(double f(double,double), double dyf(double,double), vector<double>& y,
		     double y0, double a, double b, double newtonTol) {
  int n = y.size()-1;
  double h = (b-a)/n;

  double t = a;
  y[0] = y0;

  for(int i=0; i<n; i++) {
    t += h;

    // Newton loop
    double yy = y[i];
    int iteration = 0;
    while(1) {
      double dyy = - (yy - h*f(t,yy) - y[i]) / (1 - h*dyf(t,yy));
      yy += dyy;

      if(fabs(dyy) <= newtonTol) break;
      iteration++;
      if(iteration >= 10) return 1;
    }
    y[i+1] = yy;
  }
  return 0;
}
  

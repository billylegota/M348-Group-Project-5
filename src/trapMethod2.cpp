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
#include "trapMethod2.h"
#include "matlabPlot.h"
using namespace std;

void trapMethod2(void f(double,double[2],double[2]), vector<double> y[2], double y0[2], double a, double b) {
  int m = y[0].size()-1;
  double h = (b-a)/m;

  double t = a;
  y[0][0] = y0[0];
  y[1][0] = y0[1];

  for(int i=0; i<m; i++) {
    double f1[2];
    double yy[2];
    yy[0] = y[0][i];
    yy[1] = y[1][i];
    f(t,yy,f1);
    double yEuler[2];
    yEuler[0] = y[0][i] + h*f1[0];
    yEuler[1] = y[1][i] + h*f1[1];

    t += h;
    double f2[2];
    f(t,yEuler,f2);

    y[0][i+1] = y[0][i] + h*(f1[0] + f2[0])/2;
    y[1][i+1] = y[1][i] + h*(f1[1] + f2[1])/2;
  }
}
 
void trapMethod2(void f(double,double[2],double[2]), vector<double>& x, 
                 vector<double> y[2], double y0[2], double a, double b) {
  int m = y[0].size()-1;
  double h = (b-a)/m;

  double t = a;
  x[0] = t;
  y[0][0] = y0[0];
  y[1][0] = y0[1];

  for(int i=0; i<m; i++) {
    double f1[2];
    double yy[2];
    yy[0] = y[0][i];
    yy[1] = y[1][i];
    f(t,yy,f1);
    double yEuler[2];
    yEuler[0] = y[0][i] + h*f1[0];
    yEuler[1] = y[1][i] + h*f1[1];

    t += h;
    double f2[2];
    f(t,yEuler,f2);

    y[0][i+1] = y[0][i] + h*(f1[0] + f2[0])/2;
    y[1][i+1] = y[1][i] + h*(f1[1] + f2[1])/2;
    x[i+1] = t;
  }
}
 
 

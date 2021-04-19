#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
using namespace std;

#include "trapMethod2.h"
#include "matlabPlot.h"

static const double gravity = 9.8;
static double length;
static double drag;

void f(double t, double y[2], double ff[2]) {
  ff[0] = y[1];
  ff[1] = - (gravity/length)*sin(y[0]) - drag*y[1];
}

int main() {
  cout << "Enter length and drag: ";
  cin >> length >> drag;

  double a,b,y0[2];
  int n;
  cout << "Enter a,b,y0[2],n: ";
  cin >> a >> b >> y0[0] >> y0[1] >> n;
  vector<double> x(n+1);
  vector<double> y[2];
  y[0].resize(n+1);
  y[1].resize(n+1);
  //trapMethod2(f, y, y0, a, b);
  trapMethod2(f, x, y, y0, a, b);

  string fileName;
  cout << "Enter output file name: ";
  cin >> fileName;
  ofstream fout(fileName.c_str());
  if(!fout) {
    cerr << "ERROR: Opening file" << endl;
    return 1;
  }
  //matlabPlot(fout,y[0]);
  //matlabPlot(fout,x,y);
  string xlabel,ylabel,title,leg1,leg2;
  double h = (b-a)/n;
  if (drag == 0) {
    title = "Pendulum: Explicit Trapezoidal Method, h=" + to_string(h);
  } else {
    title = "Damped Pendulum: Explicit Trapezoidal Method, drag=" 
          + to_string(drag) + ", h=" + to_string(h);
  } 
  xlabel = "time";
  ylabel = "";
  leg1 = "angle";  
  leg2 = "angular velocity";  

  matlabPlot(fout,x,y,title,xlabel,ylabel,leg1,leg2);

  return 0;
}
  

#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include "backEulerMethod.h"
#include "matlabPlot.h"

double f(double t, double y) { return -10*y; }
double dyf(double t, double y) { return -10; }

double f2(double t, double y) { return (1 + (8 - 9*y)*y)*y; }
double dyf2(double t, double y) { return 1 + (16 - 27*y)*y; }

double f3(double t, double y) { return -y*y; }
double dyf3(double t, double y) { return -2*y; }

double f4(double t, double y) { return -y/(1+y*y); }
double dyf4(double t, double y) { return (y*y-1)/((1+y*y)*(1+y*y)); }

int main() {
  double a,b,y0;
  int n;
  cout << "Enter a,b,y0,n: ";
  cin >> a >> b >> y0 >> n;
  vector<double> y(n+1);

  backEulerMethod(f4, dyf4, y, y0, a, b);

  string fileName;
  cout << "Enter output file name: ";
  cin >> fileName;
  ofstream fout(fileName.c_str());
  if(!fout) {
    cerr << "ERROR: Opening file" << endl;
    return 1;
  }
  matlabPlot(fout,y);

  return 0;
}
  

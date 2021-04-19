#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
using namespace std;

#include "trapMethod.h"
#include "matlabPlot.h"

double f(double t, double y) { return t*cos(y); }

double f2(double t, double y) { return t/(1+y*y); }

double f3(double t, double y) { return (2-2*t*y)/(t*t+1); }
// y_true = (2*x+1)/(x*x+1); run on [-1 3] y0=-0.5 N=4,8,16,32
// In matlab:  
// yt=@(x) (2.*x+1)./(x.*x+1); t=linspace(-1,3,100);
// t2; plot(x,y,'o-'); hold on; plot(t,yt(t),'r')

int main() {
  double a,b,y0;
  int n;
  cout << "Enter a,b,y0,n: ";
  cin >> a >> b >> y0 >> n;
  vector<double> x(n+1);
  vector<double> y(n+1);

  //trapMethod(f, y, y0, a, b);
  //trapMethod(f, x, y, y0, a, b);
  trapMethod(f3, x, y, y0, a, b);

  string fileName;
  cout << "Enter output file name: ";
  cin >> fileName;
  ofstream fout(fileName.c_str());
  if(!fout) {
    cerr << "ERROR: Opening file" << endl;
    return 1;
  }
  //matlabPlot(fout,y);
  matlabPlot(fout,x,y);

  return 0;
}
  
